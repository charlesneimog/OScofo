#include "../OScofo.hpp"

// ╭─────────────────────────────────────╮
// │     Construstor and Destructor      │
// ╰─────────────────────────────────────╯
//  ─────────────────────────────────────
OScofo::OScofo(float Sr, float FftSize, float HopSize) : m_MDP(Sr, FftSize, HopSize), m_MIR(Sr, FftSize, HopSize) {
    m_States = States();
    m_Desc = Description();
}

// ╭─────────────────────────────────────╮
// │            Set Functions            │
// ╰─────────────────────────────────────╯
void OScofo::SetPitchTemplateSigma(double Sigma) {
    m_MDP.SetPitchTemplateSigma(Sigma);
    m_MDP.UpdatePitchTemplate();
}

// ─────────────────────────────────────
void OScofo::SetHarmonics(int Harmonics) {
    m_MDP.SetHarmonics(Harmonics);
    m_MDP.UpdatePitchTemplate();
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
    m_MDP.SetTunning(Tunning);
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
double OScofo::GetKappa() {
    return m_MDP.GetKappa();
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
    return m_States;
}

// ─────────────────────────────────────
std::vector<double> OScofo::GetPitchTemplate(double Freq, int Harmonics, double Sigma) {
    return m_MDP.GetPitchTemplate(Freq, Harmonics, Sigma);
}

// ╭─────────────────────────────────────╮
// │           Main Functions            │
// ╰─────────────────────────────────────╯
bool OScofo::ParseScore(std::string ScorePath) {
    m_Score.Parse(m_States, ScorePath);
    m_MDP.SetScoreStates(m_States);
    return true;
}

// ─────────────────────────────────────
bool OScofo::ProcessBlock(std::vector<double> &AudioBuffer) {
    if (!m_Score.ScoreIsLoaded()) {
        return true;
    }
    m_MIR.GetDescription(AudioBuffer, m_Desc);
    m_CurrentScorePosition = m_MDP.GetEvent(m_Desc);
    return true;
}
