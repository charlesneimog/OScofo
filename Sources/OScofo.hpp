#pragma once

#include "OScofo/mdp.hpp"
#include "OScofo/mir.hpp"
#include "OScofo/score.hpp"
#include "OScofo/states.hpp"

#define OSCOFO_VERSION_MAJOR 0
#define OSCOFO_VERSION_MINOR 1
#define OSCOFO_VERSION_PATCH 0

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
    void SetCurrentState(int Event);

    // Get Functions
    double GetLiveBPM();
    int GetEventIndex();
    double GetKappa();

    // Main Functions
    bool ParseScore(std::string ScorePath);
    bool ProcessBlock(std::vector<double> &AudioBuffer);

    // Helpers Functions
    bool ScoreIsLoaded();
    std::string GetError();

  private:
    OScofoMDP m_MDP;
    OScofoMIR m_MIR;
    OScofoScore m_Score;

    States m_States;
    Description m_Desc;
    int m_CurrentState = 0;

    std::string m_Error;
};
