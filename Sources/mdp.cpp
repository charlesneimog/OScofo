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
    m_x = Obj;
    m_Desc = new FollowerMIR::m_Description();
    m_BpmHistory.assign(20, 1);
    if (Obj->WindowSize / 2 != m_PitchTemplate.size()) {
        m_PitchTemplate.resize(Obj->WindowSize / 2);
    }
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
float FollowerMDP::GetLiveBpm() {
    return m_LiveBpm;
}

// ─────────────────────────────────────
void FollowerMDP::SetLiveBpm(float Bpm) {
    m_LiveBpm = Bpm;
}

// ─────────────────────────────────────
void FollowerMDP::ResetLiveBpm() {
    m_BpmHistory.assign(20, 1);
}

// ─────────────────────────────────────
int FollowerMDP::GetStatesSize() {
    return m_States.size();
}
// ─────────────────────────────────────
void FollowerMDP::AddState(FollowerMDP::m_State state) {
    m_States.push_back(state);
}
// ─────────────────────────────────────
FollowerMDP::m_State FollowerMDP::GetState(int Index) {
    return m_States[Index];
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
FollowerMDP::m_TimeDecoder::m_TimeDecoder(Follower *Obj) {

    // k é o número de ciclos para chegar em Onset[i]
    unsigned int StateSize = Obj->MDP->GetStatesSize();

    float k = 1; // TODO: How to calculate k?

    for (int i = 1; i < StateSize; i++) {
        m_State State0 = Obj->MDP->GetState(i - 1);
        m_State State1 = Obj->MDP->GetState(i);

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
double FollowerMDP::m_TimeDecoder::PhaseOfN() {

    return 0;
}

double FollowerMDP::m_TimeDecoder::RDispersion(int n, double coupleStrength,
                                               std::vector<float> mean,
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
double FollowerMDP::m_TimeDecoder::HatKappa(double r, double tol, double max_iter) {

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
float FollowerMDP::GetPitchSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc) {
    float KLDiv = 0.0;
    int Harmonics = 5;
    std::fill(m_PitchTemplate.begin(), m_PitchTemplate.end(), 0);

    // Template Config
    float z = 0.5; // TODO: This is the beta value of function 16.

    float NextPitch = NextPossibleState.Freq;
    float Sr = Desc->Sr;
    float RootBinFreq = NextPitch / (Desc->Sr / Desc->WindowSize);

    // TODO: This must be done offline, this function is called each audio block
    for (size_t i = 0; i < Desc->WindowSize / 2; i++) {
        for (size_t j = 0; j < Harmonics; j++) {
            float amp = Desc->MaxAmp / (pow(2, j));
            float num = std::pow(i - (RootBinFreq * (j + 1)), 2);
            float den = 2 * M_PI * m_PitchTemplateSigma * m_PitchTemplateSigma;
            m_PitchTemplate[i] += amp * exp(-(num / den));
        }
    }

    for (size_t i = 0; i < Desc->WindowSize / 2; i++) {
        float P = m_PitchTemplate[i];
        float Q = Desc->NormSpectralPower[i];
        if (P > 0 && Q > 0) {
            KLDiv += P * log(P / Q) - P + Q;
        } else if (P == 0 && Q >= 0) {
            KLDiv += Q;
        }
    }

    KLDiv = exp(-z * KLDiv);
    return KLDiv;
}

// ─────────────────────────────────────
float FollowerMDP::GetTimeSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc) {
    return 0;
}

// ─────────────────────────────────────
float FollowerMDP::GetReward(m_State NextPossibleState, FollowerMIR::m_Description *Desc) {
    float PitchWeight = 0.5;
    float TimeWeight = 0.5;

    float PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    // float TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc) * TimeWeight;

    float Reward = PitchSimilarity * PitchWeight;

    return Reward;
}

// ─────────────────────────────────────
void FollowerMDP::GetBestEvent(std::vector<m_State> States, FollowerMIR::m_Description *Desc) {
    float BestGuess = m_CurrentEvent;
    m_State CurState = States[m_CurrentEvent];

    float BestReward = -1;

    // Get Best Reward
    for (int i = m_CurrentEvent; i < (m_CurrentEvent + 6); i++) {
        if (i >= States.size() || i < 0) {
            continue;
        }

        m_State NextPossibleState = States[i];
        float Reward = GetReward(NextPossibleState, Desc);

        if (Reward > BestReward) {
            BestReward = Reward;
            BestGuess = i;
        }
    }
    m_CurrentEvent = BestGuess;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(Follower *x, FollowerMIR *MIR) {
    // MIR->UpdateTempoInEvent();

    // Sound Description
    MIR->GetDescription(x->inBuffer, m_Desc, m_Tunning);

    if (m_Desc->dB < -40) { // TODO: Make this -40 variable for user define
        return m_CurrentEvent;
    }
    GetBestEvent(m_States, m_Desc);

    return m_CurrentEvent;
}
