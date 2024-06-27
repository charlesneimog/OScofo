#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <m_pd.h>

// FFT
#include <fftw3.h>

#define PI 3.14159265358979323846
#define TWO_PI (2 * M_PI)

class Follower;

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class FollowerMIR {
  public:
    FollowerMIR(Follower *x);
    static float Mtof(float note, float tunning);
    static float Ftom(float freq, float tunning);
    static float Freq2Bin(t_float freq, t_float n, t_float Sr);
    static unsigned GetPitchBinRanges(std::vector<float> binRanges, t_float thisPitch,
                                      t_float loFreq, t_float hiFreq, t_float pitchTolerance, int n,
                                      t_float sr);

    struct Description {
        float WindowSize;
        float Sr;
        float Tunning = 440;

        float Freq;
        float Midi;
        float Quality;
        float dB;
        float TimeElapsed;
        std::vector<float> SpectralImag;
        std::vector<float> SpectralReal;
        std::vector<float> SpectralPower;
        std::vector<float> NormSpectralPower;

        // Pitch
        std::vector<float> SpectralChroma;
        float HigherChroma;
    };

    void GetDescription(std::vector<float> *in, Description *Desc, float Tunning);
    void GetMidi(float tunning);

    // Time
    float TimePrediction();
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    float GetEventTimeElapsed();
    float GetTempoInEvent();
    float EventTimeElapsed = 0.0; // ms

  private:
    // Obj
    Follower *x;

    // FFT
    float *FFTIn;
    fftwf_complex *FFTOut;
    fftwf_plan FFTPlan;

    // Pitch
    bool CreateYin(float tolerance, float silence);
    void GetYin(std::vector<float> *in, Description *Desc);
    void AubioYin(std::vector<float> *in, Description *Desc);

    // MFCC
    void GetMFCC(std::vector<float> *in, Description *Desc);
    void GetChroma(std::vector<float> *in, Description *Desc);

    // FFT
    void GetFFT(std::vector<float> *in, Description *Desc);

    // Env
    void GetRMS(std::vector<float> *in, Description *Desc);

    // Audio
    float WindowSize;
    float BlockSize;
    float HopSize;
    float Sr;
};

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class FollowerMDP {
  public:
    FollowerMDP(Follower *Obj);

    void SetMinQualityForNote(float minQuality);
    float GetLiveBpm();
    void SetLiveBpm(float Bpm);
    void ResetLiveBpm();

    // MDP
    struct State {
        int Id;
        bool Valid;

        // Audio
        float Sr;
        float WindowSize;

        // Score
        int Type; // NOTE, CHORD, PIZZ, SILENCE

        // Pitch
        float Midi;
        float Freq;

        // Time
        float Bpm;
        float Onset;
        float Duration;

        // MDP
        float Similarity;
    };
    std::vector<State> States;

    std::vector<State> GetStates();
    State GetState(int Index);
    void AddState(FollowerMDP::State state);
    int GetStatesSize();
    std::vector<double> PitchTemplate;
    float RValue;

    int GetEvent(Follower *x, FollowerMIR *MIR);
    class TimeDecoder {
      public:
        TimeDecoder(Follower *Obj);
        double HatKappa(double r, double tol = 1e-6, double max_iter = 100);
        double RDispersion(int n, double coupleStrength, std::vector<float> mean,
                           std::vector<float> expPhasePos);
        double PhaseOfN();

      private:
        std::vector<float> Onsets;
    };

    float Tunning = 440;
    int CurrentEvent = -1;
    float LastOnset = 0;
    float PhasePrediction = 0;

  private:
    Follower *x;

    float GetBestEvent(std::vector<State> States, FollowerMIR::Description *Desc);
    float GetSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float GetPitchSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float GetTimeSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float CompareSpectralTemplate(State NextPossibleState, FollowerMIR::Description *Desc);

    // Thing place this
    void GetPitchTemplate(State NextPossibleState);

    FollowerMIR::Description *Desc;
    float MinQualityForNote = 0.9;

    std::vector<float> BpmHistory;
    float LiveBpm;
    float LiveTimePhase;
};

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

// ─────────────────────────────────────
class FollowerScore {
  public:
    FollowerScore(Follower *x) {
        this->x = x;
    }

    enum EventType {
        SILENCE = 0,
        NOTE,
        // TODO: Add more events
    };

    int Name2Midi(std::string note);
    void Parse(FollowerMDP *MDP, const char *score);
    float GetTimePhase(float t_n0, float t_n1, float phase0, float pulse);
    float Tunning = 440;
    float K = 1;

  private:
    FollowerMDP::State AddNote(FollowerMDP::State State, std::vector<std::string> tokens, float bpm,
                               int lineCount);

    Follower *x;
    float lastOnset = 0;
    float lastPhase = 0;
    float FollowBpm(std::vector<std::string> tokens, int lineCount);
};

// ╭─────────────────────────────────────╮
// │           PureData Object           │
// ╰─────────────────────────────────────╯
class Follower {
  public:
    t_object xObj;
    t_sample Sample;
    std::vector<float> *inBuffer;
    t_clock *Clock;

    //
    FollowerScore *Score;
    FollowerMDP *MDP;
    FollowerMIR *MIR;

    int Event;
    t_symbol *patchDir;

    // Testing
    bool Testing = false;

    // Score
    bool ScoreLoaded = false;
    bool Following = false;
    int CurrentEvent = 0;
    std::vector<double> PitchTemplate;

    // Audio
    float BlockIndex;
    float BlockSize;
    float HopSize;
    float WindowSize;
    float Sr;

    t_outlet *EventIndex;
    t_outlet *Tempo;
    t_outlet *Debug;
};

class LogStream {
  public:
    template <typename T> LogStream &operator<<(const T &value) {
        buffer << value;
        return *this;
    }

    ~LogStream() {
        // Convert the log message to a C string
        std::string message = buffer.str();
        const char *c_message = message.c_str();

        // Print the log message to pd_error()
        printf("%s\n", c_message);
    }

  private:
    std::ostringstream buffer;
};

#define LOGE() LogStream()
