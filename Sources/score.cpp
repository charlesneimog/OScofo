#include "follower.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

#define ACCUMULATION_FACTOR 1 // TODO: define by user

// clang-format off

// TODO: Add SECTION word, for example, "SECTION B" will start a score after the SECTION B event
// TODO: Add EVENT (This must get a duration) and output one timer with it, for example, in 10000ms, a timer from 0 to 10000ms
// TODO: ADD CHORD, MULTI, etc.
// TODO: ADD EXTENDED TECHNIQUES @pizz, @multiphonic,


// ─────────────────────────────────────
FollowerMDP::State FollowerScore::AddNote(FollowerMDP::State State, std::vector<std::string> tokens,
                                          float bpm, int lineCount) {
    K = 1;
    if (bpm == -1) {
        pd_error(NULL, "BPM not defined");
        return State;
    }
    if (tokens.size() < 3) {
        pd_error(NULL, "Invalid note on line");
        return State;
    }

    // check if pitch is a number os a string
    if (!std::isdigit(tokens[1][0])) {
        std::string noteName = tokens[1];
        int midi = Name2Midi(noteName);
        State.Midi = midi;
    } else {
        State.Midi = std::stof(tokens[1]);
        if (State.Midi > 127) {
            State.Midi = State.Midi * 0.01;
        }
    }
    State.Freq = Tunning * std::pow(2, (State.Midi - 69) / 12);

    // check if there is / in the string
    bool isRatio = tokens[2].find('/') != std::string::npos;
    if (isRatio) {
        std::string ratio = tokens[2];
        std::replace(ratio.begin(), ratio.end(), '/', ' ');
        std::istringstream iss(ratio);
        std::vector<std::string> ratioTokens;
        std::string token;
        while (std::getline(iss, token, ' ')) {
            ratioTokens.push_back(token);
        }
        float numerator = std::stof(ratioTokens[0]);
        float denominator = std::stof(ratioTokens[1]);
        State.Duration = numerator / denominator;
    } else {
        State.Duration = std::stof(tokens[2]);
    }

    // time phase
    State.Bpm = bpm;
    State.Valid = true;

    return State;
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
void FollowerScore::Parse(FollowerMDP *MDP, const char *score) {
    // check if file exists
    std::ifstream file(score);
    if (!file) {
        pd_error(NULL, "File not found");
        return;
    }
    float bpm = -1;
    std::string line;
    int lineCount = 0;
    float LastOnset = 0;
    while (std::getline(file, line)) {
        lineCount++;
        // parse line
        if (line[0] == '#' || line.empty() || line[0] == ';') {
            continue;
        }
        // parse line
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(iss, token, ' ')) {
            tokens.push_back(token);
        }

        if (tokens[0] == "NOTE") {
            FollowerMDP::State State;
            State.Type = NOTE;
            State.Id = MDP->GetStatesSize();
            if (State.Id == 0) {
                MDP->SetLiveBpm(bpm);
            }

            State = AddNote(State, tokens, bpm, lineCount);

            if (!State.Valid) {
                pd_error(NULL, "Error adding note on line %d", lineCount);
                return;
            }
            if (bpm == -1) {
                pd_error(NULL, "BPM not defined");
                return;
            }
            State.Onset = LastOnset + State.Duration;
            MDP->AddState(State);
            LastOnset = State.Onset;

        } else if (tokens[0] == "BPM") {
            bpm = std::stof(tokens[1]);
        }
    }

    return;
}
