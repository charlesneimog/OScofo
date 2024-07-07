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
State OScofoScore::AddNote(State &State, std::vector<std::string> Tokens, double BPM,
                           int LineCount) {
    double Midi;
    if (BPM == -1) {
        State.Valid = false;
        State.Error = "BPM not defined";
        return State;
    }
    if (Tokens.size() < 3) {
        State.Valid = false;
        State.Error = "Invalid note on line " + std::to_string(LineCount);
        return State;
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
    State.Freq = m_Tunning * std::pow(2, (Midi - 69) / 12);

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
        State.Duration = numerator / denominator;
    } else {
        State.Duration = std::stof(Tokens[2]);
    }
    // time phase
    State.BPMExpected = BPM;
    State.Valid = true;
    return State;
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
        State State;
        State.Valid = false;
        State.Error = "File not found";
        return;
    }

    double BPM = -1;
    std::string Line;
    int LineCount = 0;
    double LastOnset = 0;
    double Event = 0;
    double PreviousDuration = 0;

    while (std::getline(File, Line)) {
        LineCount++;
        if (Line[0] == '#' || Line.empty() || Line[0] == ';') {
            continue;
        }
        std::istringstream iss(Line);
        std::string Token;
        std::vector<std::string> Tokens;

        while (std::getline(iss, Token, ' ')) {
            Tokens.push_back(Token);
        }

        if (Tokens[0] == "NOTE") {
            State State;
            State.Type = NOTE;
            State.Id = States.size();
            State.Line = LineCount;
            State = AddNote(State, Tokens, BPM, LineCount);
            if (!State.Valid) {
                State.Error = "Error on line " + std::to_string(LineCount) + ": " + State.Error;
                States.push_back(State);
                continue;
            }
            if (Event != 0) {
                State.OnsetExpected = LastOnset + PreviousDuration * (60 / BPM); // in Seconds
            } else {
                State.OnsetExpected = 0;
            }
            Event++;
            States.push_back(State);
            PreviousDuration = State.Duration;
            LastOnset = State.OnsetExpected;

        } else if (Tokens[0] == "BPM") {
            BPM = std::stof(Tokens[1]);
        }
    }
    // Optionally, set m_ScoreLoaded to true if necessary
    m_ScoreLoaded = true;

    LOGE() << "end OScofoScore::Parse | There are " << States.size() << " events";
}