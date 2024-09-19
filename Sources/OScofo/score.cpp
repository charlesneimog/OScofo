#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

#include "score.hpp"

#define ACCUMULATION_FACTOR 1 // TODO: define by user

// clang-format off

// TODO: Add SECTION word, for example, "SECTION B" will start a score after the SECTION B event
// TODO: Add EVENT (This must get a duration) and output one timer with it, for example, in 10000ms, a timer from 0 to 10000ms
// TODO: ADD CHORD, MULTI, etc.
// TODO: ADD EXTENDED TECHNIQUES @pizz, @multiphonic,
// clang-format on

void OScofoScore::SetTunning(double Tunning) {
    m_Tunning = Tunning;
}
bool OScofoScore::ScoreIsLoaded() {
    return m_ScoreLoaded;
}

// ╭─────────────────────────────────────╮
// │                Utils                │
// ╰─────────────────────────────────────╯
int OScofoScore::Name2Midi(std::string note) {
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
        // TODO: Need to implement pd_error
        // pd_error(NULL, "Invalid note name for %s", note.c_str());
        break;
        return -1;
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
            // pd_error(NULL, "Invalid note name for %s", note.c_str());
            return -1;
        }
    } else {
        if (std::isdigit(note[1])) {
            int octave = std::stoi(note.substr(1));
            int midi = classNote + 12 + (12 * octave);
        } else {
            // pd_error(NULL, "Invalid note name for %s", note.c_str());
            return -1;
        }
    }
    return -1;
}

// ─────────────────────────────────────
double OScofoScore::ModPhases(double Phase) {
    // Following Cont (2010) conventions
    Phase = fmod(Phase + M_PI, TWO_PI);
    if (Phase < 0) {
        Phase += TWO_PI;
    }
    return Phase - M_PI;
}

// ─────────────────────────────────────
void OScofoScore::AddTrans(States &ScoreStates, std::vector<std::string> Tokens) {
    return;
}

// ─────────────────────────────────────
void OScofoScore::AddNote(States &ScoreStates, std::vector<std::string> Tokens) {
    double Midi;

    State NoteState;
    NoteState.Line = m_LineCount;

    NoteState.Type = NOTE;
    NoteState.Markov = SEMIMARKOV;

    NoteState.Index = ScoreStates.size();
    NoteState.Position = m_ScorePosition;

    if (m_MarkovIndex != 0) {
        NoteState.OnsetExpected = m_LastOnset + m_PrevDuration * (60 / m_CurrentBPM); // in Seconds

    } else {
        NoteState.OnsetExpected = 0;
    }

    if (m_CurrentBPM == -1) {
        throw std::runtime_error("BPM is not defined");
    }
    if (Tokens.size() < 3) {
        throw std::runtime_error("Invalid note on line " + std::to_string(m_LineCount));
    }

    // check if pitch is a number os a string
    if (!std::isdigit(Tokens[1][0])) {
        std::string noteName = Tokens[1];
        int midi = Name2Midi(noteName);
        Midi = midi;
    } else {
        Midi = std::stof(Tokens[1]);
        if (Midi > 127) {
            Midi = Midi * 0.01;
        }
    }
    NoteState.Freqs.push_back(m_Tunning * std::pow(2, (Midi - 69) / 12));

    // check if there is / in the string
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
    NoteState.Valid = true;

    m_PrevDuration = NoteState.Duration;
    m_LastOnset = NoteState.OnsetExpected;
    ScoreStates.push_back(NoteState);

    // State TransState;
    // TransState.Type = SILENCE;
    // TransState.Markov = MARKOV;
    // TransState.BPMExpected = m_CurrentBPM;
    // TransState.Valid = true;
    // TransState.Freqs = NoteState.Freqs;
    // TransState.Position = m_ScorePosition;
    // TransState.Duration = 0;
    // ScoreStates.push_back(TransState);

    return;
}

// ─────────────────────────────────────
void OScofoScore::AddChord(States &ScoreStates, std::vector<std::string> Tokens) {
    // TODO:
    return;
}

// ─────────────────────────────────────
void OScofoScore::AddTrill(States &ScoreStates, std::vector<std::string> Tokens) {
    // TODO:
    return;
}

// ─────────────────────────────────────
void OScofoScore::AddMulti(States &ScoreStates, std::vector<std::string> Tokens) {
    // TODO:
    return;
}

// ─────────────────────────────────────
void OScofoScore::AddRest(States &ScoreStates, std::vector<std::string> Tokens) {
    // TODO:
    return;
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
void OScofoScore::Parse(States &States, std::string ScoreFile) {
    LOGE() << "start OScofoScore::Parse";

    States.clear(); // Clear the vector before parsing

    // Open the score file for reading
    std::ifstream File(ScoreFile);
    if (!File) {
        throw std::runtime_error("Score File not found");
    }

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
        if (Line[0] == '#' || Line.empty() || Line[0] == ';') {
            continue;
        }

        std::istringstream iss(Line);
        std::string Token;
        std::vector<std::string> Tokens;

        while (std::getline(iss, Token, ' ')) {
            Tokens.push_back(Token);
        }

        // Initial Silence
        if (m_ScorePosition == 1) {
        }

        // Actually Score
        if (Tokens[0] == "NOTE") {
            AddNote(States, Tokens);
            m_ScorePosition++;

        } else if (Tokens[0] == "BPM") {
            m_CurrentBPM = std::stof(Tokens[1]);
            State Implicity;
            Implicity.Type = REST;
            Implicity.Markov = MARKOV;
            Implicity.BPMExpected = m_CurrentBPM;
            Implicity.Position = 0;
            Implicity.Duration = 0;
            States.push_back(Implicity);
        }
        m_MarkovIndex++;
    }

    // Optionally, set m_ScoreLoaded to true if necessary
    m_ScoreLoaded = true;
    LOGE() << "end OScofoScore::Parse | There are " << States.size() << " events";
}
