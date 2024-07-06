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
    void Parse(States &States, const char *ScoreFile);
    bool ScoreLoaded() {
        return m_ScoreLoaded;
    }

  private:
    State AddNote(State State, std::vector<std::string> tokens, double bpm, int lineCount);
    double FollowBpm(std::vector<std::string> tokens, int lineCount);
    double m_LastOnset = 0;
    double m_LastPhase = 0;
    bool m_ScoreLoaded = false;
    double m_Tunning = 440;
    double m_K = 1;
};
