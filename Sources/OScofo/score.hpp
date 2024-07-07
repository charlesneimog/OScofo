#pragma once

#include <string>
#include <vector>

#include "log.hpp"
#include "states.hpp"

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

class OScofoScore {
  public:
    int Name2Midi(std::string note);
    void Parse(States &States, std::string ScoreFile);
    void SetTunning(double Tunning);
    bool ScoreIsLoaded();

  private:
    State AddNote(State &State, std::vector<std::string> Tokens, double BPM, int LineCount);
    double FollowBpm(std::vector<std::string> Tokens, int LineCount);
    double m_LastOnset = 0;
    double m_LastPhase = 0;
    bool m_ScoreLoaded = false;
    double m_Tunning = 440;
    double m_K = 1;
};
