#pragma once

#include <string>
#include <vector>

enum EventType {
    SILENCE = 0,
    NOTE,
    // TODO: Add more events
};

// ─────────────────────────────────────
struct State {
    int Id;
    int Type; // NOTE, CHORD, PIZZ, SILENCE
    double Freq;

    // Time
    double BPMExpected;
    double BPMObserved;
    double OnsetExpected;
    double OnsetObserved;
    double PhaseExpected;
    double PhaseObserved;

    // double IOIPhaseExpected;
    // double IOIPhaseObserved;
    double IOIPhiN;
    double IOIHatPhiN;
    double Duration;

    // Error Handling
    bool Valid;
    int Line;
    std::string Error;
};
using States = std::vector<State>;

// ─────────────────────────────────────
struct Description {
    bool PassTreshold;

    double WindowSize;
    double Sr;
    double Freq;
    double Midi;
    double Quality;
    double dB;
    std::vector<double> SpectralPower;
    std::vector<double> NormSpectralPower;
    double TotalPower;
    double MaxAmp;
    double SpectralFlatness;
};
