#include "../OScofo.hpp"

// ╭─────────────────────────────────────╮
// │     Construstor and Destructor      │
// ╰─────────────────────────────────────╯
//  ─────────────────────────────────────
OScofo::OScofo(float Sr, float WindowSize, float HopSize)
    : m_MDP(Sr, WindowSize, HopSize), m_MIR(Sr, WindowSize, HopSize) {
    m_States = States();
    m_Desc = Description();
}

// ╭─────────────────────────────────────╮
// │            Set Functions            │
// ╰─────────────────────────────────────╯
void OScofo::SetPitchTemplateSigma(double Sigma) {
    m_MDP.SetPitchTemplateSigma(Sigma);
}

// ─────────────────────────────────────
void OScofo::SetHarmonics(int Harmonics) {
    m_MDP.SetHarmonics(Harmonics);
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
}

// ─────────────────────────────────────
void OScofo::SetTunning(double Tunning) {
    m_MDP.SetTunning(Tunning);
    m_Score.SetTunning(Tunning);
}

// ─────────────────────────────────────
void OScofo::SetCurrentState(int Event) {
    if (Event < 0) {
        printf("Event must be greater than -1, current event set to 0.\n");
        Event = 0;
    }
    m_MDP.SetCurrentEvent(Event);
}

// ╭─────────────────────────────────────╮
// │            Get Functions            │
// ╰─────────────────────────────────────╯
int OScofo::GetEventIndex() {
    return m_CurrentState; // TODO: Implement yet
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
// │           Main Functions            │
// ╰─────────────────────────────────────╯
bool OScofo::ParseScore(std::string ScorePath) {
    LOGE() << "OScofo::ParseScore";
    m_States = m_Score.Parse(ScorePath);

    for (int i = 0; i < m_States.size(); i++) {
        if (!m_States[i].Valid) {
            m_Error = std::string("Error on line ") + std::to_string(m_States[i].Line) + ": " +
                      m_States[i].Error;
            return false;
        }
    }

    m_MDP.SetScoreStates(m_States);

    return true;
}

// ─────────────────────────────────────
bool OScofo::ProcessBlock(std::vector<double> &AudioBuffer) {
    if (!m_Score.ScoreIsLoaded()) {
        return true;
    }
    m_MIR.GetDescription(AudioBuffer, m_Desc);
    m_CurrentState = m_MDP.GetEvent(m_Desc);

    LOGE() << "States event size: " << m_States.size();
    return true;
}
