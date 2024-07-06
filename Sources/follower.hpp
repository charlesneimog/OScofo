#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <m_pd.h>

// FFT
#include <fftw3.h>

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

#define DEBUG true
#define DEBUGDSP false

class Follower;
using PitchTemplateArray = std::vector<double>;

// ╭─────────────────────────────────────╮
// │            States of MDP            │
// ╰─────────────────────────────────────╯
struct State {
    int Id;
    bool Valid;
    int Type; // NOTE, CHORD, PIZZ, SILENCE
    double Freq;

    // Time
    double BPMExpected;
    double BPMObserved;
    double OnsetExpected;
    double OnsetObserved;
    double PhaseExpected;
    double PhaseObserved;

    double IOIPhaseExpected;
    double IOIPhaseObserved;
    double IOIPhiN;
    double IOIHatPhiN;
    double Duration;
};
using States = std::vector<State>;

// ─────────────────────────────────────
enum EventType {
    SILENCE = 0,
    NOTE,
    // TODO: Add more events
};

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class FollowerMIR {
  public:
    FollowerMIR(Follower *x);
    static double Mtof(double note, double tunning);
    static double Ftom(double freq, double tunning);
    static double Freq2Bin(double freq, double n, double Sr);

    void SetTreshold(double dB);
    struct m_Description {
        double WindowSize;
        double Sr;
        double Freq;
        double Midi;
        double Quality;
        double dB;
        std::vector<double> SpectralPower;
        std::vector<double> NormSpectralPower;
        double TotalPower;
        double MaxAmp;
        double SpectralFlatness;

        // Pitch
        // std::vector<double> SpectralChroma;
        // double HigherChroma;
    };

    void GetDescription(std::vector<double> in, m_Description *Desc, double Tunning);
    void GetMidi(double tunning);

    // Time
    double TimePrediction();
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    double GetEventTimeElapsed();
    double GetTempoInEvent();

  private:
    // Obj
    Follower *m_x;

    // Helpers
    std::vector<double> m_WindowingFunc;
    void GetHanning(int WindowSize);

    // FFT
    // double *m_FFTIn;
    fftw_complex *m_FFTOut;
    fftw_plan m_FFTPlan;
    void GetFFTDescriptions(std::vector<double> in, m_Description *Desc);

    // Env
    double m_dBTreshold = -80;
    void GetRMS(std::vector<double> in, m_Description *Desc);

    // Audio
    double m_WindowSize;
    double m_BlockSize;
    double m_HopSize;
    double m_Sr;

    // Time
    double m_EventTimeElapsed = 0.0; // ms
};

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class FollowerMDP {
  public:
    FollowerMDP(Follower *Obj);

    // Init Functions
    void SetScoreStates(States States);
    void UpdatePitchTemplate();
    void UpdatePhaseValues();

    // Config Functions
    void SetPitchTemplateSigma(double f);
    void SetHarmonics(int i);
    void SetBPM(double Bpm);
    double GetLiveBPM();
    void ResetLiveBpm();
    void SetTreshold(double dB);

    // Get Functions
    int GetTunning();

    std::vector<State> m_States;
    std::vector<double> m_PitchTemplate;

    std::vector<State> GetStates();
    State GetState(int Index);
    void AddState(State state);
    void ClearStates();

    int GetStatesSize();
    int GetEvent(Follower *x, FollowerMIR *MIR);

    // Set Variables
    void SetTunning(double Tunning);
    void SetEvent(int Event);
    void SetTimeAccumFactor(double f);
    void SetTimeCouplingStrength(double f);

  private:
    Follower *m_x;

    // Audio
    double m_Sr;
    double m_WindowSize;
    double m_HopSize;
    double m_Harmonics = 10;
    double m_PitchTemplateHigherBin = 0;
    double m_dBTreshold = -70;
    FollowerMIR::m_Description *m_Desc;

    // Events
    double m_Tunning = 440;
    int m_CurrentEvent = -1;

    // Time
    void GetBPM();
    double m_AccumulationFactor =
        0.5; // The adaptation rate between 0-1 determines an adaptation time constant, with
             // smaller values approximating r over longer time periods (LARGE, 1999, p. n.

    double m_CouplingStrength =
        0.5; // Coupling strength captures the amount of force exerted on the
             // attentional rhythm and determines, among other factors, the
             // speed with which the coupled system relaxes to theattractor.
    double m_SyncStr = 0;
    double m_TimeInThisEvent = 0;

    double m_LastTn = 0;
    double m_Tn = 0;

    double m_LastPsiN = 0;
    double m_PsiN = 0;
    double m_PsiN1 = 0;
    double m_BPM = 0;

    // Time
    double InverseA2(double r);
    double ModPhases(double value);
    double CouplingFunction(double Phi, double PhiMu, double Kappa);

    // Pitch
    double m_PitchTemplateSigma = 0.3;
    double m_Z = 0.5; // TODO: How should I call this?
    std::unordered_map<double, PitchTemplateArray> m_PitchTemplates;

    // MDP
    double GetBestEvent(FollowerMIR::m_Description *Desc);
    double GetReward(State NextPossibleState, FollowerMIR::m_Description *Desc);
    double GetPitchSimilarity(State NextPossibleState, FollowerMIR::m_Description *Desc);
    double GetTimeSimilarity(State NextPossibleState, FollowerMIR::m_Description *Desc);
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

    int Name2Midi(std::string note);
    void Parse(FollowerMDP *MDP, const char *score);
    double GetTimePhase(double t_n0, double t_n1, double phase0, double pulse);
    bool ScoreLoaded() {
        return m_ScoreLoaded;
    }
    States GetStates() {
        return m_States;
    };
    void AddState(State State) {
        m_States.push_back(State);
    }
    void ClearStates() {
        m_States.clear();
    }

  private:
    State AddNote(State State, std::vector<std::string> tokens, double bpm, int lineCount);
    double FollowBpm(std::vector<std::string> tokens, int lineCount);

    Follower *m_x;
    double m_lastOnset = 0;
    double m_lastPhase = 0;
    bool m_ScoreLoaded = false;
    double m_Tunning = 440;
    double m_K = 1;
    States m_States;
};

// ╭─────────────────────────────────────╮
// │           PureData Object           │
// ╰─────────────────────────────────────╯
class Follower {
  public:
    t_object xObj;
    t_sample Sample;
    std::vector<double> inBuffer;
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
    double BlockIndex;
    double BlockSize;
    double HopSize;
    double WindowSize;
    double Sr;

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
#if DEBUG
        std::string message = buffer.str();
        const char *c_message = message.c_str();
        printf("%s\n", c_message);
        std::cout.flush();
#endif
    }

  private:
    std::ostringstream buffer;
};

#define LOGE() LogStream()
