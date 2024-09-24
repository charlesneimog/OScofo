#pragma once

#include <string>
#include <vector>

#include "log.hpp"
#include "states.hpp"

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

class OScofoScore {
  public:
    States Parse(std::string ScoreFile);
    void SetTunning(double Tunning);
    bool ScoreIsLoaded();

  private:
    // Helpers
    double ModPhases(double Phase);
    MacroState AddTransState(MacroState &State, int ScoreEvent, int BPM);
    int Name2Midi(std::string note);

    // Add events
    void AddNote(States &ScoreStates, std::vector<std::string> Tokens);
    void AddChord(States &ScoreStates, std::vector<std::string> Tokens);
    void AddTrill(States &ScoreStates, std::vector<std::string> Tokens);
    void AddMulti(States &ScoreStates, std::vector<std::string> Tokens);
    void AddRest(States &ScoreStates, std::vector<std::string> Tokens);
    void AddTrans(States &ScoreStates, std::vector<std::string> Tokens);

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
