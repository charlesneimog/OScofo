#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <m_pd.h>

// FFT
#include <fftw3.h>

#define TWO_PI (2 * M_PI)
#define DEBUG true

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

    struct m_Description {
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
        float MaxAmp;

        // Pitch
        std::vector<float> SpectralChroma;
        float HigherChroma;
    };

    void GetDescription(std::vector<float> in, m_Description *Desc, float Tunning);
    void GetMidi(float tunning);

    // Time
    float TimePrediction();
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    float GetEventTimeElapsed();
    float GetTempoInEvent();

  private:
    // Obj
    Follower *m_x;

    // FFT
    float *m_FFTIn;
    fftwf_complex *m_FFTOut;
    fftwf_plan m_FFTPlan;
    void GetFFT(std::vector<float> in, m_Description *Desc);

    // Env
    void GetRMS(std::vector<float> in, m_Description *Desc);

    // Audio
    float m_WindowSize;
    float m_BlockSize;
    float m_HopSize;
    float m_Sr;

    // Time
    float m_EventTimeElapsed = 0.0; // ms
};

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class FollowerMDP {
  public:
    FollowerMDP(Follower *Obj);

    // Config Functions
    void SetPitchTemplateSigma(float f);
    void SetLiveBpm(float Bpm);
    void ResetLiveBpm();

    // Get Functions
    float GetLiveBpm();

    struct m_State {
        int Id;
        bool Valid;
        int Type; // NOTE, CHORD, PIZZ, SILENCE
        float Freq;

        // Time
        float Bpm;
        float Onset;
        float PhaseOnset;
        float Duration;
        float Dispersion;
    };
    std::vector<m_State> m_States;
    std::vector<m_State> GetStates();
    m_State GetState(int Index);
    void AddState(m_State state);
    int GetStatesSize();
    std::vector<double> m_PitchTemplate;
    float m_RValue;

    int GetEvent(Follower *x, FollowerMIR *MIR);

    float m_Tunning = 440;
    int m_CurrentEvent = -1;
    float m_TimeInThisEvent = 0;
    std::vector<float> m_RealtimeDur; // TODO: How to name this?
    float m_BPM = 0;
    float m_PrevBPM = 0;
    float m_EtaPhi = 0.1;

  private:
    Follower *m_x;
    // MDP

    class m_TimeDecoder {
      public:
        m_TimeDecoder(Follower *Obj);
        double HatKappa(double r, double tol = 1e-6, double max_iter = 100);
        double RDispersion(int n, double coupleStrength, std::vector<float> mean,
                           std::vector<float> expPhasePos);
        double PhaseOfN();

      private:
        std::vector<float> m_Onsets;
    };

    float m_PitchTemplateSigma = 0.3;
    float m_z = 0.5; // TODO: How should I call this?

    void GetBestEvent(std::vector<m_State> States, FollowerMIR::m_Description *Desc);
    float GetReward(m_State NextPossibleState, FollowerMIR::m_Description *Desc);
    float GetPitchSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc);
    float GetTimeSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc);

    // Time Prediction
    void GetLiveBpm(std::vector<m_State> States);

    FollowerMIR::m_Description *m_Desc;
};

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

// ─────────────────────────────────────
class FollowerScore {
  public:
    FollowerScore(Follower *x) {
        this->m_x = x;
    }

    enum EventType {
        SILENCE = 0,
        NOTE,
        // TODO: Add more events
    };

    int Name2Midi(std::string note);
    void Parse(FollowerMDP *MDP, const char *score);
    float GetTimePhase(float t_n0, float t_n1, float phase0, float pulse);
    bool ScoreLoaded() {
        return m_ScoreLoaded;
    }
    float m_Tunning = 440;
    float m_K = 1;

  private:
    FollowerMDP::m_State AddNote(FollowerMDP::m_State State, std::vector<std::string> tokens,
                                 float bpm, int lineCount);
    float FollowBpm(std::vector<std::string> tokens, int lineCount);

    Follower *m_x;
    float m_lastOnset = 0;
    float m_lastPhase = 0;
    bool m_ScoreLoaded = false;
};

// ╭─────────────────────────────────────╮
// │           PureData Object           │
// ╰─────────────────────────────────────╯
class Follower {
  public:
    t_object xObj;
    t_sample Sample;
    std::vector<float> inBuffer;
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
#ifdef DEBUG
        // Convert the log message to a C string
        std::string message = buffer.str();
        const char *c_message = message.c_str();

        printf("%s\n", c_message);
#endif
    }

  private:
    std::ostringstream buffer;
};

#define LOGE() LogStream()
