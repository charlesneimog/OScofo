#include "mdp.hpp"
#include "log.hpp"
#include "states.hpp"
#include <algorithm>

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

    m_BlockDur = 1 / m_Sr * m_HopSize;

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
    m_BeatsAhead = m_States[0].BPMExpected / 60 * 2;

    CreateMarkovMatrix();

    int size = m_States.size();

    for (int i = 0; i < size; i++) {
        m_EventObservations[i].resize(m_MaxHistory + 1, 1);
        m_PitchObservations[i].resize(m_MaxHistory + 1, 1);
    }
}

// ─────────────────────────────────────
void OScofoMDP::CreateMarkovMatrix() {
    int size = m_States.size();
    // TODO: REVER

    int i = -1;
    for (int i = -1; i < size; i++) {
        double Dur = 0;
        for (int j = i + 1; j < m_States.size(); j++) {
            double DurProb = exp(-5 * (Dur / m_BeatsAhead));
            double LastDur = Dur / m_BeatsAhead;
            m_TransitionsProb[i][j] = DurProb;
            Dur += m_States[j].Duration;
        }
        double Sum = 0;
        int innerSize = m_TransitionsProb[i].size();

        for (int j = i + 1; j <= i + innerSize; j++) {
            Sum += m_TransitionsProb[i][j];
        }
        for (int j = i + 1; j <= i + innerSize; j++) {
            m_TransitionsProb[i][j] /= Sum;
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
                }
            }
        }
    }
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
double OScofoMDP::GetSojournTime(State &State, int u) {
    double T = m_Tn + (m_BlockDur * u);
    double Duration = State.Duration;
    double Sojourn = std::exp(-(T - m_Tn) / (m_PsiN1 * Duration));
    return Sojourn;
}

// ─────────────────────────────────────
int OScofoMDP::MaxBlocksInState(State &State) {
    int MaxBlocksInState = State.Duration / m_BlockDur;
    return MaxBlocksInState + 1;
}

// ─────────────────────────────────────
double OScofoMDP::SemiMarkovState(Description &Desc, int j) {
    int t = m_T;
    if (m_T > m_MaxHistory) {
        t = m_MaxHistory;
    }

    double Pitch = GetPitchSimilarity(m_States[j], Desc);

    double MaxProb = 1;
    for (int u = 1; u < std::min(t, MaxBlocksInState(m_States[j])); u++) {
        // value 1
        double Obs = 1;
        for (int v = 1; v < u; v++) {
            Obs *= m_PitchObservations[j][t - v];
        }

        // value 2
        double Sojourn = GetSojournTime(m_States[j], u);

        // value 3
        double Prob = 0;
        double EventIObs;
        for (int i = m_CurrentEvent - 1; i < j; i++) {
            if (i < -1) {
                i++;
            }
            if (i != j) {
                if (i < 0) {
                    EventIObs = m_TransitionsProb[i][j];
                } else {
                    EventIObs = m_EventObservations[i][t - u];
                }
                Prob = fmax(Prob, m_TransitionsProb[i][j] * EventIObs);
            }
        }
        if (Prob != 0 && Prob != 1) {
            MaxProb = Prob;
        } else {
            MaxProb = fmax(MaxProb, Obs * Sojourn * Prob);
        }
    }

    double AlphaJ = Pitch * MaxProb;
    printf("%d -> %d: %f\n", m_CurrentEvent, j, AlphaJ);

    // Rotate the observations history
    if (m_T < m_MaxHistory) {
        m_EventObservations[j][m_T] = MaxProb;
        m_PitchObservations[j][m_T] = Pitch;
    } else {
        std::copy(m_EventObservations[j].begin() + 1, m_EventObservations[j].end(),
                  m_EventObservations[j].begin());
        std::copy(m_PitchObservations[j].begin() + 1, m_PitchObservations[j].end(),
                  m_PitchObservations[j].begin());
        m_EventObservations[j][m_MaxHistory] = MaxProb;
        m_PitchObservations[j][m_MaxHistory] = MaxProb;
    }

    return AlphaJ;
}

// ─────────────────────────────────────
double OScofoMDP::MarkovState(Description &Desc, int j) {
    // m_PitchKL[j][m_T] = GetPitchSimilarity(m_States[j], Desc);
    // m_PrevObserved[j][m_T] = AlphaJ;

    return 0;
}

// ─────────────────────────────────────
int OScofoMDP::GetBestEventIndex(Description &Desc) {
    int BestEvent = m_CurrentEvent;
    bool BestEventFound = false;

    if (m_CurrentEvent == -1) {
        m_T = 0;
        double MaxProb = 0;
        for (int j = 0; j < m_StateWindow + 1; j++) {
            double Pitch = GetPitchSimilarity(m_States[j], Desc);
            m_EventObservations[j][m_T] = m_TransitionsProb[m_CurrentEvent][j];
            m_PitchObservations[j][m_T] = Pitch;
            double Prob = m_TransitionsProb[m_CurrentEvent][j] * Pitch;
            if (Prob > MaxProb) {
                MaxProb = Prob;
                BestEvent = j;
                BestEventFound = true;
            }
        }
    } else {
        double BestAlphaJ = 0;
        for (int j = m_CurrentEvent; j < m_StateWindow + 1; j++) {
            double AlphaJ;
            if (m_States[j].MarkovType == SEMIMARKOV) {
                AlphaJ = SemiMarkovState(Desc, j);
            } else if (m_States[j].MarkovType == MARKOV) {
                AlphaJ = MarkovState(Desc, j);
            }
            if (AlphaJ > BestAlphaJ) {
                BestAlphaJ = AlphaJ;
                BestEvent = j;
                BestEventFound = true;
            }
        }
    }
    printf("BestEvent: %d\n", BestEvent + 1);
    printf("\n\n");
    return BestEvent;
}

// ─────────────────────────────────────
int OScofoMDP::GetEvent(Description &Desc) {
    m_TimeInThisEvent += m_BlockDur;
    m_T += 1;
    m_AudioTick += 1;

    if (!Desc.PassTreshold || m_CurrentEvent == m_States.size()) {
        return m_CurrentEvent;
    }

    if (m_CurrentEvent == -1) {
        m_BPM = m_States[0].BPMExpected;
        m_PsiN = 60 / m_BPM;
        m_MaxAheadSeconds = m_BeatsAhead * m_PsiN;
        m_Kappa = 1;
    }

    int StatesSize = m_States.size();
    int NewUpperBound = m_CurrentEvent;
    double NewEventLookAhead = 0;

    while ((NewEventLookAhead - m_TimeInThisEvent) < (m_BeatsAhead * m_PsiN)) {
        if (NewUpperBound >= StatesSize) {
            break;
        }
        if (NewUpperBound < 0) {
            NewUpperBound = 0;
        }
        m_StateWindow = NewUpperBound;
        NewUpperBound++;
        State &State = m_States[NewUpperBound];
        NewEventLookAhead += State.Duration * m_PsiN;
    }

    int Event = GetBestEventIndex(Desc);

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
    }

    m_CurrentEvent = Event;
    return m_CurrentEvent;
}
