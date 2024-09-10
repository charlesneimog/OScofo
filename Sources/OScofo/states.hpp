#pragma once

#include <complex>
#include <string>
#include <vector>

enum EventType {
    TRANSITION = -1,
    SILENCE = 0,
    NOTE,
    // TODO: Add more events
};
enum HMMType { SEMIMARKOV = 0, MARKOV };

// ─────────────────────────────────────
struct State {
    int Index;
    int ScoreEventNumber;
    EventType Type;     // NOTE, CHORD, PIZZ, SILENCE
    HMMType MarkovType; // NOTE, CHORD, PIZZ, SILENCE
    int Position;
    std::vector<double> Freqs;

    // Time
    double BPMExpected;
    double BPMObserved;
    double PsiN;

    //
    double OnsetExpected;
    double OnsetObserved;
    double PhaseExpected;
    double PhaseObserved;

    double IOIPhiN;
    double IOIHatPhiN;
    double Duration;

    // Audio Observations
    std::vector<double> KLDiv;
    std::vector<double> AlphaT;

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
    std::vector<double> NormSpectralPower;
    std::vector<double> SpectralMag;
    std::vector<double> SpectralPhase;
    std::vector<double> SpectralPhaseMinus2;
    double TotalPower;
    double MaxAmp;

    // double SpectralFlatness;
};
