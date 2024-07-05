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
    m_AccumulationFactor = 0.3;
    m_CouplingStrength = 0.5;

    SetTunning(440);
}

// ─────────────────────────────────────
void FollowerMDP::SetScoreStates(States States) {
    m_States = States;
}
// ─────────────────────────────────────
void FollowerMDP::UpdatePitchTemplate() {
    LOGE() << "start FollowerMDP::UpdatePitchTemplate";
    m_PitchTemplates.clear();
    m_PitchTemplateHigherBin = 0;

    int StateSize = m_States.size();
    for (int h = 0; h < StateSize; h++) {
        if (m_States[h].Valid) {
            double Pitch = m_States[h].Freq;
            double RootBinFreq = round(Pitch / (m_Sr / m_WindowSize));
            if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
                continue;
            } else {
                m_PitchTemplates[RootBinFreq].resize(m_WindowSize / 2);
            }
            for (size_t i = 0; i < m_WindowSize / 2; ++i) {
                for (size_t j = 0; j < m_Harmonics; ++j) {
                    double amp = 1 / (std::pow(2, j)); // TODO: FIX THE AMP IN THE SIMILARY FUNCTION
                    double num = std::pow(i - (RootBinFreq * (j + 1)), 2);
                    double den = 2 * M_PI * m_PitchTemplateSigma * m_PitchTemplateSigma;
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
    m_LastR = 0;
    m_States[0].PhaseExpected = 0;
    for (int i = 0; i < m_States.size() - 1; i++) {
        double PsiK = 60.0f / m_States[i].BPMExpected;
        double Tn = m_States[i].OnsetExpected;
        double Tn1 = m_States[i + 1].OnsetExpected;
        double PhiN0 = m_States[i].PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        m_States[i + 1].PhaseExpected = PhiN1;
        m_States[i + 1].PhaseObserved = PhiN1;
        m_States[i + 1].IOIPhaseExpected = (Tn1 - Tn) / PsiK;
    }
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void FollowerMDP::ClearStates() {
    m_States.clear();
}
// ─────────────────────────────────────
double FollowerMDP::GetLiveBPM() {
    return m_BPM;
}

// ─────────────────────────────────────
void FollowerMDP::SetBPM(double BPM) {
    m_BPM = BPM;
}

// ─────────────────────────────────────
void FollowerMDP::SetTreshold(double dB) {
    m_dBTreshold = dB;
}

// ─────────────────────────────────────
void FollowerMDP::SetTunning(double Tunning) {
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
void FollowerMDP::AddState(State State) {
    m_States.push_back(State);
}
// ─────────────────────────────────────
State FollowerMDP::GetState(int Index) {
    return m_States[Index];
}

// ─────────────────────────────────────
void FollowerMDP::SetPitchTemplateSigma(double f) {
    m_PitchTemplateSigma = f;
}

// ─────────────────────────────────────
void FollowerMDP::SetTimeAccumFactor(double f) {
    m_AccumulationFactor = f;
}

// ─────────────────────────────────────
void FollowerMDP::SetTimeCouplingStrength(double f) {
    m_CouplingStrength = f;
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
double FollowerMDP::GetAttentionalEnergy() {
    double SumSin = 0, SumCos = 0;
    for (int i = 0; i < m_CurrentEvent; i++) {
        SumSin += sin(m_States[i].PhaseObserved);
        SumCos += cos(m_States[i].PhaseObserved);
    }

    // Calculate mean direction (phi_mu)
    double PhiMu = atan2(SumSin, SumCos);

    // Calculate R and kappa (as you did before)
    double R = sqrt(pow(SumSin, 2) + pow(SumCos, 2)) / m_CurrentEvent;
    float Kappa;
    if (R < 0.53) {
        Kappa = 2 * R + pow(R, 3) + 5 * pow(R, 5) / 6;
    } else if (R < 0.85) {
        Kappa = -0.4 + 1.39 * R + 0.43 / (1 - R);
    } else {
        Kappa = 1 / (pow(R, 3) - 4 * pow(R, 2) + 3 * R);
    }

    // Correct normalization
    double Norm = 1 / boost::math::cyl_bessel_i(0, Kappa);
    double PhiN = m_States[m_CurrentEvent].PhaseObserved;
    double AttentionalEnergy = exp(Kappa * cos(TWO_PI * (PhiN - PhiMu)));

    return Norm * AttentionalEnergy;
}

// ─────────────────────────────────────
double FollowerMDP::InverseA2(double r) {
    if (r > 0.95) {
        return 10.0f;
    }

    double Low = 0.0;
    double Tol = 1e-5;
    double High = std::max(r, 10.0);
    double Mid;

    for (int i = 0; i < 10000; ++i) {
        Mid = (Low + High) / 2.0;
        double I1 = boost::math::cyl_bessel_i(1, Mid);
        double I0 = boost::math::cyl_bessel_i(0, Mid);
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
double FollowerMDP::VonMises(double Phi, double PhiMu, double Kappa) {
    double ExpKappa = exp(Kappa);
    double CosTerm = cos(TWO_PI * (Phi - PhiMu));
    double SinTerm = sin(TWO_PI * (Phi - PhiMu));
    double PhiN = (1 / (TWO_PI * ExpKappa)) * exp(Kappa * CosTerm) * SinTerm;
    return PhiN;
}

// ─────────────────────────────────────
double FollowerMDP::ModPhases(double Phase) {
    // make a modules between -pi and pi
    while (Phase < -M_PI) {
        Phase += TWO_PI;
    }

    while (Phase > M_PI) {
        Phase -= TWO_PI;
    }

    return Phase;
}

// ─────────────────────────────────────
void FollowerMDP::GetBPM() {

    double IOISeconds = m_Tn - m_TnMinus1;
    double HatPhiN = m_States[m_CurrentEvent].IOIPhaseExpected;
    double PhiNMinus1 = m_States[m_CurrentEvent - 1].PhaseObserved;

    // Update Variance (Cont, 2010) - Coupling Strength (Large 1999)
    double Term = TWO_PI * ((IOISeconds / m_PsiN) - HatPhiN);
    double R = m_LastR - m_AccumulationFactor * (m_LastR - cos(Term));
    double Kappa = InverseA2(R);

    if (Kappa < 1) { // Valor de Kappa é 1 quando o ritmo não é estável
        Kappa = 1;
    }

    m_LastR = R;

    // Update and Correct PhiN
    double HatLastPhiN = m_States[m_CurrentEvent - 1].IOIPhaseExpected;
    double LastPhiN = m_States[m_CurrentEvent - 1].PhaseObserved;
    double FValueUpdate = VonMises(LastPhiN, HatLastPhiN, Kappa);
    double PhiN = LastPhiN + (IOISeconds / m_PsiNMinus1) + (m_CouplingStrength * FValueUpdate);
    PhiN = ModPhases(PhiN);
    m_States[m_CurrentEvent].IOIPhaseObserved = PhiN;

    // Prediction
    double FValuePrediction = VonMises(PhiN, HatPhiN, Kappa); // TODO: Change to coupling function
    double PsiN1 = m_PsiN * (1 + m_AccumulationFactor * FValuePrediction);

    // Update Previous Values
    m_BPM = 60.0f / m_PsiN1;
    m_PsiNMinus1 = m_PsiN;
    m_PsiN = PsiN1;
    m_PsiN1 = PsiN1;

    // printf("Attentional Energy %f\n", GetAttentionalEnergy());
    // printf("Kappa %f\n", Kappa);
    printf("BPM %f\n", m_BPM);
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
double FollowerMDP::GetPitchSimilarity(State NextPossibleState, FollowerMIR::m_Description *Desc) {
    double KLDiv = 0.0;
    double RootBinFreq = round(NextPossibleState.Freq / (m_Sr / m_WindowSize));

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
        double P = PitchTemplate[i] * Desc->MaxAmp;
        double Q = Desc->NormSpectralPower[i];
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
double FollowerMDP::GetTimeSimilarity(State NextPossibleState, FollowerMIR::m_Description *Desc) {
    return 0;
}

// ─────────────────────────────────────
double FollowerMDP::GetReward(State NextPossibleState, FollowerMIR::m_Description *Desc) {
    double PitchWeight = 0.5;
    double TimeWeight = 0.5;
    // FUTURE: Add Attack Envelope

    double PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    double TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc) * TimeWeight;

    double Reward = (PitchSimilarity * PitchWeight) + (TimeSimilarity * TimeWeight);

    return Reward;
}

// ─────────────────────────────────────
double FollowerMDP::GetBestEvent(FollowerMIR::m_Description *Desc) {
    if (m_CurrentEvent == -1) {
        m_BPM = m_States[0].BPMExpected;
    }

    // TODO: Make this user defined
    double LookAhead = 2; // Look 5 seconds in future

    int BestGuess, i = m_CurrentEvent;
    double BestReward = -1;
    double EventLookAhead = 0;
    int StatesSize = m_States.size();
    int lastLook = 0;

    while (EventLookAhead < LookAhead) {
        if (i >= StatesSize) {
            break;
        }
        if (i < 0) {
            i = 0;
        }
        EventLookAhead += m_States[i].Duration * m_PsiN; // TODO: Realtime bpm
        State NextPossibleState = m_States[i];
        double Reward = GetReward(NextPossibleState, Desc);
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
    double BlockDur = 1 / m_x->Sr;
    m_TimeInThisEvent += BlockDur * m_x->HopSize;

    MIR->GetDescription(x->inBuffer, m_Desc, m_Tunning);

    if (m_Desc->dB < m_dBTreshold) {
        double BlockDur = 1 / m_x->Sr;
        return m_CurrentEvent;
    }

    // Get the best event to describe the current state
    double Event = GetBestEvent(m_Desc);
    if (Event != m_CurrentEvent && Event == 0) {
        printf("\n");
        m_CurrentEvent = Event;
        m_PsiK = 60 / m_States[0].BPMExpected;
        m_PsiNMinus1 = m_PsiK;
        m_PsiN = m_PsiK;
        m_PsiN1 = m_PsiK;
        m_States[0].OnsetObserved = 0;
        m_BPM = m_States[0].BPMExpected;
        m_Tn = 0;
        m_TnMinus1 = 0;
        m_TimeInThisEvent = 0;
    } else if (Event != m_CurrentEvent && Event != 0) {
        LOGE() << "\n\n========= Event: " << Event << " ===============";
        m_CurrentEvent = Event;
        m_TnMinus1 = m_Tn;
        m_Tn += m_TimeInThisEvent;
        GetBPM();
        m_TimeInThisEvent = 0;
    }

    return m_CurrentEvent;
}
