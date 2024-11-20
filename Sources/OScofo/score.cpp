#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

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
MacroState Score::AddNote(std::vector<std::string> Tokens) {
    m_ScorePosition++;
    double Midi;
    MacroState NoteState;
    NoteState.Line = m_LineCount;
    NoteState.Type = NOTE;
    NoteState.Markov = SEMIMARKOV;
    NoteState.Index = m_ScoreStates.size();
    NoteState.ScorePos = m_ScorePosition;

    if (m_MarkovIndex != 0) {
        NoteState.OnsetExpected = m_LastOnset + m_PrevDuration * (60 / m_CurrentBPM); // in Seconds
    } else {
        NoteState.OnsetExpected = 0;
    }

    if (m_CurrentBPM == -1) {
        throw std::runtime_error("BPM is not defined");
    }
    if (Tokens.size() < 3) {
        throw std::runtime_error("Invalid note on line " + std::to_string(m_LineCount) + ". Need at least 3 tokens");
    }

    // check if pitch is a number os a string
    if (!std::isdigit(Tokens[1][0])) {
        std::string noteName = Tokens[1];
        Midi = Name2Midi(noteName);
    } else {
        Midi = std::stof(Tokens[1]);
        if (Midi > 127) {
            Midi = Midi * 0.01;
        }
    }
    NoteState.Freqs.push_back(m_Tunning * std::pow(2, (Midi - 69) / 12));

    // Duration and tempo
    bool isRatio = Tokens[2].find('/') != std::string::npos;
    if (isRatio) {
        std::string ratio = Tokens[2];
        std::replace(ratio.begin(), ratio.end(), '/', ' ');
        std::istringstream iss(ratio);
        std::vector<std::string> ratioTokens;
        std::string token;
        while (std::getline(iss, token, ' ')) {
            ratioTokens.push_back(token);
        }
        double numerator = std::stof(ratioTokens[0]);
        double denominator = std::stof(ratioTokens[1]);
        NoteState.Duration = numerator / denominator;
    } else {
        NoteState.Duration = std::stof(Tokens[2]);
    }

    if (NoteState.Index != 0) {
        int Index = NoteState.Index;
        double PsiK = 60.0f / m_ScoreStates[Index - 1].BPMExpected;
        double Tn = m_ScoreStates[Index - 1].OnsetExpected;
        double Tn1 = NoteState.OnsetExpected;
        double PhiN0 = NoteState.PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        NoteState.PhaseExpected = PhiN1;
        NoteState.IOIHatPhiN = (Tn1 - Tn) / PsiK;
        NoteState.IOIPhiN = (Tn1 - Tn) / PsiK;
    } else {
        NoteState.PhaseExpected = 0;
        NoteState.IOIHatPhiN = 0;
        NoteState.IOIPhiN = 0;
    }

    // time phase
    NoteState.BPMExpected = m_CurrentBPM;

    // Add values
    m_PrevDuration = NoteState.Duration;
    m_LastOnset = NoteState.OnsetExpected;
    return NoteState;
}

