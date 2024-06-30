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
    if (Obj->WindowSize / 2 != m_PitchTemplate.size()) {
        m_PitchTemplate.resize(Obj->WindowSize / 2);
    }
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
float FollowerMDP::GetLiveBpm() {
    return m_BPM;
}

// ─────────────────────────────────────
void FollowerMDP::SetLiveBpm(float Bpm) {
    m_BPM = Bpm;
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
void FollowerMDP::GetLiveBpm(std::vector<m_State> States) {
    if (m_CurrentEvent < 1) {
        return;
    }
    float phi_n = 0; // Initial phase
    float r = 0;     // Initial dispersion
    std::vector<float> PhiValues;
    PhiValues.push_back(0);

    // float eta_s = 0.05; // Small coupling constant for dispersion update
    float eta_s = 0.2; // Small coupling constant for dispersion update
    float psi_k = 60 / States[0].Bpm;
    float psi_n = psi_k;

    for (int i = 1; i < m_CurrentEvent; i++) {
        // Calculate psi_k
        psi_k = 60 / States[i].Bpm;

        // Calculate phases using Equation 8
        float t_n0 = States[i - 1].Onset * psi_k;
        float t_n1 = States[i].Onset * psi_k;
        float ExpectedPhase = phi_n + ((t_n1 - t_n0) / psi_k);
        ExpectedPhase = fmod(ExpectedPhase + M_PI, TWO_PI) - M_PI;
        PhiValues.push_back(ExpectedPhase);

        // Calculate dispersion r using Equation 13
        float sumCos = 0;
        for (float phi : PhiValues) {
            sumCos += std::cos(TWO_PI * (phi - phi_n));
        }
        r = sumCos / PhiValues.size();

        // Update kappa
        r = r - eta_s * (r - std::cos(TWO_PI * ((t_n1 - t_n0) / psi_n - ExpectedPhase)));

        float kappa;
        if (r < 0.53) {
            kappa = 2 * r + pow(r, 3) + (5 * pow(r, 5)) / 6.0;
        } else if (r < 0.85) {
            kappa = -0.4 + 1.39 * r + 0.43 / (1 - r);
        } else {
            kappa = 1 / (pow(r, 3) - 4 * pow(r, 2) + 3 * r);
        }

        // Iterate using Newton-Raphson method to improve approximation
        for (int i = 0; i < 1000; ++i) {
            float I0 = boost::math::cyl_bessel_i(0, kappa);
            float I1 = boost::math::cyl_bessel_i(1, kappa);
            float f_kappa = I1 / I0 - r;
            float f_prime_kappa = 1 - (I1 * I1) / (I0 * I0);
            kappa -= f_kappa / f_prime_kappa;
        }

        // Calculate F using Equation 10
        float F_value = (1 / (TWO_PI * std::exp(kappa))) *
                        std::exp(kappa * std::cos(TWO_PI * (phi_n - ExpectedPhase))) *
                        std::sin(TWO_PI * (phi_n - ExpectedPhase));

        // Update phase using Equation 11
        phi_n = phi_n + ((t_n1 - t_n0) / psi_n) + m_EtaPhi * F_value;
        phi_n = fmod(phi_n + M_PI, TWO_PI) - M_PI;

        // Update psi using Equation 15
        psi_n = psi_n * (1 + kappa * F_value);
    }
    m_BPM = 60 / psi_n;
}
// ─────────────────────────────────────
// float FollowerMDP::GetLiveBpm(std::vector<m_State> States) {
//     if (m_CurrentEvent < 1) {
//         return m_BPM;
//     }
//     float psi_k; // Valor fixo (?)
//
//     // Calculate initial value of r
//     float r = 0;
//     std::vector<float> PhiValues;
//     float CurrentPhase = 0;
//     float CouplingFactor = 0.1;
//     PhiValues.push_back(0);
//     for (int i = 0; i < m_CurrentEvent - 1; i++) {
//         psi_k = 60 / States[i].Bpm;
//
//         // First Phase
//         float t_n = States[i].Onset * psi_k;
//         float t_n1 = States[i + 1].Onset * psi_k; // ????????w
//         float ExpectedPhase = CurrentPhase + ((t_n1 - t_n) / psi_k);
//         ExpectedPhase = fmod(CurrentPhase + M_PI, TWO_PI) - M_PI;
//
//         PhiValues.push_back(ExpectedPhase);
//
//         float Mean = 0;
//         for (float Phi : PhiValues) {
//             Mean += Phi;
//         }
//         Mean /= PhiValues.size();
//         float kappa;
//         if (Mean < 0.53) {
//             kappa = 2 * Mean + std::pow(Mean, 3) + 5 * std::pow(Mean, 5) / 6;
//         } else if (Mean < 0.85) {
//             kappa = -0.4 + 1.39 * Mean + 0.43 / (1 - Mean);
//         } else {
//             kappa = 1 / (std::pow(Mean, 3) - 4 * std::pow(Mean, 2) + 3 * Mean);
//         }
//
//         // Von Mises Distribution
//         float VonMises = VonMissesDistribution(CurrentPhase, ExpectedPhase, kappa);
//         float Correction = DistributionFunction(CurrentPhase, ExpectedPhase, kappa);
//
//         float eq11_1 = VonMises + CouplingFactor * Correction;
//         float eq11 = std::fmod(eq11_1 + M_PI, TWO_PI) - M_PI;
//         CurrentPhase = eq11;
//         r = 1.0 / PhiValues.size();
//     }
//     for (float phi : PhiValues) {
//         r += std::cos(2 * M_PI * (phi - CurrentPhase));
//     }
//     r /= PhiValues.size();
//
//     // Update r and Kappa
//     psi_k = 60 / m_BPM;
//     float t_n = States[m_CurrentEvent].Onset * psi_k;
//     float t_nm1 = States[m_CurrentEvent - 1].Onset * psi_k;
//     float v0 = (t_nm1 - t_n) / psi_k - States[m_CurrentEvent].PhaseOnset;
//     r = r - m_EtaS * (r - cos(TWO_PI * v0));
//     float kappa = GetKappa(r);
//
//     // Update Phi N
//     t_n = States[m_CurrentEvent].Onset * psi_k;
//     float last_t_n = States[m_CurrentEvent - 1].Onset * psi_k;
//     float psi_n = 60 / m_BPM;
//     float last_psi_n = 60 / m_BPM;
//     float LastPhiHat = States[m_CurrentEvent - 1].PhaseOnset;
//     float DF = DistributionFunction(m_LastPhi, LastPhiHat, kappa);
//     float Phi = m_LastPhi + ((t_n - last_t_n) / last_psi_n) + m_EtaPhi * DF;
//     Phi = fmod(Phi + M_PI, TWO_PI) - M_PI;
//
//     // BPM prediction
//     float PhiHat = States[m_CurrentEvent].PhaseOnset;
//     float DecodedPsi = psi_n * (1 + m_EtaS * DistributionFunction(Phi, PhiHat, kappa));
//     m_BPM = 60 / (DecodedPsi - 1);
//
//     m_LastPhi = Phi;
//     return m_BPM;
// }

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
    if (m_CurrentEvent == -1) {
        m_BPM = States[0].Bpm;
    }

    // TODO: Make this user defined
    float LookAhead = 5; // Look 5 seconds in future

    int BestGuess, i = m_CurrentEvent;
    float BestReward = -1;
    float EventLookAhead = 0;
    int StatesSize = States.size();
    int lastLook = 0;
    while (EventLookAhead < LookAhead) {
        if (i >= StatesSize) {
            break;
        }
        if (i < 0) {
            i = 0;
        }
        EventLookAhead += States[i].Duration * 60 / States[i].Bpm; // TODO: Realtime bpm
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
    // Get Sound Description saved in m_Desc
    MIR->GetDescription(x->inBuffer, m_Desc, m_Tunning);

    // Check if we have silence
    if (m_Desc->dB < -40) { // TODO: Make this -40 variable for user define
        return m_CurrentEvent;
    }

    // Get the best event to describe the current state
    GetBestEvent(m_States, m_Desc);

    return m_CurrentEvent;
}
