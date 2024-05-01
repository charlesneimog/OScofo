#include "follower.hpp"

#include <cmath>
#include <math.h>
#include <omp.h>
// #include <random>

#define MAX_FREQUENCY_DIFFERENCE 10.0
#define MAX_QUALITY_DIFFERENCE 0.5

// TEST:
double UpdateR(double r, double eta_r, double t_n_1, double t_n, double psi_k, double phi_n) {
    r = r - eta_r * (r - cos(2 * M_PI * (t_n - t_n_1) / psi_k - phi_n));
    return r;
}

// ─────────────────────────────────────
FollowerMDP::FollowerMDP(Follower *Obj) {
    x = Obj;
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
float FollowerMDP::CompareSpectralTemplate(State NextPossibleState,
                                           FollowerMIR::Description *Desc) {

    // Prevision
    float KLDiv = 0.0;

    // Pitch Template
    int Harmonics = 10;
    float Sigma = 5;

    float Freq = FollowerMIR::Mtof(NextPossibleState.Midi, Tunning);
    float PitchSpectroForce = 0;
    std::vector<float> PitchTemplate(Desc->WindowSize, 0);

    for (int i = 1; i <= Harmonics; i++) {
        float FreqHarm = i * Freq;
        int mu = round(FreqHarm / (Desc->Sr / Desc->WindowSize));
        float Amp = 1 / exp(2);
        for (int j = 0; j < Desc->WindowSize; j++) {
            float x = j;
            float gaussValue = exp(-0.5 * pow((x - mu) / Sigma, 2));
            PitchTemplate[j] += gaussValue * Amp;
        }
    }

    // use Kullback-Leibler divergence to compare Desc->SpectralPower with PitchTemplate
    for (int i = 0; i < Desc->WindowSize; i++) {
        float p = Desc->SpectralPower[i];
        float q = PitchTemplate[i];
        if (q > 0 && p > 0) {
            // Equation 7.18 in Cont's thesis
            KLDiv += p * log(p / q) - p + q;
        }
    }

    PitchSpectroForce = exp(-0.4 * KLDiv);

    t_atom out[2];
    SETFLOAT(&out[0], NextPossibleState.Id + 1);
    SETFLOAT(&out[1], KLDiv);

    outlet_anything(x->Debug, gensym("pitch"), 2, out);

    return PitchSpectroForce;
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

    // float PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    // float TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc);

    float Similarity = CompareSpectralTemplate(NextPossibleState, Desc);

    // float Similarity = PitchSimilarity;

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
        NextPossibleState.WindowSize = CurState.WindowSize;
        NextPossibleState.Sr = CurState.Sr;
        float Similarity = GetSimilarity(NextPossibleState, Desc);
        NextPossibleState.Similarity = Similarity;
        if (Similarity > MaxSimilarity) {
            MaxSimilarity = Similarity;
            BestGuess = i;
        }
        // post("Event %d | Similarity %f", i, Similarity);
    }
    return BestGuess;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(Follower *x, FollowerMIR *MIR) {

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
    MIR->GetDescription(x->inBuffer, Desc, Tunning);
    Desc->TimeElapsed = MIR->GetEventTimeElapsed();

    if (Desc->dB < -40) {
        return CurrentEvent;
    }

    float BestGuess = GetBestEvent(States, Desc);
    if (BestGuess != CurrentEvent) {
        // Value of R
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
