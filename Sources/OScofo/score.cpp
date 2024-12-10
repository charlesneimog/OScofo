#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "score.hpp"
#include "tree_sitter/api.h"

extern "C" TSLanguage *tree_sitter_scofo();

namespace OScofo {

// ─────────────────────────────────────
void Score::PrintTreeSitterNode(TSNode node, int indent) {
    const char *type = ts_node_type(node);
    std::string text = ts_node_string(node);
    if (indent != 0) {
        std::cout << std::string(indent, ' ') << type << ": " << text << std::endl;
    }
    uint32_t child_count = ts_node_child_count(node);
    for (uint32_t i = 0; i < child_count; i++) {
        PrintTreeSitterNode(ts_node_child(node, i), indent + 4);
    }
}

// ─────────────────────────────────────
void Score::SetTunning(double Tunning) {
    m_Tunning = Tunning;
}

// ─────────────────────────────────────
bool Score::ScoreIsLoaded() {
    return m_ScoreLoaded;
}

// ─────────────────────────────────────
double Score::PitchNode2Freq(const std::string Score, TSNode node) {
    TSNode pitch = ts_node_child(node, 0);
    std::string type = ts_node_type(pitch);
    if (type == "midi") {
        int midi = std::stof(GetCodeStr(Score, pitch));
        return m_Tunning * pow(2, (midi - 69.0) / 12);

    } else if (type != "noteName") {
        throw std::runtime_error("Invalid pitch type");
    }

    char pitchName = GetChildStringFromId(Score, pitch, "pitchname")[0];
    std::string alt = GetChildStringFromId(Score, pitch, "alteration");
    std::string octave = GetChildStringFromId(Score, pitch, "octave");

    int classNote = -1;
    switch (pitchName) {
    case 'C':
        classNote = 0;
        break;
    case 'D':
        classNote = 2;
        break;
    case 'E':
        classNote = 4;
        break;
    case 'F':
        classNote = 5;
        break;
    case 'G':
        classNote = 7;
        break;
    case 'A':
        classNote = 9;
        break;
    case 'B':
        classNote = 11;
        break;
    default:
        throw std::runtime_error("Invalid note name");
    }

    if (alt != "") {
        if (alt == "#") {
            classNote++;
        } else if (alt == "b") {
            classNote--;
        } else if (alt == "##") {
            classNote += 2;
        } else if (alt == "bb") {
            classNote -= 2;
        }
    }
    int midi = classNote + 12 + (12 * std::stoi(octave));
    return m_Tunning * pow(2, (midi - 69.0) / 12);
}

// ─────────────────────────────────────
double Score::ModPhases(double Phase) {
    // Following Cont (2010) conventions
    double NewPhase = fmod(Phase + M_PI, TWO_PI);
    if (NewPhase < 0) {
        NewPhase += TWO_PI;
    }
    return NewPhase - M_PI;
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
std::string Score::GetCodeStr(const std::string &Score, TSNode Node) {
    int start = ts_node_start_byte(Node);
    int end = ts_node_end_byte(Node);
    return std::string(std::string_view(Score.data() + start, end - start));
}

// ─────────────────────────────────────
double Score::GetDurationFromNode(const std::string &Score, TSNode Node) {
    uint32_t count = ts_node_child_count(Node);
    if (count != 1) {
        throw std::runtime_error("Invalid duration count");
    }

    TSNode dur = ts_node_child(Node, 0);
    std::string dur_type = ts_node_type(dur);
    if (dur_type == "number") {
        std::string dur_str = GetCodeStr(Score, dur);
        return std::stof(dur_str);
    }
    throw std::runtime_error("Invalid duration type");
}

// ─────────────────────────────────────
MacroState Score::PitchEvent(const std::string &Score, TSNode Node) {
    m_ScorePosition++;

    double Midi;
    MacroState Note;
    Note.Line = m_LineCount;
    Note.Markov = SEMIMARKOV;
    Note.Index = m_ScoreStates.size();
    Note.ScorePos = m_ScorePosition;

    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "pitchEventId") {
            std::string id = GetCodeStr(Score, child);
            if (id == "NOTE") {
                Note.Type = NOTE;
            } else if (id == "TRILL") {
                Note.Type = TRILL;
            } else if (id == "CHORD") {
                Note.Type = CHORD;
            } else {
                throw std::runtime_error("Invalid pitch event id");
            }
        } else if (type == "pitch") {
            TSNode pitch = ts_node_child(child, 0);
            AudioState SubState;
            SubState.Markov = MARKOV;
            SubState.Type = NOTE;
            SubState.Freq = PitchNode2Freq(Score, child);
            Note.SubStates.push_back(SubState);
        } else if (type == "pitches") {
            uint32_t pitchCount = ts_node_child_count(child);
            for (int j = 0; j < pitchCount; j++) {
                TSNode eventPitch = ts_node_child(child, j);
                std::string eventPitchId = ts_node_type(eventPitch);
                if (eventPitchId == "pitch") {
                    AudioState SubState;
                    SubState.Markov = MARKOV;
                    SubState.Type = NOTE;
                    SubState.Freq = PitchNode2Freq(Score, eventPitch);
                    Note.SubStates.push_back(SubState);
                }
            }

        } else if (type == "duration") {
            double duration = GetDurationFromNode(Score, child);
            Note.Duration = duration;
        } else if (type == "ACTION") {
            // TODO:
            continue;
        } else {
            throw std::runtime_error("Invalid note event");
        }
    }
    ProcessEventTime(Note);
    return Note;
}

