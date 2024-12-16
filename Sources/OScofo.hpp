#pragma once

#include <OScofo/mdp.hpp>
#include <OScofo/mir.hpp>
#include <OScofo/score.hpp>
#include <OScofo/states.hpp>

#define OSCOFO_VERSION_MAJOR 0
#define OSCOFO_VERSION_MINOR 0
#define OSCOFO_VERSION_PATCH 2

namespace OScofo {

class OScofo {
  public:
    OScofo(float Sr, float WindowSize, float HopSize);

    // Set Functions
    void SetPitchTemplateSigma(double Sigma);
    void SetHarmonics(int Harmonics);
    void SetTimeAccumFactor(double TimeAccumFactor);
    void SetTimeCouplingStrength(double TimeCouplingStrength);
    void SetdBTreshold(double dB);
    void SetTunning(double Tunning);
    void SetCurrentEvent(int Event);
    void SetMinEntropy(double EntropyValue);

    // Get Functions
    double GetLiveBPM();
    int GetEventIndex();
    double GetKappa();
    double GetdBValue();
    ActionVec GetEventActions(int Index);

    // Main Functions
    bool ParseScore(std::string ScorePath);
    bool ProcessBlock(std::vector<double> &AudioBuffer);

    // Python Function for Research
    States GetStates();
    std::unordered_map<double, PitchTemplateArray> GetPitchTemplate();
    std::vector<double> GaussianProbTimeOnset(int j, double Sigma);

    // Helpers Functions
    bool ScoreIsLoaded();
    std::string GetError();

  private:
    MDP m_MDP;
    MIR m_MIR;
    Score m_Score;

    States m_States;
    Description m_Desc;
    int m_CurrentScorePosition = -1;

    double m_Sr;
    double m_FFTSize;
    double m_HopSize;

    std::string m_Error;
};
} // namespace OScofo
