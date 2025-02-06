#include <OScofo.hpp>
#include <cmath>

// ╭─────────────────────────────────────╮
// │     Construstor and Destructor      │
// ╰─────────────────────────────────────╯
namespace OScofo {

#if defined(OSCOFO_LUA)
int luaopen_oscofo(lua_State *L);
#endif

//  ─────────────────────────────────────
OScofo::OScofo(float Sr, float FftSize, float HopSize) : m_MDP(Sr, FftSize, HopSize), m_MIR(Sr, FftSize, HopSize) {
    m_States = States();
    m_Desc = Description();
    m_Sr = Sr;
    m_FFTSize = FftSize;
    m_HopSize = HopSize;

    if (m_MIR.HasErrors() || m_MDP.HasErrors()) {
        for (auto &error : m_MIR.GetErrorMessage()) {
            SetError(error);
        }
        m_MIR.ClearError();
        for (auto &error : m_MDP.GetErrorMessage()) {
            SetError(error);
        }
        m_MDP.ClearError();
        return;
    }

#if defined(OSCOFO_LUA)
    InitLua();
#endif
}

//  ─────────────────────────────────────
void OScofo::SetNewAudioParameters(float Sr, float FftSize, float HopSize) {
    if (m_FFTSize == FftSize && m_HopSize == HopSize && m_Sr == Sr) {
        return;
    }
    m_Sr = Sr;
    m_FFTSize = FftSize;
    m_HopSize = HopSize;
    m_MDP = MDP(Sr, FftSize, HopSize);
    m_MIR = MIR(Sr, FftSize, HopSize);
}

// ╭─────────────────────────────────────╮
// │               Errors                │
// ╰─────────────────────────────────────╯
bool OScofo::HasErrors() {
    return m_HasErrors;
}

// ─────────────────────────────────────
std::vector<std::string> OScofo::GetErrorMessage() {
    return m_Errors;
}

// ─────────────────────────────────────
void OScofo::SetError(const std::string &message) {
    m_HasErrors = true;
    m_Errors.push_back(message);
}

// ─────────────────────────────────────
void OScofo::ClearError() {
    m_HasErrors = false;
    m_Errors.clear();
}

// ╭─────────────────────────────────────╮
// │                 Lua                 │
// ╰─────────────────────────────────────╯
#if defined(OSCOFO_LUA)
void OScofo::InitLua() {
    m_LuaState = luaL_newstate();
    luaL_openlibs(m_LuaState); // NOTE: Rethink if I load all functions
    lua_newtable(m_LuaState);
    lua_pushlightuserdata(m_LuaState, this);
    lua_setfield(m_LuaState, -2, "pointer");
    lua_setglobal(m_LuaState, "_OScofo");
    luaL_requiref(m_LuaState, "oscofo", luaopen_oscofo, 1);
}

// ─────────────────────────────────────
bool OScofo::LuaAddModule(std::string name, lua_CFunction func) {
    if (m_LuaState == nullptr) {
        return false;
    }
    luaL_requiref(m_LuaState, name.c_str(), func, 1);
    if (lua_isnil(m_LuaState, -1)) {
        return false;
    }
    return true;
}

// ─────────────────────────────────────
bool OScofo::LuaExecute(std::string code) {
    if (m_LuaState == nullptr) {
        return false;
    }
    int status = luaL_loadstring(m_LuaState, code.c_str());
    if (status == LUA_OK) {
        status = lua_pcall(m_LuaState, 0, LUA_MULTRET, 0);
        if (status != LUA_OK) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

// ─────────────────────────────────────
bool OScofo::LuaAddPointer(void *pointer, const char *name) {
    if (m_LuaState == nullptr) {
        return false;
    }
    lua_pushlightuserdata(m_LuaState, pointer);
    lua_setglobal(m_LuaState, name);
    return true;
}

// ─────────────────────────────────────
void OScofo::LuaAddPath(std::string path) {
    if (m_LuaState == nullptr) {
        return;
    }

    lua_getglobal(m_LuaState, "package");
    lua_getfield(m_LuaState, -1, "path");
    const char *current_path = lua_tostring(m_LuaState, -1);
    if (path.back() != '/') {
        lua_pushfstring(m_LuaState, "%s;%s/?.lua", current_path, path.c_str());
    } else {
        lua_pushfstring(m_LuaState, "%s;%s?.lua", current_path, path.c_str());
    }

    lua_setfield(m_LuaState, -3, "path");
    lua_pop(m_LuaState, 1);
}

// ─────────────────────────────────────
std::string OScofo::LuaGetError() {
    if (m_LuaState == nullptr) {
        return "m_LuaState is null";
    }
    if (lua_isstring(m_LuaState, -1)) {
        std::string errorMsg = lua_tostring(m_LuaState, -1);
        lua_pop(m_LuaState, 1);
        return errorMsg;
    }
    return "Unknown error";
}
#endif

// ╭─────────────────────────────────────╮
// │            Set Functions            │
// ╰─────────────────────────────────────╯
void OScofo::SetPitchTemplateSigma(double Sigma) {
    m_MDP.SetPitchTemplateSigma(Sigma);
    m_MDP.UpdateAudioTemplate();
}

// ─────────────────────────────────────
void OScofo::SetMinEntropy(double EntropyValue) {
    m_MDP.SetMinEntropy(EntropyValue);
}

// ─────────────────────────────────────
void OScofo::SetHarmonics(int Harmonics) {
    m_MDP.SetHarmonics(Harmonics);
    m_MDP.UpdateAudioTemplate();
}

// ─────────────────────────────────────
double OScofo::GetdBValue() {
    return 0;
}

// ─────────────────────────────────────
void OScofo::SetdBTreshold(double dB) {
    m_MDP.SetdBTreshold(dB);
    m_MIR.SetdBTreshold(dB);
}

// ─────────────────────────────────────
void OScofo::SetTunning(double Tunning) {
    m_Score.SetTunning(Tunning);
}

// ─────────────────────────────────────
void OScofo::SetCurrentEvent(int Event) {
    m_MDP.SetCurrentEvent(Event);
}

// ╭─────────────────────────────────────╮
// │            Get Functions            │
// ╰─────────────────────────────────────╯
int OScofo::GetEventIndex() {
    return m_CurrentScorePosition; // TODO: Implement yet
}

// ─────────────────────────────────────
double OScofo::GetLiveBPM() {
    return m_MDP.GetLiveBPM();
}

// ─────────────────────────────────────
ActionVec OScofo::GetEventActions(int Index) {
    return m_MDP.GetEventActions(Index);
}

// ─────────────────────────────────────
double OScofo::GetKappa() {
    return m_MDP.GetKappa();
}

// ─────────────────────────────────────
double OScofo::GetPitchProb(double f) {
    return m_MDP.GetPitchSimilarity(f);
}

// ─────────────────────────────────────
std::string OScofo::GetLuaCode() {
    return m_Score.GetLuaCode();
}
// ╭─────────────────────────────────────╮
// │          Helpers Functions          │
// ╰─────────────────────────────────────╯
bool OScofo::ScoreIsLoaded() {
    return m_Score.ScoreIsLoaded();
}

// ╭─────────────────────────────────────╮
// │ Python Research and Test Functions  │
// ╰─────────────────────────────────────╯
States OScofo::GetStates() {
    if (m_States.size() != 0) {
        return m_States;
    }
    SetError("No states found, please use the ScoreParse first");
    return m_States;
}

// ─────────────────────────────────────
std::unordered_map<double, PitchTemplateArray> OScofo::GetPitchTemplate() {
    return m_MDP.GetPitchTemplate();
}

// ─────────────────────────────────────
std::vector<double> OScofo::GetSpectrumPower() {
    return m_Desc.NormSpectralPower;
}

// ─────────────────────────────────────
double OScofo::GetFFTSize() {
    return m_FFTSize;
}

// ─────────────────────────────────────
double OScofo::GetHopSize() {
    return m_HopSize;
}

// ╭─────────────────────────────────────╮
// │           Main Functions            │
// ╰─────────────────────────────────────╯
bool OScofo::ParseScore(std::string ScorePath) {
    m_States.clear();
    m_States = m_Score.Parse(ScorePath);
    if (m_Score.HasErrors()) {
        for (auto &error : m_Score.GetErrorMessage()) {
            SetError(error);
            m_Score.ClearError();
        }
        return false;
    }

    m_FFTSize = m_Score.GetFFTSize();
    m_HopSize = m_Score.GetHopSize();
    SetNewAudioParameters(m_Sr, m_FFTSize, m_HopSize);

    // Parse Config
    m_MDP.SetPitchTemplateSigma(m_Score.GetPitchTemplateSigma());

    // Add States
    m_MDP.SetScoreStates(m_States);
    return true;
}

// ─────────────────────────────────────
bool OScofo::ProcessBlock(std::vector<double> &AudioBuffer) {
    if (!m_Score.ScoreIsLoaded()) {
        return false;
    }

    m_MIR.GetDescription(AudioBuffer, m_Desc);
    m_CurrentScorePosition = m_MDP.GetEvent(m_Desc);

    if (m_MDP.HasErrors()) {
        for (auto &error : m_MDP.GetErrorMessage()) {
            SetError(error);
        }
        m_MDP.ClearError();
        return false;
    }
    return true;
}

} // namespace OScofo