// ─────────────────────────────────────
MacroState Score::AddTrill(std::vector<std::string> Tokens) {
    m_ScorePosition++;
    double Midi;
    MacroState TrillState;
    TrillState.Line = m_LineCount;
    TrillState.Type = TRILL;
    TrillState.Markov = SEMIMARKOV;
    TrillState.Index = m_ScoreStates.size();
    TrillState.ScorePos = m_ScorePosition;

    if (m_MarkovIndex != 0) {
        TrillState.OnsetExpected = m_LastOnset + m_PrevDuration * (60 / m_CurrentBPM); // in Seconds
    } else {
        TrillState.OnsetExpected = 0;
    }

    if (m_CurrentBPM == -1) {
        throw std::runtime_error("BPM is not defined");
    }
    if (Tokens.size() < 3) {
        throw std::runtime_error("Invalid trill on line " + std::to_string(m_LineCount) + ". Need at least 3 tokens");
    }

    // check if Tokens[1][0] is a parenthesis
    int TimeIndex = 1;
    if (Tokens[1][0] == '(') {
        for (int i = 1; i < Tokens.size(); i++) {
            std::string str = Tokens[i];
            str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return c == '(' || c == ')'; }), str.end());
            std::string pitch = str;
            if (!std::isdigit(pitch[0])) {
                std::string noteName = pitch;
                Midi = Name2Midi(noteName);
            } else {
                Midi = std::stof(pitch);
                if (Midi > 127) {
                    Midi = Midi * 0.01;
                }
            }
            TrillState.Freqs.push_back(m_Tunning * std::pow(2, (Midi - 69) / 12));
            if (Tokens[i].find(')') != std::string::npos) {
                TimeIndex = i + 1;
                break;
            }
        }
    }

    // Duration and tempo
    bool isRatio = Tokens[TimeIndex].find('/') != std::string::npos;

    if (isRatio) {
        std::string ratio = Tokens[TimeIndex];
        std::replace(ratio.begin(), ratio.end(), '/', ' ');
        std::istringstream iss(ratio);
        std::vector<std::string> ratioTokens;
        std::string token;
        while (std::getline(iss, token, ' ')) {
            ratioTokens.push_back(token);
        }
        double numerator = std::stof(ratioTokens[0]);
        double denominator = std::stof(ratioTokens[1]);
        TrillState.Duration = numerator / denominator;
    } else {
        TrillState.Duration = std::stof(Tokens[TimeIndex]);
    }

    printf("trill duration %f\n", TrillState.Duration);

    if (TrillState.Index != 0) {
        int Index = TrillState.Index;
        double PsiK = 60.0f / m_ScoreStates[Index - 1].BPMExpected;
        double Tn = m_ScoreStates[Index - 1].OnsetExpected;
        double Tn1 = TrillState.OnsetExpected;
        double PhiN0 = TrillState.PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        TrillState.PhaseExpected = PhiN1;
        TrillState.IOIHatPhiN = (Tn1 - Tn) / PsiK;
        TrillState.IOIPhiN = (Tn1 - Tn) / PsiK;
    } else {
        TrillState.PhaseExpected = 0;
        TrillState.IOIHatPhiN = 0;
        TrillState.IOIPhiN = 0;
    }

    // time phase
    TrillState.BPMExpected = m_CurrentBPM;

    // Add values
    m_PrevDuration = TrillState.Duration;
    m_LastOnset = TrillState.OnsetExpected;
    return TrillState;
}

// ─────────────────────────────────────
MacroState Score::AddRest(std::vector<std::string> Tokens) {
    double Midi;

    MacroState RestState;
    RestState.Line = m_LineCount;
    RestState.Type = REST;
    RestState.Markov = SEMIMARKOV;
    RestState.Index = m_ScoreStates.size();
    RestState.ScorePos = m_ScorePosition;

    if (m_MarkovIndex != 0) {
        RestState.OnsetExpected = m_LastOnset + m_PrevDuration * (60 / m_CurrentBPM); // in Seconds
    } else {
        RestState.OnsetExpected = 0;
    }

    if (m_CurrentBPM == -1) {
        throw std::runtime_error("BPM is not defined");
    }
    if (Tokens.size() < 2) {
        throw std::runtime_error("Invalid note on line " + std::to_string(m_LineCount) + ". Need at least 3 tokens");
    }

    // Duration and tempo
    bool isRatio = Tokens[1].find('/') != std::string::npos;
    if (isRatio) {
        std::string ratio = Tokens[1];
        std::replace(ratio.begin(), ratio.end(), '/', ' ');
        std::istringstream iss(ratio);
        std::vector<std::string> ratioTokens;
        std::string token;
        while (std::getline(iss, token, ' ')) {
            ratioTokens.push_back(token);
        }
        double numerator = std::stof(ratioTokens[0]);
        double denominator = std::stof(ratioTokens[1]);
        RestState.Duration = numerator / denominator;
    } else {
        RestState.Duration = std::stof(Tokens[1]);
    }

    if (RestState.Index != 0) {
        int Index = RestState.Index;
        double PsiK = 60.0f / m_ScoreStates[Index - 1].BPMExpected;
        double Tn = m_ScoreStates[Index - 1].OnsetExpected;
        double Tn1 = RestState.OnsetExpected;
        double PhiN0 = RestState.PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        RestState.PhaseExpected = PhiN1;
        RestState.IOIHatPhiN = (Tn1 - Tn) / PsiK;
        RestState.IOIPhiN = (Tn1 - Tn) / PsiK;
    } else {
        RestState.PhaseExpected = 0;
        RestState.IOIHatPhiN = 0;
        RestState.IOIPhiN = 0;
    }

    // time phase
    RestState.BPMExpected = m_CurrentBPM;

    // Add values
    m_PrevDuration = RestState.Duration;
    m_LastOnset = RestState.OnsetExpected;

    return RestState;
}

