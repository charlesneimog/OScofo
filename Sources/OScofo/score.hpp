#pragma once

#include <string>
#include <vector>

#include "states.hpp"
#include <tree_sitter/api.h>

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
    States m_ScoreStates;

    // Helpers
    double ModPhases(double Phase);
    MacroState AddTransState(MacroState &State, int ScoreEvent, int BPM);
    int Name2Midi(std::string note);
    bool SpaceTab(const std::string &line, int numSpaces);
    void ParseInput();
    void PrintTreeSitterNode(TSNode node, int indent = 0);

    void ProcessEvent(TSNode Event);
    void ProcessConfig(TSNode Event);

    void ProcessNote(TSNode Note);

    // Get TreeSitter Values
    std::string GetCodeStr(TSNode Node);
    double GetFreqsFromNode(TSNode Node);
    double GetDurationFromNode(TSNode Node);

    // Events
    MacroState NoteEvent(TSNode Node);
    MacroState TrillEvent(TSNode Node);

    // Add events
    MacroState AddNote(std::vector<std::string> Tokens);
    MacroState AddChord(std::vector<std::string> Tokens);
    MacroState AddTrill(std::vector<std::string> Tokens);
    MacroState AddMulti(std::vector<std::string> Tokens);
    MacroState AddDumpSilence();
    MacroState AddRest(std::vector<std::string> Tokens);
    void AddAction(std::vector<std::string> Tokens);

    // Variables
    std::string m_TxtInput;
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
