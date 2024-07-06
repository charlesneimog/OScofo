#pragma once

#include <unordered_map>
#include <vector>

#include "mir.hpp"
#include "states.hpp"

using PitchTemplateArray = std::vector<double>;

// ╭─────────────────────────────────────╮
// │            States of MDP            │
// ╰─────────────────────────────────────╯

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class OScofoMDP {
  public:
    OScofoMDP(float Sr, float WindowSize, float HopSize);

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
    int GetEvent(std::vector<double> AudioIn, OScofoMIR *MIR);

    // Set Variables
    void SetTunning(double Tunning);
    void SetEvent(int Event);
    void SetTimeAccumFactor(double f);
    void SetTimeCouplingStrength(double f);

  private:
    // Audio
    double m_Sr;
    double m_WindowSize;
    double m_HopSize;
    double m_Harmonics = 10;
    double m_PitchTemplateHigherBin = 0;
    double m_dBTreshold = -70;
    OScofoMIR::m_Description *m_Desc;

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
    double GetBestEvent(OScofoMIR::m_Description *Desc);
    double GetReward(State NextPossibleState, OScofoMIR::m_Description *Desc);
    double GetPitchSimilarity(State NextPossibleState, OScofoMIR::m_Description *Desc);
    double GetTimeSimilarity(State NextPossibleState, OScofoMIR::m_Description *Desc);
};
