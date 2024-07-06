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

// ─────────────────────────────────────
State OScofoScore::AddNote(State State, std::vector<std::string> Tokens, double BPM,
                           int lineCount) {
    double Midi;
    if (BPM == -1) {
        State.Valid = false;
        State.Error = "BPM not defined";
        return State;
    }
    if (Tokens.size() < 3) {
        State.Valid = false;
        State.Error = "Invalid note on line " + std::to_string(lineCount);
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
void OScofoScore::Parse(States &States, const char *ScoreFile) {
    LOGE() << "start OScofoScore::Parse";

    States.clear();

    m_ScoreLoaded = false;
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
            State = AddNote(State, Tokens, BPM, LineCount);
            if (!State.Valid) {
                return;
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
    m_ScoreLoaded = true;

    LOGE() << "end OScofoScore::Parse | There is " << States.size() << " events";
    return;
}
