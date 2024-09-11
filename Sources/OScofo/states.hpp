#pragma once

#include <complex>
#include <string>
#include <vector>

enum EventType {
    SILENCE = 0,
    NOTE,
    ONSET,
    // TODO: Add more events
};

// ─────────────────────────────────────
struct State {
    int Index;
    EventType Type; // NOTE, CHORD, PIZZ, SILENCE
    std::vector<double> Freqs;

    // Time
    double BPMExpected;
    double BPMObserved;

    //
    double OnsetExpected;
    double OnsetObserved;
    double PhaseExpected;
    double PhaseObserved;

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
    double HalfWindowSize;
    double WindowSize;
    double Sr;
    double dB;

    // Silence
    bool PassTreshold; // what we consider silence
    bool Silence;
    bool SilenceLast;

    // FFT
    std::vector<std::complex<double>> FFTOut;
    // Mag
    std::vector<double> NormSpectralPower;
    double TotalPower;
    double MaxAmp;
    std::vector<double> SpectralMag;
    // Phase
    std::vector<double> SpectralPhase;
    std::vector<double> SpectralPhaseMinus2;

    // double SpectralFlatness;
};
