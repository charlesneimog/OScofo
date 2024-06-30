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
FollowerMDP::m_State FollowerScore::AddNote(FollowerMDP::m_State State, std::vector<std::string> tokens,
                                          float BPM, int lineCount) {
    float Midi;
    if (BPM== -1) {
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
        Midi = midi;
    } else {
        Midi = std::stof(tokens[1]);
        if (Midi > 127) {
            Midi = Midi * 0.01;
        }
    }
    State.Freq = m_Tunning * std::pow(2, (Midi - 69) / 12);

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
    State.BPM = BPM;
    State.Valid = true;

    return State;
}

// ╭─────────────────────────────────────╮
// │       Parse File of the Score       │
// ╰─────────────────────────────────────╯
void FollowerScore::Parse(FollowerMDP *MDP, const char *score) {
    LOGE() << "start FollowerScore::Parse";
    m_ScoreLoaded = false;
    std::ifstream File(score);
    if (!File) {
        pd_error(NULL, "File not found");
        return;
    }
    float BPM= -1;
    std::string Line;
    int LineCount = 0;
    float LastOnset = 0;
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
            FollowerMDP::m_State State;
            State.Type = NOTE;
            State.Id = MDP->GetStatesSize();
            State = AddNote(State, Tokens, BPM, LineCount);

            if (!State.Valid) {
                pd_error(NULL, "Error adding note on line %d", LineCount);
                return;
            }
            if (BPM== -1) {
                pd_error(NULL, "BPM not defined");
                return;
            }
            State.Onset = LastOnset + State.Duration; // in beats
            MDP->AddState(State);
            LastOnset = State.Onset;
                    

        } else if (Tokens[0] == "BPM") {
            BPM= std::stof(Tokens[1]);
        }
    }
    m_ScoreLoaded = true;
    LOGE() << "end FollowerScore::Parse";
    return;
}
