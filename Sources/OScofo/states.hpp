#pragma once

#include <string>
#include <vector>

namespace OScofo {

enum EventType {
    REST,  // Markov state
    NOTE,  // MacroState, Semimarkov with Markov inside
    CHORD, // MacroState,
    TRILL, // MacroState, SemiMarkov with Markov inside
    MULTI, // MacroState,
};

enum HMMType { SEMIMARKOV, MARKOV };

// ─────────────────────────────────────
class SubState {
  public:
    EventType Type;
    HMMType Markov;
    double Freq;
    std::vector<double> Obs;
    std::vector<double> AlphaT;
};

// ─────────────────────────────────────
class MacroState {
  public:
    int Index;
    int ScorePos;
    EventType Type;
    HMMType Markov;
    int MarkovIndex = -1;

    // Forward Algorithm
    double InitProb;
    std::vector<double> Obs;
    std::vector<double> Forward;
    // std::vector<double> Norm;
    // std::vector<double> In;

    // Audio Obs
    std::vector<double> Freqs;

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
    int Line;

    std::string __repr__() const {
        std::string oss;
        oss = "<<State(Index=";
        oss += std::to_string(Index);
        oss += ", ScorePosition=";
        oss += std::to_string(ScorePos);
        oss += ", BPMExpected=";
        oss += std::to_string(BPMExpected);
        oss += ")>>";
        return oss;
    }
};

using States = std::vector<MacroState>;

// ─────────────────────────────────────
class Description {
  public:
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
} // namespace OScofo
