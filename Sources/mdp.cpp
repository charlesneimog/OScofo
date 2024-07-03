#include "follower.hpp"

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
                    float amp = 1 / (std::pow(2, j)); // TODO: FIX THE AMP IN THE SIMILARY FUNCTION
                    float num = std::pow(i - (RootBinFreq * (j + 1)), 2);
                    float den = 2 * M_PI * m_PitchTemplateSigma * m_PitchTemplateSigma;
                    m_PitchTemplates[RootBinFreq][i] += amp * std::exp(-(num / den));
                    if (m_PitchTemplateHigherBin < RootBinFreq) {
                        m_PitchTemplateHigherBin = RootBinFreq;
                    }
                }
            }
        }
    }

    LOGE() << "end FollowerMDP::UpdatePitchTemplate";
}

// ─────────────────────────────────────
void FollowerMDP::UpdatePhaseValues() {
    m_LastR = 1;
    m_States[0].PhaseExpected = 0;
    float Tn = m_States[0].OnsetExpected;
    for (int i = 0; i < m_States.size() - 1; i++) {
        float PsiK = 60.0f / m_States[i].BPM;
        float Tn = m_States[i].OnsetExpected;
        float Tn1 = m_States[i + 1].OnsetExpected;
        float PhiN0 = m_States[i].PhaseExpected;
        float PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        m_States[i].IOI = ModPhases(PhiN1 - PhiN0);
        m_States[i + 1].PhaseExpected = PhiN1;
    }
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void FollowerMDP::ClearStates() {
    m_States.clear();
}
// ─────────────────────────────────────
float FollowerMDP::GetLiveBPM() {
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

// ─────────────────────────────────────
void FollowerMDP::SetTimeAccumFactor(float f) {
    m_AccumulationFactor = f;
}

// ─────────────────────────────────────
void FollowerMDP::SetTimeCouplingStrength(float f) {
    m_CouplingStrength = f;
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
double FollowerMDP::InverseA2(double r) {
    if (r > 0.95) { // Following Large (1999) p. 157
        return 10.0f;
    }

    double Low = 0.0;
    double Tol = 1e-5;
    double High = std::max(r, 10.0);
    double Mid;

    int i;
    for (i = 0; i < 10000; ++i) {
        Mid = (Low + High) / 2.0;
        double I1 = boost::math::cyl_bessel_i(1, r);
        double I0 = boost::math::cyl_bessel_i(0, r);
        double A2Mid = I1 / I0;
        if (std::fabs(A2Mid - r) < Tol) {
            return Mid;
        } else if (A2Mid < r) {
            Low = Mid;
        } else {
            High = Mid;
        }
    }
    return Mid;
}

// ─────────────────────────────────────
float FollowerMDP::VonMises(float Phi, float PhiMu, float Kappa) { // TODO: Rename to Von Mises
    float Exponent = Kappa * cos(TWO_PI * (Phi - PhiMu));
    float Coefficient = 1 / (TWO_PI * exp(Kappa));
    float PhiN = Coefficient * exp(Exponent) * sin(TWO_PI * (Phi - PhiMu));
    PhiN = ModPhases(PhiN);
    return PhiN;
}

// ─────────────────────────────────────
float FollowerMDP::ModPhases(float Value) {
    float ModValue = M_PI;
    Value = fmod(Value + ModValue, ModValue * 2) - ModValue;
    return Value;
}

// ─────────────────────────────────────
void FollowerMDP::GetBPM() {
    float HatPhiN, HatLastPhiN;

    HatPhiN = m_States[m_CurrentEvent].PhaseExpected; // IOI
    HatLastPhiN = m_States[m_CurrentEvent - 1].PhaseExpected;

    float Tn = m_States[m_CurrentEvent].IOI;
    float TnMinus1 = m_States[m_CurrentEvent - 1].IOI;

    // Correction - Update Kappa
    double CosTerm = TWO_PI * ((Tn - TnMinus1) / m_PsiK - HatPhiN);
    double CosValue = cos(CosTerm);
    float R = m_LastR - m_AccumulationFactor * (m_LastR - CosValue);
    if (R > 0.95) { // Following Large (1999) p. 157
        R = 0.95;
    }
    float Kappa = InverseA2(R);
    printf("Kappa: %f\n", Kappa);

    // Update PhiN
    double FValue = VonMises(m_LastPhiN, HatLastPhiN, Kappa);
    double PhiN = m_LastPhiN + (Tn - TnMinus1) / m_PsiNMinus1 + m_CouplingStrength * FValue;
    PhiN = ModPhases(PhiN);

    // Prediction
    FValue = VonMises(m_LastPhiN, HatLastPhiN, Kappa);
    float PsiN1 = m_PsiN * (1 + m_AccumulationFactor * FValue);

    m_LastPhiN = PhiN;
    m_PsiNMinus1 = m_PsiN;
    m_PsiN = m_PsiN1;
    m_PsiN1 = PsiN1;
    m_LastR = R;
    m_BPM = 60.0f / m_PsiN1;
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
        float P = PitchTemplate[i] * Desc->MaxAmp;
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
float FollowerMDP::GetBestEvent(FollowerMIR::m_Description *Desc) {
    if (m_CurrentEvent == -1) {
        m_BPM = m_States[0].BPM;
    }

    // TODO: Make this user defined
    float LookAhead = 2; // Look 5 seconds in future

    int BestGuess, i = m_CurrentEvent;
    float BestReward = -1;
    float EventLookAhead = 0;
    int StatesSize = m_States.size();
    int lastLook = 0;

    while (EventLookAhead < LookAhead) {
        if (i >= StatesSize) {
            break;
        }
        if (i < 0) {
            i = 0;
        }
        EventLookAhead += m_States[i].Duration * 60 / m_States[i].BPM; // TODO: Realtime bpm
        m_State NextPossibleState = m_States[i];
        float Reward = GetReward(NextPossibleState, Desc);
        if (Reward > BestReward) {
            BestReward = Reward;
            BestGuess = i;
        }
        lastLook = i;
        i++;
    }
    return BestGuess;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(Follower *x, FollowerMIR *MIR) {
    MIR->GetDescription(x->inBuffer, m_Desc, m_Tunning);

    if (m_Desc->dB < m_dBTreshold) {
        float BlockDur = 1 / m_x->Sr;
        m_TimeInThisEvent += BlockDur * m_x->HopSize;
        return m_CurrentEvent;
    }

    // Get the best event to describe the current state
    float Event = GetBestEvent(m_Desc);
    if (Event == m_CurrentEvent && Event != -1) {
        float BlockDur = 1 / m_x->Sr;
        m_TimeInThisEvent += BlockDur * m_x->HopSize;
    } else if (Event != m_CurrentEvent && Event == 0) {
        printf("\n");
        printf("============================================\n");
        m_CurrentEvent = Event;
        m_PsiK = 60 / m_States[0].BPM;
        m_PsiNMinus1 = m_PsiK;
        m_PsiN = m_PsiK;
        m_PsiN1 = m_PsiK;
        m_States[0].OnsetObserved = 0;

        // == psi
        m_LastPhiN = 0;
        m_LastPhiNHat = 0;

        m_BPM = m_States[0].BPM;
        m_Tn = 0;
        m_TimeInThisEvent = 0;
    } else if (Event != m_CurrentEvent && Event != 0) {
        m_CurrentEvent = Event;
        m_TnMinus1 = m_Tn;
        m_Tn += m_TimeInThisEvent;
        GetBPM();

        m_TimeInThisEvent = 0;
        float BlockDur = 1 / m_x->Sr;
        m_TimeInThisEvent += BlockDur * m_x->HopSize;
    }

    return m_CurrentEvent;
}
