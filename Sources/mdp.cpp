#include "follower.hpp"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric> // for std::accumulate

#define MAX_FREQUENCY_DIFFERENCE 10.0
#define MAX_QUALITY_DIFFERENCE 0.5

// TEST:
double UpdateR(double r, double eta_r, double t_n_1, double t_n, double psi_k, double phi_n) {
    r = r - eta_r * (r - cos(2 * M_PI * (t_n - t_n_1) / psi_k - phi_n));
    return r;
}

// ─────────────────────────────────────
FollowerMDP::FollowerMDP() {
    Desc = new FollowerMIR::Description();
    BpmHistory.assign(20, 1);
}

// ─────────────────────────────────────
void FollowerMDP::SetMinQualityForNote(float minQuality) {
    MinQualityForNote = minQuality;
}

// ─────────────────────────────────────
float FollowerMDP::GetLiveBpm() {
    return LiveBpm;
}

// ─────────────────────────────────────
void FollowerMDP::SetLiveBpm(float Bpm) {
    LiveBpm = Bpm;
}

// ─────────────────────────────────────
void FollowerMDP::ResetLiveBpm() {
    BpmHistory.assign(20, 1);
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
float FollowerMDP::GetPitchSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {
    float NextMidi = NextPossibleState.Midi;
    float DescMidi = Desc->Midi;
    float NextFreq = Tunning * pow(2.0, (NextMidi - 69) / 12.0);
    float DescFreq = Desc->Freq;
    float Distance = abs(DescFreq - NextFreq);
    float Similarity = Distance / MAX_FREQUENCY_DIFFERENCE;
    if (Similarity > 1.0) {
        float OctaveDiff = abs(fmod(DescMidi, 12) - fmod(NextMidi, 12));
        if (OctaveDiff < 0.3) {
            return OctaveDiff;
        } else {
            return 0;
        }
    }

    Similarity = 1.0 - (Distance / MAX_FREQUENCY_DIFFERENCE);
    return Similarity;
}

// ─────────────────────────────────────
float FollowerMDP::GetTimeSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {

    float Similarity = 0.0;
    float CorrectedDur = NextPossibleState.Duration * (60000.0f / LiveBpm);

    if (CurrentEvent == NextPossibleState.Id || (CurrentEvent == -1 == NextPossibleState.Id == 0)) {
        float margin = 0.2f * Desc->TimeElapsed;
        float minTime = Desc->TimeElapsed - margin;
        float maxTime = Desc->TimeElapsed + margin;
        if (CorrectedDur >= minTime && CorrectedDur <= maxTime) {
            Similarity = 1.0f; // Adjust weight as needed
        } else {
            Similarity = 0.5f;
        }

    } else if (NextPossibleState.Id == CurrentEvent + 1) {
        float margin = 0.2f * Desc->TimeElapsed;
        float minTime = Desc->TimeElapsed - margin;
        float maxTime = Desc->TimeElapsed + margin;
        if (CorrectedDur >= minTime && CorrectedDur <= maxTime) {
            Similarity = 1.0f;
        } else {
            Similarity = 0.0f;
        }
    }
    return Similarity;
}

// ─────────────────────────────────────
float FollowerMDP::GetSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {
    float PitchWeight = 0.7;
    float TimeWeight = 0.3;

    float PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    // float TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc);

    float Similarity = PitchWeight * PitchSimilarity;

    return Similarity;
}

// ─────────────────────────────────────
float FollowerMDP::GetBestEvent(std::vector<State> States, FollowerMIR::Description *Desc) {
    float BestGuess = CurrentEvent;
    State CurState = States[CurrentEvent];

    float MaxSimilarity = -1;

    // 3 means that it just look for the next 3 events
    for (int i = CurrentEvent; i < (CurrentEvent + 3); i++) {
        if (i >= States.size() || i < 0) {
            continue;
        }
        State NextPossibleState = States[i];
        float Similarity = GetSimilarity(NextPossibleState, Desc);
        if (Similarity > MaxSimilarity && Similarity > 0.1) {
            MaxSimilarity = Similarity;
            BestGuess = i;
        }
    }

    return BestGuess;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(std::vector<float> *in, FollowerMIR *MIR) {
    // CurrentEvent represents the current event index.
    // In line with human understanding, the first note in the score
    // is indexed as 1 instead of 0. This adjustment is made in DspPerform.

    MIR->UpdateTempoInEvent();
    int EventId = CurrentEvent;
    float maxProb = -1;
    float Similarity;

    // MDP States
    State CurState = States[CurrentEvent];

    // Sound Description
    MIR->GetDescription(in, Desc, Tunning);
    Desc->TimeElapsed = MIR->GetEventTimeElapsed();

    if (Desc->dB < -40) {
        return CurrentEvent;
    }

    float BestGuess = GetBestEvent(States, Desc);
    if (BestGuess != CurrentEvent) {
        float Tn_1 = States[CurrentEvent].LiveOnset / 1000; // tn-1
        float Tn = States[BestGuess].LiveOnset / 1000;      // tn0
        float PsiK = 60 / States[CurrentEvent].Bpm;
        float PhiN = States[CurrentEvent].TimePhase;

        RValue = UpdateR(RValue, 0.01, Tn_1, Tn, PsiK, PhiN);

        float EventTime = MIR->GetEventTimeElapsed();
        MIR->ResetElapsedTime();
        CurrentEvent = BestGuess;
    }
    return CurrentEvent;
}
