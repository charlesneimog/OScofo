#include "mdp.hpp"
#include "log.hpp"
#include "states.hpp"

#include <boost/math/special_functions/bessel.hpp>

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
OScofoMDP::OScofoMDP(float Sr, float WindowSize, float HopSize) {

    // Check if the outer map contains the key

    m_HopSize = HopSize;
    m_WindowSize = WindowSize;
    m_Sr = Sr;
    m_AccumulationFactor = 0.5;
    m_CouplingStrength = 0.5;

    SetTunning(440);
    CreateKappaTable();
}

// ─────────────────────────────────────
void OScofoMDP::SetScoreStates(States States) {
    m_States = States;
    m_LastEvent = m_States.size() - 1;

    SetCurrentEvent(-1);
    UpdatePhaseValues();
    UpdatePitchTemplate();

    // Values
    m_PsiN = 60.0f / m_States[0].BPMExpected;
    m_PsiN1 = 60.0f / m_States[0].BPMExpected;
    m_LastPsiN = 60.0f / m_States[0].BPMExpected;
    m_BeatsAhead = m_States[0].BPMExpected / 60 * 4;

    CreateMarkovMatrix();
}

// ─────────────────────────────────────
void OScofoMDP::CreateMarkovMatrix() {
    int size = m_States.size();

    int i = -1;
    for (int i = -1; i < size; i++) {
        double Dur = 0;
        for (int j = i + 1; j < m_States.size(); j++) {
            Dur += m_States[j].Duration;
            double DurProb = std::exp(-(5 * Dur / m_BeatsAhead));
            double LastDur = Dur / m_BeatsAhead;
            if (LastDur > 1 && i < j + 3) {
                break;
            } else if (LastDur > 1 && i >= j + 3) {
                for (int k = i; k < i + 3; k++) {
                    double BigDurProb = std::exp(k);
                    m_TransitionsProb[i][k] = BigDurProb;
                }
                break;
            } else {
                m_TransitionsProb[i][j] = DurProb;
            }
        }
        double Sum = 0;
        int innerSize = m_TransitionsProb[i].size();

        for (int j = i + 1; j <= i + innerSize; j++) {
            Sum += m_TransitionsProb[i][j];
        }
        for (int j = i + 1; j <= i + innerSize; j++) {
            m_TransitionsProb[i][j] /= Sum;
            // printf("Trans %d -> %d = %f\n", i, j, m_TransitionsProb[i][j]);
        }
    }

    return;
}
// ─────────────────────────────────────
void OScofoMDP::UpdatePitchTemplate() {
    m_PitchTemplateHigherBin = 0;
    int StateSize = m_States.size();
    m_PitchTemplates.clear();
    m_PitchTemplateHigherBin = 0;

    for (int h = 0; h < StateSize; h++) {
        if (m_States[h].Valid) {
            // TODO: Implement CHORDS
            double Pitch = m_States[h].Freqs[0];
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
    printf("Pitch Template Updated\n");
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
        State &CurrentState = m_States[i];
        State &NextState = m_States[i + 1];
        double PsiK = 60.0f / m_States[i].BPMExpected;
        double Tn = CurrentState.OnsetExpected;
        double Tn1 = NextState.OnsetExpected;
        double PhiN0 = CurrentState.PhaseExpected;
        double PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK);
        PhiN1 = ModPhases(PhiN1);
        NextState.PhaseExpected = PhiN1;
        NextState.PhaseObserved = PhiN1;
        NextState.IOIHatPhiN = (Tn1 - Tn) / PsiK;
        NextState.IOIPhiN = (Tn1 - Tn) / PsiK;
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
    m_NewCurrentEvent = Event;
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
    if (m_CurrentEvent == m_States.size()) {
        return;
    }

    State &LastState = m_States[m_CurrentEvent - 1];
    State &CurrentState = m_States[m_CurrentEvent];
    State &NextState = m_States[m_CurrentEvent + 1];

    double IOISeconds = m_Tn - m_LastTn;
    double LastPhiN = LastState.IOIPhiN;
    double LastHatPhiN = LastState.IOIHatPhiN;
    double HatPhiN = CurrentState.IOIHatPhiN;
    double PhiNExpected = LastPhiN + ((m_Tn - m_LastTn) / m_PsiN);
    CurrentState.IOIHatPhiN = PhiNExpected;
    CurrentState.OnsetObserved = m_Tn;

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
    m_Tn1 = m_Tn + CurrentState.Duration * PsiN1;
    double PhiN1 = ModPhases((m_Tn1 - m_Tn) / PsiN1);
    NextState.IOIHatPhiN = PhiN1;

    // Update all next expected onsets
    NextState.OnsetExpected = m_Tn1;
    double LastOnsetExpected = m_Tn1;

    // the m_CurrentEvent + 1 already updated, now
    // we update the future events to get the Sojourn Time
    for (int i = m_CurrentEvent + 2; i < m_CurrentEvent + 20; i++) {
        if (i >= m_States.size()) {
            break;
        }
        State &FutureState = m_States[i];
        State &PreviousFutureState = m_States[(i - 1)];
        double Duration = PreviousFutureState.Duration;
        double FutureOnset = LastOnsetExpected + Duration * PsiN1;
        FutureState.OnsetExpected = FutureOnset;
        LastOnsetExpected = FutureOnset;
    }

    // TODO: m_Mu value | this is not necessary
    double SumX = 0.0, SumY = 0.0;
    for (int i = 0; i < m_CurrentEvent; ++i) {
        double PhiN = m_States[i].PhaseObserved;
        SumX += std::cos(PhiN);
        SumY += std::sin(PhiN);
    }
    m_Mu = ModPhases(std::atan2(SumY, SumX));

    // Update Values for next calls
    m_BPM = 60.0f / m_PsiN1;
    m_LastPsiN = m_PsiN;
    m_PsiN = PsiN1;
    m_PsiN1 = PsiN1;
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
double OScofoMDP::GetPitchSimilarity(State &State, Description &Desc) {
    double KLDiv = 0.0;

    // TODO: Implement CHORDS
    double RootBinFreq = round(State.Freqs[0] / (m_Sr / m_WindowSize));

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
double OScofoMDP::SojournTime(State &State, Description &Desc) {
    double T = m_Tn + m_TimeInThisEvent;
    double Duration = State.Duration;
    double Sojourn = std::exp(-((T - m_Tn) / (m_PsiN1 * Duration)));

    return Sojourn;
}

// ─────────────────────────────────────
// Guédon (2004)
double OScofoMDP::ForwardRecursion(Description &Desc) {

    double BestProb = 0;
    for (int j = m_NewCurrentEvent; j < m_StateWindow; j++) {
    }

    return 0;
}

// ─────────────────────────────────────
double OScofoMDP::ComputeStateTransition(Description &Desc) {
    int t = m_T;

    int BestEvent = -1;
    bool BestEventFound = false;

    double BestAlphaJ = 0;
    for (int j = m_NewCurrentEvent; j < m_StateWindow; j++) {
        if (j < 0) {
            j++;
            t = 1;
        }
        m_PitchKL[j][t] = GetPitchSimilarity(m_States[j], Desc);
        double maxAlphaJ = 0;
        for (int u = 1; u <= t; u++) {

            // term 1
            double MulKlDiv = m_PitchKL[j][t];
            for (int v = 1; v < u; v++) {
                MulKlDiv *= m_PitchKL[j][t - v];
            }

            // term 2
            double Sojourn = SojournTime(m_States[j], Desc);

            // term 3
            double MaxProb = 0;
            for (int i = m_NewCurrentEvent; i < m_NewCurrentEvent + 1; i++) {
                if (i == j) {
                    continue;
                }
                double PrevObserved;
                if (m_Observed.find(i) != m_Observed.end()) {
                    if (m_Observed[i].find(u) != m_Observed[i].end()) {
                        PrevObserved = m_Observed[i][u];
                    } else {
                        PrevObserved = 1;
                    }
                } else {
                    PrevObserved = 1;
                }
                double Prob = m_TransitionsProb[i][j] * PrevObserved;

                if (Prob > MaxProb) {
                    MaxProb = Prob;
                }
            }

            double AlphaJT = MulKlDiv * Sojourn * MaxProb;
            m_Observed[j][u] = AlphaJT;
            if (AlphaJT > maxAlphaJ) {
                maxAlphaJ = AlphaJT;
            }
        }

        printf("Alpha %f for event %d\n", maxAlphaJ, j);
        double AlphaJT = m_PitchKL[j][t] * maxAlphaJ;
        if (AlphaJT > BestAlphaJ) {
            BestAlphaJ = AlphaJT;
            BestEvent = j;
            BestEventFound = true;
        }
    }

    if (BestEventFound && BestEvent != m_NewCurrentEvent) {
        m_NewCurrentEvent = BestEvent;
        printf("Best Event: %d\n", BestEvent);
    }

    return m_NewCurrentEvent;
}

// ─────────────────────────────────────
double OScofoMDP::GetReward(States &PossibleStates, Description &Desc) {
    double PitchWeight;
    double TimeWeight;
    double Event = m_CurrentEvent;
    State CurrentState = PossibleStates[0];

    EventType Type = CurrentState.Type;
    double PreviousKlDiv = 0;

    for (int i = 0; i < PossibleStates.size(); i++) {
        if (PossibleStates[i].Type == NOTE) {
            double Sojourn = SojournTime(PossibleStates[i], Desc);
            double P = GetPitchSimilarity(PossibleStates[i], Desc);
            if (P > PreviousKlDiv) {
                PreviousKlDiv = P;
                Event = PossibleStates[i].Index;
            }
        } else if (PossibleStates[i].Type == ONSET) {
        }
    }

    return Event;
}

// ─────────────────────────────────────
int OScofoMDP::GetEvent(Description &Desc) {
    double BlockDur = 1 / m_Sr;
    m_TimeInThisEvent += BlockDur * m_HopSize;
    m_T += 1;

    if (!Desc.PassTreshold || m_CurrentEvent == m_States.size()) {
        return m_CurrentEvent;
    }
    if (m_CurrentEvent == -1) {
        m_BPM = m_States[0].BPMExpected;
        m_PsiN = 60 / m_BPM;
        m_MaxAheadSeconds = m_BeatsAhead * m_PsiN;
        m_Kappa = 1;
    }

    // Get the best event to describe the current state
    int Event, UpperBound = m_CurrentEvent;
    double BestReward = -1;
    double EventLookAhead = 0;
    int StatesSize = m_States.size();
    States PossibleNextStates;

    int NewUpperBound = m_CurrentEvent;
    double NewEventLookAhead = 0;

    while ((NewEventLookAhead - m_TimeInThisEvent) < (m_BeatsAhead * m_PsiN)) {
        if (NewUpperBound >= StatesSize) {
            break;
        }
        if (NewUpperBound < 0) {
            NewUpperBound = 0;
        }
        State &CurrentState = m_States[NewUpperBound];
        NewEventLookAhead += CurrentState.Duration * m_PsiN;
        m_StateWindow = NewUpperBound;
        NewUpperBound++;
    }

    while ((EventLookAhead - m_TimeInThisEvent) < (m_BeatsAhead * m_PsiN)) {
        if (UpperBound >= StatesSize) {
            break;
        }
        if (UpperBound < 0) {
            UpperBound = 0;
        }
        State &CurrentState = m_States[UpperBound];
        EventLookAhead += CurrentState.Duration * m_PsiN;
        PossibleNextStates.push_back(CurrentState);
        UpperBound++;
    }
    Event = GetReward(PossibleNextStates, Desc);
    ComputeStateTransition(Desc);

    if (Event == m_CurrentEvent) {
        return m_CurrentEvent;
    }

    // Time Decoding
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
    } else {
        LOGE() << "<== Event: " << Event << " ==>";
        m_CurrentEvent = Event;
        m_LastTn = m_Tn;
        m_Tn += m_TimeInThisEvent;
        UpdateBPM();
        m_TimeInThisEvent = 0;
        m_T = 0;
        LOGE();
        printf("Current Event: %d\n", m_CurrentEvent);
    }

    m_CurrentEvent = Event;
    return m_CurrentEvent;
}
