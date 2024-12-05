#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "score.hpp"
#include "tree_sitter/api.h"

extern "C" TSLanguage *tree_sitter_score();

namespace OScofo {

// clang-format off
// TODO: Add SECTION word, for example, "SECTION B" will start a score after the SECTION B event
// TODO: Add EVENT (This must get a duration) and output one timer with it, for example, in 10000ms, a timer from 0 to 10000ms
// TODO: ADD CHORD, MULTI, etc.
// TODO: ADD EXTENDED TECHNIQUES @pizz, @multiphonic,
// clang-format on

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

// ╭─────────────────────────────────────╮
// │                Utils                │
// ╰─────────────────────────────────────╯
bool Score::SpaceTab(const std::string &line, int numSpaces) {
    std::string spaces(numSpaces, ' ');
    return line.find(spaces) != std::string::npos;
}

// ─────────────────────────────────────
int Score::Name2Midi(std::string note) {
    char noteName = note[0];
    int classNote = -1;
    switch (noteName) {
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
        throw std::runtime_error("Invalid note name for " + note);
    }

    if (note[1] == '#' || note[1] == 'b') {
        noteName = note[1];
        if (noteName == '#') {
            classNote++;
        } else {
            classNote--;
        }
        if (std::isdigit(note[2])) {
            int octave = std::stoi(note.substr(2));
            int midi = classNote + 12 + (12 * octave);
            return midi;
        } else {
            throw std::runtime_error("Invalid note name for " + note);
        }
    } else {
        if (std::isdigit(note[1])) {
            int octave = std::stoi(note.substr(1));
            int midi = classNote + 12 + (12 * octave);
            return midi;
        } else {
            throw std::runtime_error("Invalid note name for " + note);
        }
    }
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

// ─────────────────────────────────────
void Score::AddAction(std::vector<std::string> Tokens) {
    MacroState CurrentState = m_ScoreStates[m_ScoreStates.size() - 1];
    std::vector<std::string> Action;
    for (auto Token : Tokens) {
    }

    printf("\n");
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
std::string Score::GetCodeStr(TSNode Node) {
    int start = ts_node_start_byte(Node);
    int end = ts_node_end_byte(Node);
    return std::string(std::string_view(m_TxtInput.data() + start, end - start));
}

// ─────────────────────────────────────
double Score::GetFreqsFromNode(TSNode Node) {
    uint32_t count = ts_node_child_count(Node);
    if (count != 1) {
        throw std::runtime_error("Invalid pitch count");
    }

    TSNode pitch = ts_node_child(Node, 0);
    std::string pitch_type = ts_node_type(pitch);
    if (pitch_type == "midi") {
        std::string midi = GetCodeStr(pitch);
        double freq = m_Tunning * std::pow(2, (std::stof(midi) - 69) / 12);
        return freq;
    } else if (pitch_type == "pitchname") {
        std::string pitchname = GetCodeStr(pitch);
        float midi = Name2Midi(pitchname);
        double freq = m_Tunning * std::pow(2, (midi - 69) / 12);
        return freq;
    }
    throw std::runtime_error("Invalid pitch type");
}

// ─────────────────────────────────────
double Score::GetDurationFromNode(TSNode Node) {
    uint32_t count = ts_node_child_count(Node);
    if (count != 1) {
        throw std::runtime_error("Invalid duration count");
    }

    TSNode dur = ts_node_child(Node, 0);
    std::string dur_type = ts_node_type(dur);
    if (dur_type == "float" || dur_type == "integer") {
        std::string dur_str = GetCodeStr(dur);
        return std::stof(dur_str);
    }
    throw std::runtime_error("Invalid duration type");
}

// ─────────────────────────────────────
MacroState Score::NoteEvent(TSNode Node) {
    m_ScorePosition++;

    double Midi;
    MacroState Note;
    Note.Line = m_LineCount;
    Note.Type = NOTE;
    Note.Markov = SEMIMARKOV;
    Note.Index = m_ScoreStates.size();
    Note.ScorePos = m_ScorePosition;

    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "NOTE") {
            continue;
        } else if (type == "pitch") {
            AudioState SubState;
            SubState.Type = NOTE;
            SubState.Markov = MARKOV;
            SubState.Freq = GetFreqsFromNode(child);
            Note.SubStates.push_back(SubState);
        } else if (type == "duration") {
            double duration = GetDurationFromNode(child);
            Note.Duration = duration;
        } else {
            throw std::runtime_error("Invalid note event");
        }
    }
    return Note;
}

// ─────────────────────────────────────
MacroState Score::TrillEvent(TSNode Node) {
    m_ScorePosition++;

    MacroState Trill;
    double Midi;
    Trill.Line = m_LineCount;
    Trill.Type = TRILL;
    Trill.Markov = SEMIMARKOV;
    Trill.Index = m_ScoreStates.size();
    Trill.ScorePos = m_ScorePosition;

    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "TRILL") {
            continue;
        } else if (type == "pitches") {
            uint32_t pitches_count = ts_node_child_count(child);
            for (uint32_t i = 0; i < pitches_count; i++) {
                TSNode pitch = ts_node_child(child, i);
                std::string type = ts_node_type(pitch);
                if (type == "pitch" || type == "midi") {
                    AudioState SubState;
                    SubState.Type = NOTE;
                    SubState.Markov = MARKOV;
                    SubState.Freq = GetFreqsFromNode(pitch);
                    Trill.SubStates.push_back(SubState);
                }
            }
        } else if (type == "duration") {
            double duration = GetDurationFromNode(child);
            Trill.Duration = duration;
        } else {
            throw std::runtime_error("Invalid trill event");
        }
    }
    return Trill;
}

