#pragma once

#include <unordered_map>
#include <vector>

#include "states.hpp"

namespace OScofo {

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

using PitchTemplateArray = std::vector<double>;

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class MDP {
  public:
    MDP(float Sr, float WindowSize, float HopSize);

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
    void SetdBTreshold(double dB);

    // Get Functions
    int GetTunning();

    std::vector<MacroState> GetStates();
    MacroState GetState(int Index);
    double GetKappa();
    void AddState(MacroState state);
    void ClearStates();

    int GetStatesSize();
    int GetEvent(Description &Desc);

    // Python For Research
    std::vector<double> GetPitchTemplate(double Freq, int Harmonics, double Sigma);

    // Set Variables
    void SetTunning(double Tunning);
    void SetCurrentEvent(int Event);
    void SetTimeAccumFactor(double f);
    void SetTimeCouplingStrength(double f);
    double GaussianProbTimeOnset(int j, int T, double Sigma);

  private:
    // Audio
    double m_Sr;
    double m_FFTSize;
    double m_HopSize;
    double m_Harmonics = 10;
    double m_dBTreshold = -55;

    // Events
    double m_Tunning = 440;
    int m_CurrentStateIndex = -1;

    // Time
    double m_AccumulationFactor = 0.5; // The adaptation rate between 0-1 determines an adaptation time constant, with
                                       // smaller values approximating r over longer time periods (LARGE, 1999, p. n.

    double m_CouplingStrength = 0.5; // Coupling strength captures the amount of force exerted on the
                                     // attentional rhythm and determines, among other factors, the
                                     // speed with which the coupled system relaxes to theattractor.
    double m_SyncStr = 0;
    double m_TimeInPrevEvent = 0;

    double m_LastTn = 0;
    double m_BlockDur = 0;
    double m_CurrentStateOnset = 0;
    int m_MaxScoreState = 0;

    int m_Tau = 0;
    double m_LastPsiN = 0;
    double m_PsiN = 0;
    double m_PsiN1 = 0;
    double m_BPM = 0;
    double m_Kappa = 1;
    double m_MaxAheadSeconds;
    double m_BeatsAhead = 1;
    double m_NormAlpha = 1;
    double m_SecondsAhead = 2;

    // Time
    double UpdatePsiN(int StateIndex);
    double InverseA2(double r);
    double ModPhases(double value);
    double CouplingFunction(double Phi, double PhiMu, double Kappa);
    double GetSojournTime(MacroState &State, int u);

    // Markov and Probabilities
    double GetTransProbability(int i, int j);
    void GetInitialDistribution(int CurrentState, int j);
    int GetMaxUForJ(MacroState &StateJ);

    // Pitch
    std::vector<MacroState> m_States;
    std::vector<double> m_PitchTemplate;
    double m_PitchTemplateSigma = 1;
    double m_PitchScalingFactor = 0.5; // TODO: How should I call this?
    std::unordered_map<double, PitchTemplateArray> m_PitchTemplates;

    // Audio Observations
    void GetAudioObservations(Description &Desc, int FirstStateIndex, int LastStateIndex, int T);

    // Markov
    bool m_EventDetected = false;
    double GetBestEvent(Description &Desc);
    double GetPitchSimilarity(MacroState &NextPossibleState, Description &Desc);
    int FindMaxLookaheadIndex(int StateIndex);
    int Inference(int CurrentState, int j, int T);
    double SemiMarkov(int j, int T);
    double Markov(int j, int T);
};
} // namespace OScofo
