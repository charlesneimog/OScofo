#pragma once

#include <string>
#include <vector>

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

    double IOIPhaseExpected;
    double IOIPhaseObserved;
    double IOIPhiN;
    double IOIHatPhiN;
    double Duration;

    // Error Handling
    bool Valid;
    std::string Error;
};
using States = std::vector<State>;

// ─────────────────────────────────────
enum EventType {
    SILENCE = 0,
    NOTE,
    // TODO: Add more events
};
