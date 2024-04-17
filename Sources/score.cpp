#include "follower.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

// ==============================================
FollowerMDP::State FollowerScore::AddNote(FollowerMDP::State State,
                                          std::vector<std::string> tokens,
                                          float bpm, int lineCount) {
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
        int midi = Follower_NoteName2Midi(noteName);
        State.Midi = midi;
    } else {
        State.Midi = std::stof(tokens[1]);
        if (State.Midi > 127) {
            State.Midi = State.Midi * 0.01;
        }
    }

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
        State.Duration = std::stoi(tokens[2]);
    }

    State.Valid = true;
    return State;
}

// ==============================================
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
            State = AddNote(State, tokens, bpm, lineCount);
            if (!State.Valid) {
                pd_error(NULL, "Error adding note on line %d", lineCount);
                return;
            }
            if (bpm == -1) {
                pd_error(NULL, "BPM not defined");
                return;
            }
            MDP->States.push_back(State);

        } else if (tokens[0] == "BPM") {
            bpm = std::stof(tokens[1]);
        }
    }
    return;
}
