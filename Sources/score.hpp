#pragma once

#include <string>
#include <vector>

#include "mdp.hpp"

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

class OScofoScore {
  public:
    int Name2Midi(std::string note);
    void Parse(OScofoMDP *MDP, const char *Score);
    bool ScoreLoaded() {
        return m_ScoreLoaded;
    }
    States GetStates() {
        return m_States;
    };
    void AddState(State State) {
        m_States.push_back(State);
    }
    void ClearStates() {
        m_States.clear();
    }

  private:
    State AddNote(State State, std::vector<std::string> tokens, double bpm, int lineCount);
    double FollowBpm(std::vector<std::string> tokens, int lineCount);
    double m_LastOnset = 0;
    double m_LastPhase = 0;
    bool m_ScoreLoaded = false;
    double m_Tunning = 440;
    double m_K = 1;
    States m_States;
};
