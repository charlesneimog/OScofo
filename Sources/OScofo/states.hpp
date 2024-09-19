#pragma once

#include <sstream>
#include <string>
#include <vector>

enum EventType {
    TRANSITION = -1,
    REST = 0,
    NOTE,
};
enum HMMType { SEMIMARKOV = 0, MARKOV };

// ─────────────────────────────────────
struct State {
    int Index;
    int Position;
    int Type;
    HMMType Markov;
    // Forward Algorithm
    double InitProb;
    std::vector<double> Obs;
    std::vector<double> AlphaT;

    // Observed
    double Alpha;

    // Audio
    std::vector<double> Freqs;

    // Observations

    // Time
    int UpperBound;
    double BPMExpected;
    double BPMObserved = 0;
    double OnsetExpected;
    double OnsetObserved = 0;
    double PhaseExpected;
    double PhaseObserved = 0;
    double IOIPhiN;
    double IOIHatPhiN;
    double Duration;

    // Error Handling
    bool Valid;
    int Line;
    std::string Error;

    std::string to_string() const {
        std::ostringstream oss;
        oss << "State(Index=" << Index << ", ScorePosition=" << Position << ", BPMExpected=" << BPMExpected << ")";
        return oss.str();
    }
};
using States = std::vector<State>;

// ─────────────────────────────────────
struct Description {
    bool Silence;
    double WindowSize;
    double Sr;
    double Freq;
    double Midi;
    double dB;
    double Amp;
    std::vector<double> SpectralPower;
    std::vector<double> NormSpectralPower;
    double TotalPower;
    double MaxAmp;
    double SpectralFlatness;
};
