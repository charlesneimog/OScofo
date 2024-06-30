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
                LOGE() << "Pitch Template already " << RootBinFreq << " exits...";

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
float FollowerMDP::GetBPM() {
    return m_BPM;
}

// ─────────────────────────────────────
void FollowerMDP::SetBPM(float BPM) {
    m_BPM = BPM;
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
void FollowerMDP::GetBPM(std::vector<m_State> States) {
    if (m_CurrentEvent < 1) {
        return;
    }
    float phi_n = 0; // Initial phase
    float r = 0;     // Initial dispersion
    std::vector<float> PhiValues;
    PhiValues.push_back(0);

    // float eta_s = 0.05; // Small coupling constant for dispersion update
    float eta_s = 0.2; // Small coupling constant for dispersion update
    float psi_k = 60 / States[0].BPM;
    float psi_n = psi_k;

    for (int i = 1; i < m_CurrentEvent; i++) {
        // Calculate psi_k
        psi_k = 60 / States[i].BPM;

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
        int i = m_CurrentEvent;
        // TODO: FINISH

        m_TimeInThisEvent = 0;
    }

    GetBPM(States);
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
