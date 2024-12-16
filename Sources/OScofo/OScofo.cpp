#include <OScofo.hpp>
#include <cmath>

// ╭─────────────────────────────────────╮
// │     Construstor and Destructor      │
// ╰─────────────────────────────────────╯
namespace OScofo {

//  ─────────────────────────────────────
OScofo::OScofo(float Sr, float FftSize, float HopSize) : m_MDP(Sr, FftSize, HopSize), m_MIR(Sr, FftSize, HopSize) {
    m_States = States();
    m_Desc = Description();
    m_Sr = Sr;
    m_FFTSize = FftSize;
    m_HopSize = HopSize;
}

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
void OScofo::SetTimeCouplingStrength(double TimeCouplingStrength) {
    m_MDP.SetTimeCouplingStrength(TimeCouplingStrength);
}

// ─────────────────────────────────────
void OScofo::SetTimeAccumFactor(double TimeAccumFactor) {
    m_MDP.SetTimeAccumFactor(TimeAccumFactor);
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
std::string OScofo::GetError() {
    return m_Error;
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
    throw std::runtime_error("No states found, please use the ScoreParse first");
}

// ─────────────────────────────────────
std::unordered_map<double, PitchTemplateArray> OScofo::GetPitchTemplate() {
    return m_MDP.GetPitchTemplate();
}

// ─────────────────────────────────────
std::vector<double> OScofo::GaussianProbTimeOnset(int j, double sigma) {
    double BlockDur = (1 / m_Sr) * m_HopSize;
    MacroState State = m_MDP.GetState(j);
    MacroState LastState = m_MDP.GetState(m_MDP.GetStatesSize() - 1);
    double LastStateDur = LastState.Duration;
    double LastStateOnset = LastState.OnsetExpected;
    double EndTime = LastStateDur + LastStateOnset;
    int LastT = std::ceil(EndTime / BlockDur);
    std::vector<double> Probs(LastT);
    for (int i = 0; i < LastT; i++) {
        Probs.at(i) = m_MDP.GaussianProbTimeOnset(j, i, sigma);
    }

    return Probs;
}

// ╭─────────────────────────────────────╮
// │           Main Functions            │
// ╰─────────────────────────────────────╯
bool OScofo::ParseScore(std::string ScorePath) {
    m_States.clear();
    m_States = m_Score.Parse(ScorePath);
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
    return true;
}

} // namespace OScofo
