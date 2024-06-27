#include "follower.hpp"

#include <algorithm> // For std::max_element
#include <cmath>
#include <math.h>
#include <omp.h>

#include <boost/math/special_functions/bessel.hpp>

#define MAX_FREQUENCY_DIFFERENCE 10.0
#define MAX_QUALITY_DIFFERENCE 0.5

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯
FollowerMDP::FollowerMDP(Follower *Obj) {
    x = Obj;
    Desc = new FollowerMIR::Description();
    BpmHistory.assign(20, 1);
    if (Obj->WindowSize / 2 != PitchTemplate.size()) {
        PitchTemplate.resize(Obj->WindowSize / 2);
    }
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
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

// ─────────────────────────────────────
std::vector<FollowerMDP::State> FollowerMDP::GetStates() {
    return States;
}

// ─────────────────────────────────────
int FollowerMDP::GetStatesSize() {
    return States.size();
}
// ─────────────────────────────────────
void FollowerMDP::AddState(FollowerMDP::State state) {
    States.push_back(state);
}
// ─────────────────────────────────────
FollowerMDP::State FollowerMDP::GetState(int Index) {
    return States[Index];
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
FollowerMDP::TimeDecoder::TimeDecoder(Follower *Obj) {

    // k é o número de ciclos para chegar em Onset[i]
    unsigned int StateSize = Obj->MDP->GetStatesSize();

    float k = 1; // TODO: How to calculate k?

    for (int i = 1; i < StateSize; i++) {
        State State0 = Obj->MDP->GetState(i - 1);
        State State1 = Obj->MDP->GetState(i);

        // eq 8
        float Time = 60 / State1.Bpm;
        float t0 = State0.Onset;
        float t1 = State1.Onset;
        float PhiN = t0 / Time + TWO_PI * k;
        float PhiN1 = PhiN + (t1 - t0) / Time;
        PhiN1 = fmod(PhiN1, TWO_PI) - PI;

        // eq 10
    }
}

// ─────────────────────────────────────
double FollowerMDP::TimeDecoder::PhaseOfN() {

    return 0;
}

double FollowerMDP::TimeDecoder::RDispersion(int n, double coupleStrength, std::vector<float> mean,
                                             std::vector<float> expPhasePos) {

    // Eq 13;
    float sum = 0;
    for (int i = 1; i < n; i++) {
        sum += cos(TWO_PI * (mean[i] - expPhasePos[i]));
    }
    sum = sum / n;
    return sum;
}

// ─────────────────────────────────────
double FollowerMDP::TimeDecoder::HatKappa(double r, double tol, double max_iter) {

    // Eq 14;
    double low = 0.01, up = 10.0;
    double mid;
    int iter = 0;
    while (iter < max_iter) {
        mid = (low + up) / 2.0;
        double f_mid = boost::math::cyl_bessel_i(1, mid) / boost::math::cyl_bessel_i(0, mid) - r;
        if (std::abs(f_mid) < tol) {
            return mid;
        }
        double f_lower = boost::math::cyl_bessel_i(1, low) / boost::math::cyl_bessel_i(0, low) - r;
        if (f_lower * f_mid < 0) {
            up = mid;
        } else {
            low = mid;
        }
        iter++;
    }
    return mid;
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
void FollowerMDP::SetPitchTemplateSigma(float f) {
    m_PitchTemplateSigma = f;
}
// ─────────────────────────────────────
float FollowerMDP::CompareSpectralTemplate(State NextPossibleState,
                                           FollowerMIR::Description *Desc) {
    float KLDiv = 0.0;
    int Harmonics = 5;
    std::fill(PitchTemplate.begin(), PitchTemplate.end(), 0);

    // Template Config
    float z = 0.5;

    float NextPitch = NextPossibleState.Freq;
    float Sr = Desc->Sr;
    float BinFreq = NextPitch / (Desc->Sr / Desc->WindowSize);

    for (size_t i = 0; i < Desc->WindowSize / 2; i++) {
        for (size_t j = 0; j < Harmonics; j++) {
            float amp = Desc->MaxAmp / (pow(2, j));
            float num = std::pow(i - (BinFreq * (j + 1)), 2);
            float den = 2 * M_PI * m_PitchTemplateSigma * m_PitchTemplateSigma;
            PitchTemplate[i] += amp * exp(-(num / den));
        }
    }

    for (size_t i = 0; i < Desc->WindowSize / 2; i++) {
        float P = PitchTemplate[i];
        float Q = Desc->NormSpectralPower[i];
        if (P > 0 && Q > 0) {
            KLDiv += P * log(P / Q) - P + Q;
        } else if (P == 0 && Q >= 0) {
            KLDiv += Q;
        }
    }

    KLDiv = exp(-z * KLDiv);
    LOGE() << "KLDiv " << KLDiv;
    return KLDiv;
}

// ─────────────────────────────────────
float FollowerMDP::GetTimeSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {
    return 0;
}

// ─────────────────────────────────────
float FollowerMDP::GetReward(State NextPossibleState, FollowerMIR::Description *Desc) {
    float PitchWeight = 0.7;
    float TimeWeight = 0.3;

    float PitchSimilarity = CompareSpectralTemplate(NextPossibleState, Desc) * PitchWeight;
    // float TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc) * TimeWeight;

    // float Similarity = PitchSimilarity + TimeSimilarity;

    return PitchSimilarity;
}

// ─────────────────────────────────────
float FollowerMDP::GetBestEvent(std::vector<State> States, FollowerMIR::Description *Desc) {
    float BestGuess = CurrentEvent;
    State CurState = States[CurrentEvent];

    float MaxSimilarity = -1;

    // 3 means that it just look for the next 3 events
    for (int i = CurrentEvent; i < (CurrentEvent + 3); i++) {
        LOGE() << "Event " << i;
        if (i >= States.size() || i < 0) {
            continue;
        }
        State NextPossibleState = States[i];
        NextPossibleState.WindowSize = CurState.WindowSize;
        NextPossibleState.Sr = CurState.Sr;
        float Similarity = GetReward(NextPossibleState, Desc);
        LOGE() << "Similarity " << Similarity;
        NextPossibleState.Similarity = Similarity;
        if (Similarity > MaxSimilarity) {
            MaxSimilarity = Similarity;
            BestGuess = i;
        }
    }
    LOGE() << "\n";
    CurrentEvent = BestGuess;
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
    if (Desc->dB < -40) { // TODO: Make this variable
        return CurrentEvent;
    }
    Desc->TimeElapsed = MIR->GetEventTimeElapsed();

    float BestGuess = GetBestEvent(States, Desc);
    if (BestGuess != CurrentEvent) {
        // Value of R
    }
    return CurrentEvent;
}
