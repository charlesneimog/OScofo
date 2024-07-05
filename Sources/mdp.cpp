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
    m_AccumulationFactor = 0.5;
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
        m_States[i + 1].IOIHatPhiN = (Tn1 - Tn) / PsiK;
        m_States[i + 1].IOIPhiN = (Tn1 - Tn) / PsiK;
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
double FollowerMDP::CouplingFunction(double Phi, double PhiMu, double Kappa) {
    double ExpKappa = exp(Kappa);
    double CosTerm = cos(TWO_PI * (Phi - PhiMu));
    double SinTerm = sin(TWO_PI * (Phi - PhiMu));
    double PhiN = (1 / (TWO_PI * ExpKappa)) * exp(Kappa * CosTerm) * SinTerm;
    return PhiN;
}

// ─────────────────────────────────────
double FollowerMDP::ModPhases(double Phase) {
    // Normalize phase to be within -pi to pi
    Phase = fmod(Phase + M_PI, TWO_PI); // adjust range to 0 to 2*pi
    if (Phase < 0) {
        Phase += TWO_PI; // handle negative result from fmod
    }
    return Phase - M_PI; // shift range to -pi to pi
}

// ─────────────────────────────────────
void FollowerMDP::GetBPM() {
    int LastEvent = m_CurrentEvent - 1;
    int CurrentEvent = m_CurrentEvent;
    int NextEvent = m_CurrentEvent + 1;
    int here = 0;

    printf("I am here 1\n");
    double IOISeconds = m_Tn - m_LastTn;

    double LastPhiN = m_States[LastEvent].IOIPhiN;
    double LastHatPhiN = m_States[LastEvent].IOIHatPhiN;

    double HatPhiN = m_States[CurrentEvent].IOIHatPhiN;

    double PhiNExpected = LastPhiN + ((m_Tn - m_LastTn) / m_PsiN);
    m_States[CurrentEvent].IOIHatPhiN = PhiNExpected;
    printf("I am here 2\n");

    // Começa o algoritmo 1
    // Update Variance (Cont, 2010) - Coupling Strength (Large 1999)
    double Term = (IOISeconds / m_PsiN) - HatPhiN;
    double R = m_LastR - m_AccumulationFactor * (m_LastR - cos(TWO_PI * Term));
    printf("I am here 3\n");
    double Kappa = InverseA2(R);
    printf("I am here 4\n");
    m_LastR = R;

    // Update and Correct PhiN
    double FValueUpdate = CouplingFunction(LastPhiN, LastHatPhiN, Kappa);
    double PhiN = LastPhiN + (IOISeconds / m_LastPsiN) + (m_CouplingStrength * FValueUpdate);
    PhiN = ModPhases(PhiN); // Atual
    printf("I am here 5\n");

    // Prediction for next PsiN+1
    double FValuePrediction = CouplingFunction(PhiN, HatPhiN, Kappa);
    double PsiN1 = m_PsiN * (1 + m_AccumulationFactor * FValuePrediction);
    printf("I am here 6\n");

    // Prediction for next PhiN
    // State.OnsetExpected = LastOnset + PreviousDuration * (60 / BPM); // in Seconds
    double Duration = m_States[CurrentEvent].Duration;
    double Tn1 = m_Tn + Duration * PsiN1;
    double PhiN1 = ModPhases((Tn1 - m_Tn) / PsiN1);
    m_States[CurrentEvent + 1].IOIHatPhiN = PhiN1;

    // Update Previous Values
    m_BPM = 60.0f / m_PsiN1;
    m_LastPsiN = m_PsiN;
    m_PsiN = PsiN1;
    m_PsiN1 = PsiN1;
    printf("BPM: %f\n", m_BPM);
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
        double PsiK = 60 / m_States[0].BPMExpected;

        m_LastPsiN = PsiK;
        m_PsiN = PsiK;
        m_PsiN1 = PsiK;
        m_States[0].OnsetObserved = 0;
        m_BPM = m_States[0].BPMExpected;
        m_Tn = 0;
        m_LastTn = 0;
        m_TimeInThisEvent = 0;
    } else if (Event != m_CurrentEvent && Event != 0) {
        LOGE() << "\n\n========= Event: " << Event << " ===============";
        m_CurrentEvent = Event;
        m_LastTn = m_Tn;
        m_Tn += m_TimeInThisEvent;
        GetBPM();
        m_TimeInThisEvent = 0;
    }

    return m_CurrentEvent;
}
