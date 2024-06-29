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

static float Equation10(float phi, float phi_mu, float kappa) {
    float eq10_1 = 1.f / (2 * PI * std::exp(kappa));
    float eq10_2 = exp(kappa * cos(TWO_PI * (phi - phi_mu)));
    float eq10_3 = sin(TWO_PI * (phi - phi_mu));
    return eq10_1 * eq10_2 * eq10_3;
}

// ─────────────────────────────────────
float FollowerMDP::GetLiveBpm(std::vector<m_State> States) {
    if (m_CurrentEvent == 0) {
        return 0;
    }

    // Calculate r with correction term
    float r = States[m_CurrentEvent].Dispersion;
    float t_n0 = States[m_CurrentEvent - 1].Onset;
    float t_n1 = States[m_CurrentEvent].Onset;
    float psi_k = 60 / States[m_CurrentEvent].Bpm;
    float v0 = (t_n1 - t_n0) / psi_k - States[m_CurrentEvent].PhaseOnset;
    r = r - m_EtaS * (r - cos(TWO_PI * v0));

    // Solve for kappa
    double low = 0.01, up = 10.0;
    int max_iter = 100;
    double mid;
    int iter = 0;
    float tol = 1e-6;
    while (iter < max_iter) {
        mid = (low + up) / 2.0;
        double f_mid = boost::math::cyl_bessel_i(1, mid) / boost::math::cyl_bessel_i(0, mid) - r;
        if (std::abs(f_mid) < tol) {
            break;
        }
        double f_lower = boost::math::cyl_bessel_i(1, low) / boost::math::cyl_bessel_i(0, low) - r;
        if (f_lower * f_mid < 0) {
            up = mid;
        } else {
            low = mid;
        }
        iter++;
    }
    float kappa = mid;

    // Phase update
    float t_n = States[m_CurrentEvent].Onset;
    float last_t_n = States[m_CurrentEvent - 1].Onset;
    float last_psi_n = 60 / States[m_CurrentEvent - 1].Bpm;
    float LastPhiHat = States[m_CurrentEvent - 1].PhaseOnset;

    float eq10 = Equation10(m_LastPhi, LastPhiHat, kappa);

    m_LastPhi = m_LastPhi + (t_n - last_t_n) / last_psi_n + m_EtaPhi * eq10;
    m_LastPhi = fmod(m_LastPhi, TWO_PI);

    // BPM prediction
    float PhiHat = States[m_CurrentEvent].PhaseOnset;
    m_BPM = m_BPM * (1 + m_EtaS * Equation10(m_LastPhi, PhiHat, kappa));
    return m_BPM;
}

float FollowerMDP::GetBpm() {
    return m_BPM;
}

// ─────────────────────────────────────

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
    // FUTURE: Add Attack Envelope

    float PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    float TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc) * TimeWeight;

    float Reward = (PitchSimilarity * PitchWeight) + (TimeSimilarity * TimeWeight);

    return Reward;
}

// ─────────────────────────────────────
void FollowerMDP::GetBestEvent(std::vector<m_State> States, FollowerMIR::m_Description *Desc) {
    if (m_BPM == 0 && m_CurrentEvent == -1) {
        m_BPM = States[0].Bpm;
    }

    float BestGuess = m_CurrentEvent;
    float BestReward = -1;
    float LookAhead = 5;
    float EventLookAhead = 0;
    int i = m_CurrentEvent;
    int StatesSize = States.size();

    int lastLook = 0;

    while (EventLookAhead < LookAhead) {
        if (i >= StatesSize) {
            break;
        }
        if (i < 0) {
            i = 0;
        }
        EventLookAhead += States[i].Duration * 60 / m_BPM;
        m_State NextPossibleState = States[i];
        float Reward = GetReward(NextPossibleState, Desc);
        if (Reward > BestReward) {
            BestReward = Reward;
            BestGuess = i;
        }
        lastLook = i;
        i++;
    }

    if (BestGuess == m_CurrentEvent) {
        int BlockDurMs = m_x->HopSize / m_x->Sr * 1000;
        m_TimeInThisEvent += BlockDurMs;
        return;
    } else if (m_CurrentEvent != -1) {
        int i = m_CurrentEvent;
        float ExpectedDuration = States[m_CurrentEvent].Duration * 60 / m_BPM * 1000;
        m_RealtimeDur.push_back(m_TimeInThisEvent);

        m_TimeInThisEvent = 0;
    }

    GetLiveBpm(States);
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
