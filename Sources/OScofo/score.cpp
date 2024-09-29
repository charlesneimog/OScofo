#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

#include "log.hpp"
#include "score.hpp"

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
MacroState Score::AddNote(States &ScoreStates, std::vector<std::string> Tokens) {
    double Midi;
    bool isRest = false;

    MacroState NoteState;
    NoteState.Line = m_LineCount;
    NoteState.Type = NOTE;
    NoteState.Markov = SEMIMARKOV;
    NoteState.Index = ScoreStates.size();
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
        if (Midi == 0) {
            isRest = true;
        } else if (Midi > 127) {
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
        double PsiK = 60.0f / ScoreStates[Index - 1].BPMExpected;
        double Tn = ScoreStates[Index - 1].OnsetExpected;
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

    if (!isRest) {
        m_ScorePosition++;
    }

    return NoteState;
}

// ─────────────────────────────────────
// MacroState OScofoScore::AddChord(States &ScoreStates, std::vector<std::string> Tokens) {
//     // TODO:
//     return;
// }
//
// // ─────────────────────────────────────
// MacroState OScofoScore::AddTrill(States &ScoreStates, std::vector<std::string> Tokens) {
//     // TODO:
//     return;
// }
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
void Score::ParseInput(const std::string &input) {
    TSParser *Parser = ts_parser_new();
    ts_parser_set_language(Parser, tree_sitter_score());
    TSTree *Tree = ts_parser_parse_string(Parser, nullptr, input.c_str(), input.size());
    TSNode RootNode = ts_tree_root_node(Tree);
    PrintTreeSitterNode(RootNode);

    // núcleo
    uint32_t child_count = ts_node_child_count(RootNode);
    for (uint32_t i = 0; i < child_count; i++) {
        TSNode child = ts_node_child(RootNode, i);
        std::string Type = ts_node_type(child);

        // Verifica se é um nó de erro
        if (Type == "ERROR") {
            std::cerr << "Erro de sintaxe encontrado: " << ts_node_string(child) << std::endl;
        } else if (Type == "EVENT") {
            TSNode Event = ts_node_child(RootNode, i);
            std::string EventType = ts_node_type(Event);
            if (EventType == "NOTE") {
            }
        }
    }

    // Limpeza
    ts_tree_delete(Tree);
    ts_parser_delete(Parser);
}

// ─────────────────────────────────────
States Score::Parse(std::string ScoreFile) {
    LOGE() << "start OScofoScore::Parse";

    States NewStates;

    // Open the score file for reading
    std::ifstream File(ScoreFile);
    if (!File) {
        throw std::runtime_error("Score File not found");
    }

    std::ifstream file(ScoreFile);
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Parse the input using Tree-sitter
    //ParseInput(input);

    m_CurrentBPM = -1;
    m_LineCount = 0;
    m_MarkovIndex = 0;
    m_ScorePosition = 1;
    m_LastOnset = 0;
    m_PrevDuration = 0;

    std::string Line;
    double LastOnset = 0;
    double PreviousDuration = 0;

    // Process Score
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
            // Initial Silence
            if (m_ScorePosition == 1) {
            }

            // Actually Score
            if (Tokens[0] == "NOTE") {
                MacroState NewNote = AddNote(NewStates, Tokens);
                NewStates.push_back(NewNote);
            } else if (Tokens[0] == "BPM") {
                m_CurrentBPM = std::stof(Tokens[1]);
                MacroState Implicity;
                Implicity.Type = REST;
                Implicity.Markov = MARKOV;
                Implicity.BPMExpected = m_CurrentBPM;
                Implicity.ScorePos = 0;
                Implicity.Duration = 0;
                Implicity.Index = 0;
                NewStates.push_back(Implicity);
            }
            m_MarkovIndex++;
        }
    }

    m_ScoreLoaded = true;
    LOGE() << "end OScofoScore::Parse | There are " << NewStates.size() << " events";
    return NewStates;
}
} // namespace OScofo
