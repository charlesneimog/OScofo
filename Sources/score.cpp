#include "follower.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

#define ACCUMULATION_FACTOR 1 // TODO: define by user

#define M_PI 3.14159265358979323846
#define TWO_PI (2 * M_PI)

// clang-format off

// TODO: Add SECTION word, for example, "SECTION B" will start a score after the SECTION B event
// TODO: Add EVENT (This must get a duration) and output one timer with it, for example, in 10000ms, a timer from 0 to 10000ms
// TODO: ADD CHORD, MULTI, etc.
// TODO: ADD EXTENDED TECHNIQUES @pizz, @multiphonic,


// ╭─────────────────────────────────────╮
// │             References              │
// ╰─────────────────────────────────────╯
/*
 * CONT, Arshia. Modeling Musical Anticipation: From the Time of Music to the Music of Time. 2008.

*/


// r = r - \eta_r \left[ r - \cos \left( 2\pi \frac{(t_n - t_{n-1} - \hat{\phi}_n)}{\psi_k} \right) \right]
// \kappa = A^{-1}_2 (r) \quad \text{(Table lookup)}

// clang-format on

// ─────────────────────────────────────
// double UpdateR(double r, double eta_r, double t_n, double t_n_1, double psi_k, double phi_n) {
//     return r - eta_r * (r - cos(2 * M_PI * (t_n - t_n_1) / psi_k - phi_n));
// }

// ─────────────────────────────────────
float New_R(float r, float eta, float t_n, float t_n1, float phi_n, float psi_k) {
    float r_hat = std::cos(TWO_PI * ((t_n - t_n1 / psi_k) - phi_n));
    float r_new = r - eta * (r - r_hat);
    return r - eta * (r - r_hat);
}

// ─────────────────────────────────────
float AttentionalFunction(float phi, float phi_mu, float kappa) {
    // (CONT, 2008, p. 134) eq 7.9.
    float cos_term = std::cos(TWO_PI * (phi - phi_mu));
    float sin_term = std::sin(TWO_PI * (phi - phi_mu));
    float exp_term = 1 / std::exp(kappa) * TWO_PI;
    float result = exp_term * std::exp(kappa * cos_term) * sin_term;
    return result;
}

// ─────────────────────────────────────
float FollowerScore::GetTimePhase(float t_n0, float t_n1, float phase0, float pulse) {
    float phi_n1 = phase0 + (t_n1 - t_n0) / pulse;
    phi_n1 = std::fmod(phi_n1 + 0.5, 1.0) - 0.5;
    return phi_n1;
}
// ─────────────────────────────────────
FollowerMDP::State FollowerScore::AddNote(FollowerMDP::State State, std::vector<std::string> tokens,
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
        int midi = Name2Midi(noteName);
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
        State.Duration = std::stof(tokens[2]);
    }

    // time phase
    float t_n0 = lastOnset;
    float t_n1 = t_n0 + State.Duration * 60000 / bpm;
    float phase0 = lastPhase;
    float pulse = 60000 / bpm;

    lastPhase = GetTimePhase(t_n0, t_n1, phase0, pulse);
    lastOnset = t_n1;

    State.TimePhase = lastPhase;
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
            State.Id = MDP->States.size();
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
            MDP->States.push_back(State);

        } else if (tokens[0] == "BPM") {
            bpm = std::stof(tokens[1]);
        }
    }

    return;
}
