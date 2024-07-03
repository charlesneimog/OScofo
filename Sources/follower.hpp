#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <m_pd.h>

// FFT
#include <fftw3.h>

#define TWO_PI (2 * M_PI)
#define DEBUG false

class Follower;
using PitchTemplateArray = std::vector<float>;

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class FollowerMIR {
  public:
    FollowerMIR(Follower *x);
    static float Mtof(float note, float tunning);
    static float Ftom(float freq, float tunning);
    static float Freq2Bin(t_float freq, t_float n, t_float Sr);

    void SetTreshold(float dB);
    struct m_Description {
        float WindowSize;
        float Sr;
        float Freq;
        float Midi;
        float Quality;
        float dB;
        // float TimeElapsed;
        // std::vector<float> SpectralImag;
        // std::vector<float> SpectralReal;
        std::vector<float> SpectralPower;
        std::vector<float> NormSpectralPower;
        float MaxAmp;

        // Pitch
        // std::vector<float> SpectralChroma;
        // float HigherChroma;
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

    // Helpers
    std::vector<float> m_WindowingFunc;
    void GetHanning(int WindowSize);

    // FFT
    float *m_FFTIn;
    fftwf_complex *m_FFTOut;
    fftwf_plan m_FFTPlan;
    void GetFFT(std::vector<float> in, m_Description *Desc);

    // Env
    float m_dBTreshold = -80;
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
    struct m_State {
        int Id;
        bool Valid;
        int Type; // NOTE, CHORD, PIZZ, SILENCE
        float Freq;

        // Time
        float BPM;
        float OnsetExpected;
        float OnsetObserved;
        float IOI;

        float PhaseExpected;
        float PhaseObserved;
        float Duration;
        float Dispersion;
    };

    // Init Functions
    void UpdatePitchTemplate();
    void UpdatePhaseValues();

    // Config Functions
    void SetPitchTemplateSigma(float f);
    void SetHarmonics(int i);
    void SetBPM(float Bpm);
    float GetLiveBPM();
    void ResetLiveBpm();
    void SetTreshold(float dB);

    // Get Functions
    int GetTunning();

    std::vector<m_State> m_States;
    std::vector<double> m_PitchTemplate;

    std::vector<m_State> GetStates();
    m_State GetState(int Index);
    void AddState(m_State state);
    void ClearStates();

    int GetStatesSize();
    int GetEvent(Follower *x, FollowerMIR *MIR);

    // Set Variables
    void SetTunning(float Tunning);
    void SetEvent(int Event);
    void SetTimeAccumFactor(float f);
    void SetTimeCouplingStrength(float f);

  private:
    Follower *m_x;

    // Audio
    float m_Sr;
    float m_WindowSize;
    float m_HopSize;
    float m_Harmonics = 10;
    float m_PitchTemplateHigherBin = 0;
    float m_dBTreshold = -80;
    FollowerMIR::m_Description *m_Desc;

    // Events
    float m_Tunning = 440;
    int m_CurrentEvent = -1;

    // Time
    void GetBPM();
    float m_AccumulationFactor = 0.01;
    float m_CouplingStrength = 0.01;
    float m_LastPhiN = 0;
    float m_LastPhiNHat = 0;
    // float m_LastExpectedPhase = 0;
    // float m_LastObservedPhase = 0;
    float m_LastR = 1;
    float m_TimeInThisEvent = 0;
    float m_Tn = 0;
    float m_TnMinus1 = 0;

    float m_PsiK = 0;
    float m_PsiNMinus1 = 0;
    float m_PsiN = 0;
    float m_PsiN1 = 0;
    float m_BPM = 0;

    // Helpers
    double InverseA2(double r);
    float ModPhases(float value);
    float VonMises(float Phi, float PhiMu, float Kappa);

    // Pitch
    float m_PitchTemplateSigma = 0.3;
    float m_Z = 0.5; // TODO: How should I call this?
    std::unordered_map<float, PitchTemplateArray> m_PitchTemplates;

    // MDP
    float GetBestEvent(FollowerMIR::m_Description *Desc);
    float GetReward(m_State NextPossibleState, FollowerMIR::m_Description *Desc);
    float GetPitchSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc);
    float GetTimeSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc);
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

        printf("%s >> ", c_message);
        std::cout.flush();
#endif
    }

  private:
    std::ostringstream buffer;
};

#define LOGE() LogStream()
