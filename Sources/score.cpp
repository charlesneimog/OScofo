#include "follower.hpp"

#include <algorithm>
#include <fstream>
#include <math.h>
#include <sstream>

// ==============================================
float FollowerScore::midi2freq(float note) { return tunning * pow(2.0, (note - 69) / 12.0); }
float FollowerScore::freq2midi(float freq) { return 69 + 12 * log2(freq / tunning); }

// ==============================================
int FollowerScore::NoteName2Midi(std::string note) {
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
        pd_error(NULL, "Invalid note name for %s", note.c_str());
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
            pd_error(NULL, "Invalid note name for %s", note.c_str());
            return -1;
        }
    } else {
        if (std::isdigit(note[1])) {
            int octave = std::stoi(note.substr(1));
            int midi = classNote + 12 + (12 * octave);
        } else {
            pd_error(NULL, "Invalid note name for %s", note.c_str());
            return -1;
        }
    }
    return -1;
}

// ==============================================
int FollowerScore::AddNote(std::vector<std::string> tokens, float bpm, int lineCount) {
    State state = State();

    if (bpm == -1) {
        pd_error(NULL, "BPM not defined");
        return -1;
    }
    if (tokens.size() < 3) {
        pd_error(NULL, "Invalid note on line");
        return -1;
    }
    state.id = MDP.states.size() + 1;
    MDP.bpm.push_back(bpm);

    // check if pitch is a number os a string
    if (!std::isdigit(tokens[1][0])) {
        std::string noteName = tokens[1];
        int midi = NoteName2Midi(noteName);
        state.pitch = midi;
    } else {
        state.pitch = std::stof(tokens[1]);
        if (state.pitch > 127) {
            state.pitch = state.pitch * 0.01;
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
        state.duration = numerator / denominator;
    } else {
        state.duration = std::stoi(tokens[2]);
    }
    state.quality = 0.0f;
    MDP.states.push_back(state);

    return 0;
}

// ==============================================
void FollowerScore::Parse(const char *score) {
    // check if file exists
    std::ifstream file(score);
    if (!file) {
        pd_error(NULL, "File not found");
        return;
    }

    float bpm = -1;
    MDP = MarkovDecisionProcess();

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
            AddNote(tokens, bpm, lineCount);
            if (bpm == -1) {
                return;
            }

        } else if (tokens[0] == "BPM") {
            bpm = std::stof(tokens[1]);
        }
    }

    return;
}
