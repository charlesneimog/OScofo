#pragma once

#include <unordered_map>
#include <vector>

#include "states.hpp"

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

using PitchTemplateArray = std::vector<double>;

using MatrixMap = std::unordered_map<int, std::unordered_map<int, double>>;
using Array2DMap = std::unordered_map<int, std::vector<double>>;

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class OScofoMDP {
  public:
    OScofoMDP(float Sr, float WindowSize, float HopSize);
    // ~OScofoMDP();

    void UpdatePitchTemplate();
    void UpdatePhaseValues();

    // Config Functions
    void SetScoreStates(States States);
    void SetPitchTemplateSigma(double Sigma);
    void SetHarmonics(int Harmonics);
    void SetBPM(double Bpm);
    void SetdBTreshold(double dB);
    void SetTunning(double Tunning);
    void SetCurrentEvent(int Event);
    void SetTimeAccumFactor(double f);
    void SetTimeCouplingStrength(double f);
    void SetBeatsAhead(double BeatsAhead);

    // Get Functions
    int GetEvent(Description &Desc);
    double GetLiveBPM();
    double GetKappa();

  private:
    // Audio
    double m_Sr;
    double m_WindowSize;
    double m_HopSize;
    int m_AudioTick = 0;
    double m_Harmonics = 10;
    int m_PitchTemplateHigherBin = 0;
    double m_dBTreshold = -55;

    // Events
    double m_Tunning = 440;
    int m_CurrentEvent = -1;

    // Time
    void UpdateBPM();
    double m_AccumulationFactor = 0.5;
    // The adaptation rate between 0-1 determines an adaptation time constant, with
    // smaller values approximating r over longer time periods (LARGE, 1999, p. n.
    double m_CouplingStrength = 0.5;
    // Coupling strength captures the amount of force exerted on the
    // attentional rhythm and determines, among other factors, the
    // speed with which the coupled system relaxes to theattractor.
    double m_SyncStr = 0;

    // Markov
    void CreateMarkovMatrix();
    int GetBestEventIndex(Description &Desc);
    double ForwardRecursion(Description &Desc);
    std::vector<double> m_Nt;
    std::vector<std::vector<double>> m_Forwardj;
    std::vector<std::vector<double>> m_Normj;
    std::vector<std::vector<double>> m_StateInJ;

    int PseudoGuedonAlgorithm(Description &Desc, int j);
    double SemiMarkovState(Description &Desc, int j);
    double MarkovState(Description &Desc, int j);

    double SemiMarkovStateTest(Description &Desc, int j);
    double GetSojournTime(State &PossibleState, int u);
    int MaxBlocksInState(State &State);

    int m_StateWindow = 0;
    int m_T = 0;
    int m_BlocksInThisEvent = 0;
    int m_MaxHistory = 40;

    MatrixMap m_TransitionsProb;
    Array2DMap m_EventObservations;
    Array2DMap m_PitchObservations;

    double m_BlockDur = 0;
    double m_BeatsAhead = 1;
    double m_TimeInThisEvent = 0;
    double m_LastTn = 0;
    double m_Tn = 0;
    double m_Tn1 = 0;
    double m_OnsetN1 = 0;
    double m_Mu = 0;
    int m_LastEvent = 0;

    double m_LastPsiN = 0;
    double m_PsiN = 0;
    double m_PsiN1 = 0;
    double m_BPM = 0;
    double m_Kappa = 0;
    double m_MaxAheadSeconds = 0;
    std::unordered_map<double, double> m_KappaTable;

    // Time
    void CreateKappaTable();
    double GetKappaAt(double SyncStr);
    double InverseA2(double r);
    double ModPhases(double value);
    double CouplingFunction(double Phi, double PhiMu, double Kappa);

    // Pitch
    double m_PitchTemplateSigma = 0.1;
    // In Higher values, the pitch algorith becomes more tolerant to pitch changes
    double m_Z = 0.5;
    // Scaling Factor that controls how fast an increase in
    // distance translates to decrease in probability
    std::unordered_map<double, PitchTemplateArray> m_PitchTemplates;

    // MDP
    std::vector<State> m_States;
    double GetReward(States &NextPossibleStates, Description &Desc);
    double GetPitchSimilarity(State &NextPossibleState, Description &Desc);

    // Viterbi | SemiMarkov
    double ComputeViterbiRecursion(State &JState, Description &Desc);
};
