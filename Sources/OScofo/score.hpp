#pragma once

#include <string>
#include <vector>

#include "log.hpp"
#include "states.hpp"

namespace OScofo {

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

class Score {
  public:
    States Parse(std::string ScoreFile);
    void SetTunning(double Tunning);
    bool ScoreIsLoaded();

  private:
    // Helpers
    double ModPhases(double Phase);
    MacroState AddTransState(MacroState &State, int ScoreEvent, int BPM);
    int Name2Midi(std::string note);
    bool SpaceTab(const std::string &line, int numSpaces);

    // Add events
    MacroState AddNote(States &ScoreStates, std::vector<std::string> Tokens);
    MacroState AddChord(States &ScoreStates, std::vector<std::string> Tokens);
    MacroState AddTrill(States &ScoreStates, std::vector<std::string> Tokens);
    MacroState AddMulti(States &ScoreStates, std::vector<std::string> Tokens);
    MacroState AddRest(States &ScoreStates, std::vector<std::string> Tokens);

    // Variables
    int m_ScorePosition = 1;
    int m_LineCount = 0;
    int m_MarkovIndex = 0;
    double m_LastOnset = 0;
    double m_LastPhase = 0;
    double m_CurrentBPM = -1;
    double m_PrevDuration;
    double m_Tunning = 440;
    bool m_ScoreLoaded = false;
};
} // namespace OScofo