// ─────────────────────────────────────
void Score::ProcessEventTime(MacroState &Event) {
    // Time
    if (Event.Index != 0) {
        int Index = Event.Index;
        double PsiK = 60.0f / m_ScoreStates[Index - 1].BPMExpected;
        double Tn = m_ScoreStates[Index - 1].OnsetExpected;
        double Tn1 = Event.OnsetExpected;
        double PhiN0 = Event.PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        Event.PhaseExpected = PhiN1;
        Event.IOIHatPhiN = (Tn1 - Tn) / PsiK;
        Event.IOIPhiN = (Tn1 - Tn) / PsiK;
    } else {
        Event.PhaseExpected = 0;
        Event.IOIHatPhiN = 0;
        Event.IOIPhiN = 0;
    }

    Event.BPMExpected = m_CurrentBPM;
}

// ─────────────────────────────────────
void Score::ProcessEvent(const std::string &Score, TSNode Node) {
    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        MacroState Event;
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        TSPoint Pos = ts_node_start_point(child);
        Event.Line = Pos.row + 1;
        if (type == "pitchEvent") {
            Event = PitchEvent(Score, child);
            m_PrevDuration = Event.Duration;
            m_LastOnset = Event.OnsetExpected;
            m_ScoreStates.push_back(Event);
        }
    }
}

// ─────────────────────────────────────
std::string Score::GetChildStringFromId(const std::string &Score, TSNode node, std::string id) {
    int child_count = ts_node_child_count(node);
    for (int i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(node, i);
        const char *type = ts_node_type(child);
        if (id == type) {
            return GetCodeStr(Score, child);
        }
    }
    return "";
}

// ─────────────────────────────────────
void Score::ProcessConfig(const std::string &Score, TSNode Node) {
    MacroState Event;
    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "numberConfig") {
            std::string configType = GetChildStringFromId(Score, child, "configId");
            std::string number = GetChildStringFromId(Score, child, "numberSet");
            if (configType == "BPM") {
                m_CurrentBPM = std::stof(number);
            } else if (type == "TRANSPOSE") {
                m_Transpose = std::stof(number);
            }
        }
    }
}

// ─────────────────────────────────────
void Score::ParseInput(const std::string &Score) {
    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_scofo());
    TSTree *tree = ts_parser_parse_string(parser, nullptr, Score.c_str(), Score.size());
    TSNode rootNode = ts_tree_root_node(tree);

    uint32_t child_count = ts_node_child_count(rootNode);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(rootNode, i);
        std::string type = ts_node_type(child);
        if (type == "EVENT") {
            if (m_CurrentBPM == -1) {
                throw std::runtime_error("BPM is not defined");
            }
            ProcessEvent(Score, child);
        } else if (type == "CONFIG") {
            ProcessConfig(Score, child);
        }
    }

    // Cleanup
    ts_tree_delete(tree);
    ts_parser_delete(parser);
}

// ─────────────────────────────────────
States Score::Parse(std::string ScoreFile) {
    m_ScoreStates.clear();

    // Open the score file for reading
    std::ifstream File(ScoreFile);
    if (!File) {
        throw std::runtime_error("Score File not found");
    }

    m_CurrentBPM = -1;
    m_LineCount = 0;
    m_MarkovIndex = 0;
    m_ScorePosition = 0;
    m_LastOnset = 0;
    m_PrevDuration = 0;
    std::string Line;
    double LastOnset = 0;
    double PreviousDuration = 0;

    // read and process score
    std::string Score = std::string((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    ParseInput(Score);

    m_ScoreLoaded = true;
    return m_ScoreStates;
}
} // namespace OScofo