// ─────────────────────────────────────
// MacroState OScofoScore::AddChord(States &ScoreStates, std::vector<std::string> Tokens) {
//     // TODO:
//     return;
// }
//
//
// // ─────────────────────────────────────
// MacroState OScofoScore::AddMulti(States &ScoreStates, std::vector<std::string> Tokens) {
//     // TODO:
//     return;
// }
//
// // ─────────────────────────────────────
// MacroState OScofoScore::AddRest(States &ScoreStates, std::vector<std::string> Tokens) {
//     // TODO:
//     return;
// }
//
// ─────────────────────────────────────
void Score::AddAction(std::vector<std::string> Tokens) {

    for (auto Token : Tokens) {
        // printf("%s ", Token.c_str());
    }
    printf("\n");
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
void Score::PrintTreeSitterNode(TSNode node, int indent) {
    const char *type = ts_node_type(node);
    std::string text = ts_node_string(node);
    if (indent != 0) {
        std::cout << std::string(indent, ' ') << type << ": " << text << std::endl;
    }

    uint32_t child_count = ts_node_child_count(node);
    for (uint32_t i = 0; i < child_count; i++) {
        PrintTreeSitterNode(ts_node_child(node, i), indent + 4); // Aumenta a indentação para filhos
    }
}

// ─────────────────────────────────────
std::string Score::GetCodeStr(TSNode Node) {
    int start = ts_node_start_byte(Node);
    int end = ts_node_end_byte(Node);
    return std::string(std::string_view(m_TxtInput.data() + start, end - start));
}

// ─────────────────────────────────────
int Score::ProcessNote(TSNode Node) {
    TSNode pitchNode = ts_node_child_by_field_name(Node, "midi", 4);
    TSNode durationNode = ts_node_child_by_field_name(Node, "duration", 8);
    if (ts_node_is_null(pitchNode)) {
        throw std::runtime_error("Pitch definition not found");
    } else if (ts_node_is_null(durationNode)) {
        throw std::runtime_error("Duration definition not found");
    }
    std::string notetype = ts_node_type(pitchNode);
    std::string durtype = ts_node_type(durationNode);
    printf("note type: %s\n", notetype.c_str());
    printf("duration type: %s\n", durtype.c_str());

    return 0;
}

// ─────────────────────────────────────
void Score::ParseInput() {
    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_score());
    TSTree *tree = ts_parser_parse_string(parser, nullptr, m_TxtInput.c_str(), m_TxtInput.size());
    TSNode rootNode = ts_tree_root_node(tree);
    PrintTreeSitterNode(rootNode, 0);

    uint32_t child_count = ts_node_child_count(rootNode);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(rootNode, i);
        std::string type = ts_node_type(child);
        if (type == "note_declaration") {
            ProcessNote(child);
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

    // Parse the input using Tree-sitter
    // ParseInput();

    m_CurrentBPM = -1;
    m_LineCount = 0;
    m_MarkovIndex = 0;
    m_ScorePosition = 0;
    m_LastOnset = 0;
    m_PrevDuration = 0;

    std::string Line;
    double LastOnset = 0;
    double PreviousDuration = 0;

    // for test
    File.clear();
    File.seekg(0, std::ios::beg);

    while (std::getline(File, Line)) {
        m_LineCount++;

        // comments
        if (Line.empty() || Line[0] == '#' || Line[0] == ';') {
            continue;
        }

        std::istringstream iss(Line);
        std::string Token;
        std::vector<std::string> Tokens;
        while (std::getline(iss, Token, ' ')) {
            Tokens.push_back(Token);
        }

        // check if line is a tab line (for actions)
        if (Line[0] == '\t' || SpaceTab(Line, 2) || SpaceTab(Line, 4)) {
            AddAction(Tokens);
        } else {
            if (m_ScorePosition == 1) {
            }

            // Actually Score
            if (Tokens[0] == "NOTE") {
                MacroState NewNote = AddNote(Tokens);
                m_ScoreStates.push_back(NewNote);
            } else if (Tokens[0] == "BPM") {
                m_CurrentBPM = std::stof(Tokens[1]);
                // add first Silence event
            } else if (Tokens[0] == "REST") {
                // MacroState NewRest = AddRest(Tokens);
                // m_ScoreStates.push_back(NewRest);
            } else if (Tokens[0] == "TRILL") {
                MacroState NewTrill = AddTrill(Tokens);
                m_ScoreStates.push_back(NewTrill);
            }
            m_MarkovIndex++;
        }
    }

    m_ScoreLoaded = true;
    return m_ScoreStates;
}
} // namespace OScofo
