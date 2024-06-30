#include "follower.hpp"

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
    m_HopSize = Obj->HopSize;
    m_WindowSize = Obj->WindowSize;
    m_Sr = Obj->Sr;

    m_Desc = new FollowerMIR::m_Description();
    if (Obj->WindowSize / 2 != m_PitchTemplate.size()) {
        m_PitchTemplate.resize(Obj->WindowSize / 2);
    }

    SetTunning(440);
}

// ─────────────────────────────────────
void FollowerMDP::UpdatePitchTemplate() {
    LOGE() << "start FollowerMDP::UpdatePitchTemplate";
    m_PitchTemplates.clear();
    m_PitchTemplateHigherBin = 0;

    int StateSize = m_States.size();
    for (int h = 0; h < StateSize; h++) {
        if (m_States[h].Valid) {
            float Pitch = m_States[h].Freq;
            float RootBinFreq = round(Pitch / (m_Sr / m_WindowSize));
            if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
                continue;
            } else {
                m_PitchTemplates[RootBinFreq].resize(m_WindowSize / 2);
            }
            for (size_t i = 0; i < m_WindowSize / 2; ++i) {
                for (size_t j = 0; j < m_Harmonics; ++j) {
                    float amp = 1 / (pow(2, j)); // TODO: FIX THE AMP IN THE SIMILARY FUNCTION
                    float num = std::pow(i - (RootBinFreq * (j + 1)), 2);
                    float den = 2 * M_PI * m_PitchTemplateSigma * m_PitchTemplateSigma;
                    m_PitchTemplates[RootBinFreq][i] += amp * exp(-(num / den));
                    if (m_PitchTemplateHigherBin < RootBinFreq) {
                        m_PitchTemplateHigherBin = RootBinFreq;
                    }
                }
            }
        }
    }

    LOGE() << "end FollowerMDP::UpdatePitchTemplate";
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void FollowerMDP::ClearStates() {
    m_States.clear();
}
// ─────────────────────────────────────
float FollowerMDP::GetBPM() {
    return m_BPM;
}

// ─────────────────────────────────────
void FollowerMDP::SetBPM(float BPM) {
    m_BPM = BPM;
}

// ─────────────────────────────────────
void FollowerMDP::SetTreshold(float dB) {
    m_dBTreshold = dB;
}

// ─────────────────────────────────────
void FollowerMDP::SetTunning(float Tunning) {
    m_Tunning = Tunning;
}

// ─────────────────────────────────────
void FollowerMDP::SetHarmonics(int Harmonics) {
    m_Harmonics = Harmonics;
}

// ─────────────────────────────────────
int FollowerMDP::GetTunning() {
    return m_Tunning;
}

// ─────────────────────────────────────
void FollowerMDP::SetEvent(int Event) {
    m_CurrentEvent = Event;
}

// ─────────────────────────────────────
int FollowerMDP::GetStatesSize() {
    return m_States.size();
}
// ─────────────────────────────────────
void FollowerMDP::AddState(FollowerMDP::m_State State) {
    m_States.push_back(State);
}
// ─────────────────────────────────────
FollowerMDP::m_State FollowerMDP::GetState(int Index) {
    return m_States[Index];
}