// ─────────────────────────────────────
void Score::ProcessEvent(TSNode Node) {
    MacroState Event;
    uint32_t child_count = ts_node_child_count(Node);

    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);

        if (type == "NOTE") {
            Event = NoteEvent(child);
            m_MarkovIndex++;
        } else if (type == "TRILL") {
            Event = TrillEvent(child);
            m_MarkovIndex++;
        } else if (type == "REST") {
            // NOT IMPLEMENTED
        } else {
            std::runtime_error("Invalid event type");
        }

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
        m_PrevDuration = Event.Duration;
        m_LastOnset = Event.OnsetExpected;
        m_ScoreStates.push_back(Event);
    }
}

// ─────────────────────────────────────
void Score::ProcessConfig(TSNode Node) {
    MacroState Event;
    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(Node, i);
        std::string type = ts_node_type(child);
        if (type == "BPM") {
            TSNode bpm = ts_node_child(child, 1);
            m_CurrentBPM = std::stof(GetCodeStr(bpm));
        } else if (type == "transpose" || type == "TRANSPOSE") {
        }
    }
}

// ─────────────────────────────────────
void Score::ParseInput() {
    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_score());
    TSTree *tree = ts_parser_parse_string(parser, nullptr, m_TxtInput.c_str(), m_TxtInput.size());
    TSNode rootNode = ts_tree_root_node(tree);

    uint32_t child_count = ts_node_child_count(rootNode);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(rootNode, i);
        std::string type = ts_node_type(child);
        if (type == "EVENT") {
            if (m_CurrentBPM == -1) {
                throw std::runtime_error("BPM is not defined");
            }
            ProcessEvent(child);
        } else if (type == "CONFIG") {
            ProcessConfig(child);
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
    m_TxtInput = std::string((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());

    m_CurrentBPM = -1;
    m_LineCount = 0;
    m_MarkovIndex = 0;
    m_ScorePosition = 0;
    m_LastOnset = 0;
    m_PrevDuration = 0;
    std::string Line;
    double LastOnset = 0;
    double PreviousDuration = 0;

    ParseInput();
    m_ScoreLoaded = true;
    return m_ScoreStates;
}
} // namespace OScofo
