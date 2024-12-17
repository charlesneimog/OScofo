#pragma once

#include <OScofo/mdp.hpp>
#include <OScofo/mir.hpp>
#include <OScofo/score.hpp>
#include <OScofo/states.hpp>

#if defined(OSCOFO_LUA)
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#endif

#define OSCOFO_VERSION_MAJOR 0
#define OSCOFO_VERSION_MINOR 1
#define OSCOFO_VERSION_PATCH 0

namespace OScofo {

class OScofo;

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
    std::string GetLuaCode();
    double GetPitchProb(double f);

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

#if defined(OSCOFO_LUA)
    void InitLua();
    bool LuaExecute(std::string code);
    std::string LuaGetError();
    bool LuaAddModule(std::string name, lua_CFunction func);
#endif

  private:
    MDP m_MDP;
    MIR m_MIR;
    Score m_Score;

#if defined(OSCOFO_LUA)
    lua_State *m_LuaState;
#endif

    States m_States;
    Description m_Desc;
    int m_CurrentScorePosition = -1;

    double m_Sr;
    double m_FFTSize;
    double m_HopSize;

    std::string m_Error;
};

} // namespace OScofo