// ─────────────────────────────────────
void FollowerMDP::SetPitchTemplateSigma(float f) {
    m_PitchTemplateSigma = f;
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
float A1_2(float r) {
    // Handle edge cases to avoid division by zero and other numerical issues
    if (r <= 0.0f) {
        return 0.0f; // Or another appropriate value based on your application's requirements
    }
    if (r >= 1.0f) {
        return std::numeric_limits<float>::infinity(); // r should not be greater than or equal to 1
    }

    // Calculate modified Bessel functions of the first kind
    float I_neg_half = boost::math::cyl_bessel_i(1, r);
    // or

    float I_pos_half = boost::math::cyl_bessel_i(2, r);

    // Handle potential division by zero if I_neg_half is very small
    if (std::abs(I_neg_half) < 1e-8f) {
        return std::numeric_limits<float>::infinity(); // Or a large value to indicate an error
    }

    // Calculate and return the ratio
    return (I_pos_half / I_neg_half) - r;
}

void FollowerMDP::GetBPM(std::vector<m_State> States) {
    if (m_CurrentEvent < 1) {
        return; // Not enough events to estimate tempo
    }

    float phi_n = 0.0f; // Initial phase
    float r = 0.0f;     // Initial dispersion

    // Coupling constants (tuned based on experimentation)
    float eta_s = 0.4f;   // Dispersion update coupling strength
    float eta_phi = 0.5f; // Phase update coupling strength

    float psi_n = 1.0f / States[0].BPM * 60.0f; // Initial tempo in seconds/beat

    for (int i = 1; i < m_CurrentEvent; i++) {
        // Calculate psi_k (expected tempo for current event)
        float psi_k = 60.0f / States[i].BPM;

        // Calculate expected phase using Equation 11
        float t_n0 = States[i - 1].Onset * psi_k;
        float t_n1 = States[i].Onset * psi_k;
        float expectedPhase = phi_n + ((t_n1 - t_n0) / psi_k);
        expectedPhase = fmod(expectedPhase + M_PI, TWO_PI) - M_PI;

        // Calculate dispersion r using Equation 13 (recursive update)
        r = r - eta_s * (r - cos(TWO_PI * ((t_n1 - t_n0) / psi_n - expectedPhase)));

        // Calculate kappa using Equation 14 (approximation from the paper)
        float kappa = A1_2(r); // Assuming A1_2 is a function implementing the lookup table

        // Calculate F using Equation 10
        float F_value = (1.0f / (TWO_PI * exp(kappa))) *
                        exp(kappa * cos(TWO_PI * (phi_n - expectedPhase))) *
                        sin(TWO_PI * (phi_n - expectedPhase));

        // Update phase using Equation 11
        phi_n = phi_n + ((t_n1 - t_n0) / psi_n) + eta_phi * F_value;
        phi_n = fmod(phi_n + M_PI, TWO_PI) - M_PI;

        // Update psi (tempo) using Equation 12
        psi_n = psi_n * (1.0f + eta_phi * F_value);
    }

    m_BPM = 60.0f / psi_n; // Convert tempo back to BPM
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
float FollowerMDP::GetPitchSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc) {
    float KLDiv = 0.0;
    float RootBinFreq = round(NextPossibleState.Freq / (m_Sr / m_WindowSize));

    PitchTemplateArray PitchTemplate;
    if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
        PitchTemplate = m_PitchTemplates[RootBinFreq];
    } else {
        pd_error(NULL,
                 "[follower~] Pitch Template not found, it should not happen, please report it");
        return 0;
    }

    for (size_t i = 0; i < m_WindowSize / 2; i++) {
        if (i > m_PitchTemplateHigherBin) {
            break;
        }
        float P = PitchTemplate[i];
        float Q = Desc->NormSpectralPower[i];
        if (P > 0 && Q > 0) {
            KLDiv += P * log(P / Q) - P + Q;
        } else if (P == 0 && Q >= 0) {
            KLDiv += Q;
        }
    }

    KLDiv = exp(-m_Z * KLDiv);
    return KLDiv;
}

// ─────────────────────────────────────
float FollowerMDP::GetTimeSimilarity(m_State NextPossibleState, FollowerMIR::m_Description *Desc) {
    post("print spent in this event %f", m_TimeInThisEvent);
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
        m_BPM = States[0].BPM;
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
        EventLookAhead += States[i].Duration * 60 / States[i].BPM; // TODO: Realtime bpm
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
        m_TimeInThisEvent = 0;
    }

    GetBPM(States);
    m_CurrentEvent = BestGuess;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(Follower *x, FollowerMIR *MIR) {
    // Get Sound Description saved in m_Desc
    MIR->GetDescription(x->inBuffer, m_Desc, m_Tunning);

    if (m_Desc->dB < m_dBTreshold) {
        return m_CurrentEvent;
    }

    // Get the best event to describe the current state
    GetBestEvent(m_States, m_Desc);

    return m_CurrentEvent;
}
