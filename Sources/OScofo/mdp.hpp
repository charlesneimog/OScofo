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
    void UpdatePitchTemplate();
    void UpdatePhaseValues();
    void UpdateInitialProbability();

    // Audio
    double m_Sr;
    double m_WindowSize;
    double m_HopSize;
    double m_Harmonics = 10;
    int m_PitchTemplateHigherBin = 0;
    double m_dBTreshold = -55;

    // Events
    double m_Tunning = 440;

    // Time
    void UpdateBPM(int Event);
    double m_AccumulationFactor = 0.5;
    // The adaptation rate between 0-1 determines an adaptation time constant, with
    // smaller values approximating r over longer time periods (LARGE, 1999, p. n.
    double m_CouplingStrength = 0.5;
    // Coupling strength captures the amount of force exerted on the
    // attentional rhythm and determines, among other factors, the
    // speed with which the coupled system relaxes to theattractor.
    double m_SyncStr = 0;

    // Description m_CurrentDesc;
    int m_CurrentStateIndex = 0;
    int m_MaxScoreState = 0;
    int m_T = 0;
    int m_LastT = 0;
    int m_BlocksInThisEvent = 0;
    int m_MaxHistory = 40;

    std::vector<double> m_InitialProbs;
    MatrixMap m_JumpsProb;
    Array2DMap m_EventObservations;
    Array2DMap m_AudioObservations;

    double m_BlockDur = 0;
    double m_BeatsAhead = 1;
    double m_TimeInThisEvent = 0;
    double m_LastTn = 0; // t_{n-1}
    double m_Tn = 0;     // t_{n}
    double m_Tn1 = 0;    // t_{n+1}

    double m_Mu = 0;

    double m_LastPsiN = 0;
    double m_PsiN = 0;
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
    int GetMaxLookAhead(int StateIndex);

    // Audio Observations:
    bool m_EventDetected = false;
    void GetAudioObservations(Description &Desc, int FirstStateIndex, int LastStateIndex);

    //  * pitch
    double Gaussian(double f, double mean, double sigma2);
    double m_PitchTemplateSigma = 0.1;
    double m_Z = 0.1;
    double m_BinWidth = 0.5;
    double m_BackgroundNoise = 0.1;
    std::unordered_map<double, PitchTemplateArray> m_PitchTemplates; //  * TODO: Add others

    // MDP
    std::vector<State> m_States;
    double GetReward(States &NextPossibleStates, Description &Desc);
    double GetPitchSimilarity(State &NextPossibleState, Description &Desc);

    // Markov and Viterbi
    MatrixMap CreateMarkovMatrix();
    int GetBestEventIndex();
    double ForwardRecursion(Description &Desc);

    int PseudoGuedonAlgorithm(Description &Desc, int j);
    double SemiMarkovState(int j, int T, MatrixMap &P);
    double MarkovState(int j, int T, MatrixMap &P);

    double GetSojournTime(State &PossibleState, int u);
    int MaxBlocksInState(State &State);
    void RotateObsValues(int Event, int BestEvent, int T);
};
