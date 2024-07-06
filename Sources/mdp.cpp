#include "mdp.hpp"
#include "log.hpp"

#include <boost/math/special_functions/bessel.hpp>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯
OScofoMDP::OScofoMDP(float Sr, float WindowSize, float HopSize) {
    m_HopSize = HopSize;
    m_WindowSize = WindowSize;
    m_Sr = Sr;

    m_Desc = new OScofoMIR::m_Description();
    if (m_WindowSize / 2 != m_PitchTemplate.size()) {
        m_PitchTemplate.resize(m_WindowSize / 2);
    }
    m_AccumulationFactor = 0.5;
    m_CouplingStrength = 0.5;

    SetTunning(440);
}

// ─────────────────────────────────────
void OScofoMDP::SetScoreStates(States States) {
    m_States.clear();
    m_States = States;
}
// ─────────────────────────────────────
void OScofoMDP::UpdatePitchTemplate() {
    LOGE() << "start OScofoMDP::UpdatePitchTemplate";
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
    LOGE() << "end OScofoMDP::UpdatePitchTemplate";
}

// ─────────────────────────────────────
void OScofoMDP::UpdatePhaseValues() {
    m_SyncStr = 0;

    if (m_States.size() == 0) {
        return;
    }

    m_PsiN = 60.0f / m_States[0].BPMExpected;
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
void OScofoMDP::ClearStates() {
    m_States.clear();
}
// ─────────────────────────────────────
double OScofoMDP::GetLiveBPM() {
    return m_BPM;
}

// ─────────────────────────────────────
void OScofoMDP::SetBPM(double BPM) {
    m_BPM = BPM;
}

// ─────────────────────────────────────
void OScofoMDP::SetTreshold(double dB) {
    m_dBTreshold = dB;
}

// ─────────────────────────────────────
void OScofoMDP::SetTunning(double Tunning) {
    m_Tunning = Tunning;
}

// ─────────────────────────────────────
void OScofoMDP::SetHarmonics(int Harmonics) {
    m_Harmonics = Harmonics;
}

// ─────────────────────────────────────
int OScofoMDP::GetTunning() {
    return m_Tunning;
}

// ─────────────────────────────────────
void OScofoMDP::SetEvent(int Event) {
    m_CurrentEvent = Event;
}

// ─────────────────────────────────────
int OScofoMDP::GetStatesSize() {
    return m_States.size();
}
// ─────────────────────────────────────
void OScofoMDP::AddState(State State) {
    m_States.push_back(State);
}
// ─────────────────────────────────────
State OScofoMDP::GetState(int Index) {
    return m_States[Index];
}

// ─────────────────────────────────────
void OScofoMDP::SetPitchTemplateSigma(double f) {
    m_PitchTemplateSigma = f;
}

// ─────────────────────────────────────
void OScofoMDP::SetTimeAccumFactor(double f) {
    m_AccumulationFactor = f;
}

// ─────────────────────────────────────
void OScofoMDP::SetTimeCouplingStrength(double f) {
    m_CouplingStrength = f;
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
double OScofoMDP::InverseA2(double SyncStrength) {
    // SyncStrength must be between 0 and 1
    if (SyncStrength < 0) {
        return 0;
    }

    // Following Large and Jones (1999, p. 157).
    if (SyncStrength > 0.95) {
        return 10.0f;
    }

    double Low = 0.0;
    double Tol = 1e-8;
    double High = std::max(SyncStrength, 10.0);
    double Mid;

    // In my tests I never reached more than 100 iterations.
    int i;
    for (i = 0; i < 100; ++i) {
        Mid = (Low + High) / 2.0;
        double I1 = boost::math::cyl_bessel_i(1, Mid);
        double I0 = boost::math::cyl_bessel_i(0, Mid);
        double A2Mid = I1 / I0;
        if (std::fabs(A2Mid - SyncStrength) < Tol) {
            return Mid;
        } else if (A2Mid < SyncStrength) {
            Low = Mid;
        } else {
            High = Mid;
        }
    }
    LOGE() << "InverseA2 not converged after " << i << " iterations.";
    return Mid;
}

// ─────────────────────────────────────
double OScofoMDP::CouplingFunction(double Phi, double PhiMu, double Kappa) {
    // Equation 2b from Large and Palmer (2002)
    double ExpKappa = exp(Kappa);
    double PhiNDiff = Phi - PhiMu;
    double CosTerm = cos(TWO_PI * PhiNDiff);
    double SinTerm = sin(TWO_PI * PhiNDiff);
    double PhiN = (1 / (TWO_PI * ExpKappa)) * exp(Kappa * CosTerm) * SinTerm;
    return PhiN;
}

// ─────────────────────────────────────
double OScofoMDP::ModPhases(double Phase) {
    // Following Cont (2010) conventions
    Phase = fmod(Phase + M_PI, TWO_PI);
    if (Phase < 0) {
        Phase += TWO_PI;
    }
    return Phase - M_PI;
}

// ─────────────────────────────────────
void OScofoMDP::GetBPM() {
    // Cont (2010), Large and Palmer (1999) and Large and Jones (2002)

    State &LastState = m_States[m_CurrentEvent - 1];
    State &CurrentState = m_States[m_CurrentEvent];
    State &NextState = m_States[m_CurrentEvent + 1];

    double IOISeconds = m_Tn - m_LastTn;
    double LastPhiN = LastState.IOIPhiN;
    double LastHatPhiN = LastState.IOIHatPhiN;
    double HatPhiN = CurrentState.IOIHatPhiN;
    LOGE() << "PsiN: " << m_PsiN;
    double PhiNExpected = LastPhiN + ((m_Tn - m_LastTn) / m_PsiN);
    CurrentState.IOIHatPhiN = PhiNExpected;

    // Update Variance (Cont, 2010) - Coupling Strength (Large 1999)
    double PhaseDiff = (IOISeconds / m_PsiN) - HatPhiN;
    double SyncStrength = m_SyncStr - m_AccumulationFactor * (m_SyncStr - cos(TWO_PI * PhaseDiff));
    LOGE() << "SyncStrength: " << SyncStrength;
    double Kappa = InverseA2(SyncStrength);
    m_SyncStr = SyncStrength;

    // Update and Correct PhiN
    double FValueUpdate = CouplingFunction(LastPhiN, LastHatPhiN, Kappa);
    double PhiN = LastPhiN + (IOISeconds / m_LastPsiN) + (m_CouplingStrength * FValueUpdate);
    PhiN = ModPhases(PhiN);
    CurrentState.PhaseObserved = PhiN;

    // Prediction for next PsiN+1
    double FValuePrediction = CouplingFunction(PhiN, HatPhiN, Kappa);
    double PsiN1 = m_PsiN * (1 + m_AccumulationFactor * FValuePrediction);

    // Prediction for Next HatPhiN
    double Duration = CurrentState.Duration;
    double Tn1 = m_Tn + Duration * PsiN1;
    double PhiN1 = ModPhases((Tn1 - m_Tn) / PsiN1);
    NextState.IOIHatPhiN = PhiN1;

    // Update Previous Values
    m_BPM = 60.0f / m_PsiN1;
    m_LastPsiN = m_PsiN;
    m_PsiN = PsiN1;
    m_PsiN1 = PsiN1;

    LOGE() << "Attencional Energy: " << m_SyncStr;
    LOGE() << "BPM: " << m_BPM;
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
double OScofoMDP::GetPitchSimilarity(State NextPossibleState, OScofoMIR::m_Description *Desc) {
    double KLDiv = 0.0;
    double RootBinFreq = round(NextPossibleState.Freq / (m_Sr / m_WindowSize));

    PitchTemplateArray PitchTemplate;
    if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
        PitchTemplate = m_PitchTemplates[RootBinFreq];
    } else {
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
double OScofoMDP::GetTimeSimilarity(State NextPossibleState, OScofoMIR::m_Description *Desc) {
    // m_SyncStr = 0;

    return 0;
}

// ─────────────────────────────────────
double OScofoMDP::GetReward(State NextPossibleState, OScofoMIR::m_Description *Desc) {
    double PitchWeight;
    double TimeWeight;
    if (NextPossibleState.Type == NOTE) {
        PitchWeight = 0.5;
        TimeWeight = 0.5;
    }

    // TODO: Add Attack Envelope

    double PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    double TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc) * TimeWeight;

    double Reward = (PitchSimilarity * PitchWeight); //+ (TimeSimilarity * (m_SyncStr / 2));

    return Reward;
}

// ─────────────────────────────────────
double OScofoMDP::GetBestEvent(OScofoMIR::m_Description *Desc) {
    LOGE() << "OScofoMDP::GetBestEvent";
    if (m_CurrentEvent == -1) {
        m_BPM = m_States[0].BPMExpected;
    }

    // TODO: Make this user defined
    double LookAhead = 2; // Look 5 seconds in future

    int BestGuess, i = m_CurrentEvent;
    double BestReward = -1;
    double EventLookAhead = 0;
    int StatesSize = m_States.size();

    // Core Function
    while (EventLookAhead < LookAhead) {
        if (i >= StatesSize) {
            break;
        }
        if (i < 0) {
            i = 0;
        }
        EventLookAhead += m_States[i].Duration * m_PsiN;
        State State = m_States[i];
        double Reward = GetReward(State, Desc);
        if (Reward > BestReward) {
            BestReward = Reward;
            BestGuess = i;
        }
        i++;
    }
    LOGE() << "end OScofoMDP::GetBestEvent";
    return BestGuess;
}

// ─────────────────────────────────────
int OScofoMDP::GetEvent(std::vector<double> AudioIn, OScofoMIR *MIR) {
    double BlockDur = 1 / m_Sr;
    m_TimeInThisEvent += BlockDur * m_HopSize;
    MIR->GetDescription(AudioIn, m_Desc, m_Tunning);

    if (m_Desc->dB < m_dBTreshold) {
        double BlockDur = 1 / m_Sr;
        LOGE() << "End GetEvent";
        return m_CurrentEvent;
    }

    // Get the best event to describe the current state
    double Event = GetBestEvent(m_Desc);
    if (Event != m_CurrentEvent && Event == 0) {
        LOGE();
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
        LOGE() << "<== Event: " << Event << " ==>";
        m_CurrentEvent = Event;
        m_LastTn = m_Tn;
        m_Tn += m_TimeInThisEvent;
        GetBPM();
        m_TimeInThisEvent = 0;
        LOGE();
    }

    LOGE() << "Get Event Finish";
    return m_CurrentEvent;
}
