#include "mdp.hpp"
#include "log.hpp"

#include <boost/math/special_functions/bessel.hpp>

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
OScofoMDP::OScofoMDP(float Sr, float WindowSize, float HopSize) {
    m_HopSize = HopSize;
    m_WindowSize = WindowSize;
    m_Sr = Sr;

    if (m_WindowSize / 2 != m_PitchTemplate.size()) {
        m_PitchTemplate.resize(m_WindowSize / 2);
    }
    m_AccumulationFactor = 0.5;
    m_CouplingStrength = 0.5;
    m_BeatsAhead = 6;

    SetTunning(440);
    CreateKappaTable();
}

// ─────────────────────────────────────
void OScofoMDP::SetScoreStates(States States) {
    m_States.clear();
    m_States = States;
    UpdatePitchTemplate();
    m_PsiN = 60.0f / m_States[0].BPMExpected;
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
// │        Set Public Functions         │
// ╰─────────────────────────────────────╯
void OScofoMDP::SetBeatsAhead(double BeatsAhead) {
    m_BeatsAhead = BeatsAhead;
}

// ─────────────────────────────────────
void OScofoMDP::SetBPM(double BPM) {
    m_BPM = BPM;
}

// ─────────────────────────────────────
void OScofoMDP::SetdBTreshold(double dB) {
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
void OScofoMDP::SetCurrentEvent(int Event) {
    m_CurrentEvent = Event;
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
// │        Get Public Functions         │
// ╰─────────────────────────────────────╯
double OScofoMDP::GetLiveBPM() {
    return m_BPM;
}

// ─────────────────────────────────────
double OScofoMDP::GetKappa() {
    return m_Kappa;
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
void OScofoMDP::CreateKappaTable() {
    double start = 0.0;
    double end = 1.0;
    double step = 0.01;
    double Tol = 1e-8;
    double Mid;

    for (double x = start; x <= end; x += step) {
        double Low = 0.0; // Initialize Low inside the loop
        double High = std::max(x, 10.0);
        int TableIndex = round(x * 100);
        for (int i = 0; i < 1000; ++i) {
            Mid = (Low + High) / 2.0;
            double I1 = boost::math::cyl_bessel_i(1, Mid);
            double I0 = boost::math::cyl_bessel_i(0, Mid);
            double A2Mid = I1 / I0;

            if (std::fabs(A2Mid - x) < Tol) {
                m_KappaTable[TableIndex] = Mid;
                break;
            } else if (A2Mid < x) {
                Low = Mid;
            } else {
                High = Mid;
            }
        }
        if (m_KappaTable.find(x) == m_KappaTable.end()) {
            m_KappaTable[TableIndex] = Mid;
        }
    }
}

// ─────────────────────────────────────
double OScofoMDP::InverseA2(double SyncStrength) {
    if (SyncStrength < 0) {
        return 0;
    }
    if (SyncStrength > 0.95) {
        return 10.0;
    }
    SyncStrength = round(SyncStrength * 100);
    double Kappa;
    auto it = m_KappaTable.find(SyncStrength);
    if (it != m_KappaTable.end()) {
        Kappa = it->second;
    } else {
        Kappa = 0;
    }
    return Kappa;
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
void OScofoMDP::UpdateBPM() {
    // Cont (2010), Large and Palmer (1999) and Large and Jones (2002)
    State LastState = m_States[m_CurrentEvent - 1];
    State CurrentState = m_States[m_CurrentEvent];
    State NextState = m_States[m_CurrentEvent + 1];

    double IOISeconds = m_Tn - m_LastTn;
    double LastPhiN = LastState.IOIPhiN;
    double LastHatPhiN = LastState.IOIHatPhiN;
    double HatPhiN = CurrentState.IOIHatPhiN;
    double PhiNExpected = LastPhiN + ((m_Tn - m_LastTn) / m_PsiN);
    CurrentState.IOIHatPhiN = PhiNExpected;

    // Update Variance (Cont, 2010) - Coupling Strength (Large 1999)
    double PhaseDiff = (IOISeconds / m_PsiN) - HatPhiN;
    double SyncStrength = m_SyncStr - m_AccumulationFactor * (m_SyncStr - cos(TWO_PI * PhaseDiff));
    double Kappa = InverseA2(SyncStrength);
    m_SyncStr = SyncStrength;
    m_Kappa = Kappa;

    // Update and Correct PhiN
    double FValueUpdate = CouplingFunction(LastPhiN, LastHatPhiN, Kappa);
    double PhiN = LastPhiN + (IOISeconds / m_LastPsiN) + (m_CouplingStrength * FValueUpdate);
    PhiN = ModPhases(PhiN);
    CurrentState.PhaseObserved = PhiN;

    // Prediction for next PsiN+1
    double FValuePrediction = CouplingFunction(PhiN, HatPhiN, Kappa);
    double PsiN1 = m_PsiN * (1 + m_AccumulationFactor * FValuePrediction);

    // Prediction for Next HatPhiN
    double LastOnsetExpected = m_Tn + CurrentState.Duration * PsiN1;
    double PhiN1 = ModPhases((m_Tn1 - m_Tn) / PsiN1);
    NextState.IOIHatPhiN = PhiN1;

    // Update all next expected onsets
    NextState.OnsetExpected = LastOnsetExpected;
    for (int i = m_CurrentEvent + 2; i < m_States.size(); i++) {
        State &FutureState = m_States[i];
        State &PreviousFutureState = m_States[(i - 1)];
        double Duration = PreviousFutureState.Duration;
        float FutureOnset = LastOnsetExpected + Duration * PsiN1;
        FutureState.OnsetExpected = FutureOnset;
        LastOnsetExpected = FutureOnset;
    }

    // Update Values for next calls
    m_BPM = 60.0f / m_PsiN1;
    m_LastPsiN = m_PsiN;
    m_PsiN = PsiN1;
    m_PsiN1 = PsiN1;
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
double OScofoMDP::GetPitchSimilarity(State &PossibleState, Description &Desc) {
    double KLDiv = 0.0;
    double RootBinFreq = round(PossibleState.Freq / (m_Sr / m_WindowSize));

    PitchTemplateArray PitchTemplate;
    if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
        PitchTemplate = m_PitchTemplates[RootBinFreq];
    } else {
        printf("PitchTemplate not found\n");
        return 0;
    }

    for (size_t i = 0; i < m_WindowSize / 2; i++) {
        if (i > m_PitchTemplateHigherBin) {
            break;
        }
        double P = PitchTemplate[i] * Desc.MaxAmp;
        double Q = Desc.NormSpectralPower[i];
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
double VonMisesPDF(double Theta, double Mu, double Kappa) {
    double Norm = 1 / boost::math::cyl_bessel_i(0, Kappa);
    double PDF = Norm * exp(Kappa * cos(TWO_PI * (Theta - Mu)));
    return PDF;
}

double OScofoMDP::GetTimeSimilarity(State &PossibleState, Description &Desc) {
    double CurrentTime = m_Tn + m_TimeInThisEvent;
    double TimeSimilarity;

    if (PossibleState.Index == m_CurrentEvent) {
        double Diff = CurrentTime - PossibleState.OnsetExpected;
        double PhiN = PossibleState.PhaseObserved;
        PhiN = ModPhases(PhiN + (CurrentTime - m_Tn) / m_PsiN);
        TimeSimilarity = VonMisesPDF(PhiN, 0, m_Kappa);
        printf("TimeSimilarity: %f\n", TimeSimilarity);

    } else {
        double TimeUtilOnset = PossibleState.OnsetExpected - m_Tn;
    }

    return 0;
}

// ─────────────────────────────────────
double OScofoMDP::GetReward(State &PossibleState, Description &Desc) {
    double PitchWeight;
    double TimeWeight;

    double PitchSimilarity = GetPitchSimilarity(PossibleState, Desc);
    double TimeSimilarity = GetTimeSimilarity(PossibleState, Desc);
    double Reward;

    if (PossibleState.Type == NOTE) {
        PitchWeight = 0.5;
        TimeWeight = 0.5;
        Reward = (PitchSimilarity * PitchWeight);
    }

    // TODO: Add Attack Envelope

    return Reward;
}

// ─────────────────────────────────────
int OScofoMDP::GetEvent(Description &Desc) {
    double BlockDur = 1 / m_Sr;
    m_TimeInThisEvent += BlockDur * m_HopSize;

    if (!Desc.PassTreshold) {
        return m_CurrentEvent;
    }

    // Get the best event to describe the current state
    if (m_CurrentEvent == -1) {
        m_BPM = m_States[0].BPMExpected;
        m_PsiN = 60 / m_BPM;
        m_MaxAheadSeconds = m_BeatsAhead * m_PsiN;
        m_Kappa = 1;
    }

    int Event, i = m_CurrentEvent;
    double BestReward = -1;
    double EventLookAhead = 0;
    int StatesSize = m_States.size();

    // NOTE: For now we are not considering returning from the current event
    while (EventLookAhead < (m_BeatsAhead * m_PsiN)) {
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
            Event = i;
        }
        i++;
    }

    if (Event != m_CurrentEvent && Event == 0) {
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
        UpdateBPM();
        m_TimeInThisEvent = 0;
        LOGE();
        printf("\n");
    }

    LOGE() << "Get Event Finish";
    m_CurrentEvent = Event;
    return m_CurrentEvent;
}
