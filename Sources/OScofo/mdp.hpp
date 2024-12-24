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
    void SetMinEntropy(double EntropyValue);

    void UpdateAudioTemplate();
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
    ActionVec GetEventActions(int Index);

    std::vector<MacroState> GetStates();
    MacroState GetState(int Index);
    double GetKappa();
    void AddState(MacroState state);
    void ClearStates();

    int GetStatesSize();
    int GetEvent(Description &Desc);
    double GetPitchSimilarity(double Freq);

    // Python For Research
    std::unordered_map<double, PitchTemplateArray> GetPitchTemplate();

    // Set Variables
    void SetTunning(double Tunning);
    void SetCurrentEvent(int Event);

    // Errors
    bool HasErrors() const {
        return m_HasErrors;
    }
    std::vector<std::string> GetErrorMessage() const {
        return m_Errors;
    }
    void SetError(const std::string &message) {
        m_HasErrors = true;
        m_Errors.push_back(message);
    }
    void ClearError() {
        m_HasErrors = false;
        m_Errors.clear();
    }

  private:
    // Config
    double m_MinEntropy = 0;

    // Audio
    double m_Sr;
    double m_FFTSize;
    double m_HopSize;
    double m_Harmonics = 5;
    double m_dBTreshold = -55;
    int m_BufferSize = 1000;

    // Events
    double m_Tunning = 440;
    int m_CurrentStateIndex = -1;

    // Time
    double m_SyncStrength = 0.5;
    double m_PhaseCoupling = 0.5;
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
    double GetInitialDistribution(int CurrentState, int j);
    std::vector<double> GetInitialDistribution();

    int GetMaxUForJ(MacroState &StateJ);

    // Pitch
    std::vector<MacroState> m_States;
    std::vector<double> m_PitchTemplate;
    double m_PitchTemplateSigma = 0.35;
    double m_PitchScalingFactor = 0.5; // TODO: How should I call this?
    std::unordered_map<double, PitchTemplateArray> m_PitchTemplates;

    // Audio Observations
    void GetAudioObservations(int FirstStateIndex, int LastStateIndex, int T);
    void BuildPitchTemplate(double Freq);
    Description m_Desc;

    // Markov
    bool m_EventDetected = false;
    double GetBestEvent();
    int GetMaxJIndex(int StateIndex);
    int Inference(int CurrentState, int j, int T);
    double SemiMarkov(MacroState &StateJ, int CurrentState, int j, int T, int bufferIndex);
    double Markov(MacroState &StateJ, int CurrentState, int j, int T, int bufferIndex);

    // Errors
    bool m_HasErrors = false;
    std::vector<std::string> m_Errors;
};
} // namespace OScofo
