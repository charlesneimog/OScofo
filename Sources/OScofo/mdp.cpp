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

    // allocate memory for history
    for (int i = 0; i < m_States.size(); i++) {
        m_States[i].KLDiv.resize(1000, 0);
        m_States[i].AlphaT.resize(1000, 0);
    }

    UpdatePhaseValues();
    UpdatePitchTemplate();
    UpdateInitialProbability();

    // Values
    m_PsiN = 60.0f / m_States[0].BPMExpected;
    m_LastPsiN = 60.0f / m_States[0].BPMExpected;
    m_BeatsAhead = m_States[0].BPMExpected / 60 * 4;
    m_MaxHistory = 10000;

    int size = m_States.size();

    for (int i = 0; i < size; i++) {
        m_EventObservations[i].resize(10000 + 1, 1);
        m_AudioObservations[i].resize(10000 + 1, 1);
    }
}

// ─────────────────────────────────────
double OScofoMDP::Gaussian(double f, double mean, double sigma2) {
    return std::exp(-0.5 * std::pow((f - mean), 2) / sigma2) / std::sqrt(2 * M_PI * sigma2);
}

// ─────────────────────────────────────
void OScofoMDP::UpdatePitchTemplate() {
    m_PitchTemplateHigherBin = 0;
    int StateSize = m_States.size();
    m_PitchTemplates.clear();
    m_PitchTemplateHigherBin = 0;

    for (int h = 0; h < StateSize; h++) {
        if (m_States[h].Valid && m_States[h].Type == NOTE) {

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
    m_States[0].IOIHatPhiN = 0;
    m_States[0].IOIPhiN = 0;

    for (int i = 0; i < m_States.size() - 1; i++) {
        if (m_States[i].MarkovType == SEMIMARKOV) {
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
}

// ─────────────────────────────────────
void OScofoMDP::UpdateInitialProbability() {
    int size = std::min((int)m_States.size(), 15);

    double StatesMaxDur = 0;
    for (int i = 0; i < size; i++) {
        StatesMaxDur += m_States[i].Duration;
    }

    double Dur = 0;
    double Sum = 0;
    m_InitialProbs.resize(size);

    for (int i = 0; i < size; i++) {
        if (m_States[i].MarkovType == SEMIMARKOV) {
            double InitialProb = exp(-(Dur / StatesMaxDur));
            m_InitialProbs[i] = InitialProb;
            Dur += m_States[i].Duration;
            Sum += InitialProb;
        }
    }

    for (int i = 0; i < size; i++) {
        if (m_States[i].MarkovType == SEMIMARKOV) {
            m_InitialProbs[i] /= Sum;
            // printf("%f\n", m_InitialProbs[i]);
        }
    }

    return;
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
    UpdatePitchTemplate();
}

// ─────────────────────────────────────
void OScofoMDP::SetCurrentEvent(int Event) {
    m_CurrentStateIndex = Event;
    m_EventDetected = false;
}

// ─────────────────────────────────────
void OScofoMDP::SetPitchTemplateSigma(double f) {
    m_PitchTemplateSigma = f;
    UpdatePitchTemplate();
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
void OScofoMDP::UpdateBPM(int StateIndex) {
    if (StateIndex != m_CurrentStateIndex && StateIndex == 0) {
        // we don't run this in the first state
        double PsiK = 60 / m_States[0].BPMExpected;
        m_LastPsiN = PsiK;
        m_PsiN = PsiK;
        m_States[0].OnsetObserved = 0;
        m_BPM = m_States[0].BPMExpected;
        m_Tn = 1;
        m_TimeInThisEvent = 0;
        return;
    } else if (StateIndex == m_CurrentStateIndex) {
        // don't update if we are in the same state
        return;
    }

    // Cont (2010), Large and Palmer (1999) and Large and Jones (2002)
    if ((m_CurrentStateIndex + 1) == m_States.size()) {
        return;
    }

    State &LastState = m_States[m_CurrentStateIndex - 1];
    State &CurrentState = m_States[m_CurrentStateIndex];
    State &NextState = m_States[m_CurrentStateIndex + 1];

    double IOISeconds = m_Tn - m_LastTn;
    double LastPhiN = LastState.IOIPhiN;
    double LastHatPhiN = LastState.IOIHatPhiN;
    double HatPhiN = CurrentState.IOIHatPhiN;
    double PhiNExpected = LastPhiN + ((m_Tn - m_LastTn) / m_PsiN);
    CurrentState.IOIHatPhiN = PhiNExpected;
    CurrentState.OnsetObserved = m_Tn;

    printf("LastState PhiN %f\n", LastState.IOIPhiN);
    printf("CurrentState PhiN %f\n", CurrentState.IOIPhiN);
    printf("NextState PhiN %f\n", NextState.IOIPhiN);

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
    for (int i = m_CurrentStateIndex + 2; i < m_CurrentStateIndex + 20; i++) {
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

    // // TODO: m_Mu value | this is not necessary
    // double SumX = 0.0, SumY = 0.0;
    // for (int i = 0; i < m_CurrentStateIndex; ++i) {
    //     double PhiN = m_States[i].PhaseObserved;
    //     SumX += std::cos(PhiN);
    //     SumY += std::sin(PhiN);
    // }
    // m_Mu = ModPhases(std::atan2(SumY, SumX));

    // Update Values for next calls
    m_BPM = 60.0f / m_PsiN;
    m_LastPsiN = m_PsiN;
    m_PsiN = PsiN1;

    if (StateIndex != m_CurrentStateIndex) {
        m_TimeInThisEvent = 0;
        m_T = 0;
    }
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
void OScofoMDP::GetAudioObservations(Description &Desc, int FirstStateIndex, int LastStateIndex) {
    int T = m_T;

    // Get Pitch Template
    for (size_t j = FirstStateIndex; j < LastStateIndex; j++) {
        State &StateJ = m_States[j];
        int StateIndex = StateJ.Index;
        if (StateJ.Type == NOTE) {
            double KL = GetPitchSimilarity(StateJ, Desc);
            if (KL < 1e-8) {
                KL = 0;
            }
            StateJ.KLDiv[T] = KL;
        } else if (StateJ.Type == TRANSITION) {
            StateJ.KLDiv[T] = 0;
        }
    }
}

// ─────────────────────────────────────
double OScofoMDP::GetPitchSimilarity(State &State, Description &Desc) {
    double KLDiv = 0.0;

    // TODO: Implement CHORDS
    double RootBinFreq = round(State.Freqs[0] / (m_Sr / m_WindowSize));
    PitchTemplateArray PitchTemplate;

    if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
        PitchTemplate = m_PitchTemplates[RootBinFreq];
    } else {
        throw std::runtime_error("PitchTemplate not found");
    }

    for (size_t i = 0; i < m_WindowSize / 2; i++) {
        double P = PitchTemplate[i];
        double Q = Desc.NormSpectralPower[i] / Desc.MaxAmp;
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
    int J = m_States[m_CurrentStateIndex].Index;
    // int I = State.Index;

    double T = m_Tn + (m_BlockDur * u);
    double Duration = State.Duration;
    double Sojourn = std::exp(-(T - m_Tn) / (m_PsiN * Duration));
    return Sojourn;
}

// ─────────────────────────────────────
int OScofoMDP::MaxBlocksInState(State &State) {
    int MaxBlocksInState = State.Duration / m_BlockDur;
    return MaxBlocksInState + 1;
}

// ─────────────────────────────────────
int OScofoMDP::GetMaxLookAhead(int StateIndex) {
    int StatesSize = m_States.size();
    double EventOnset = 0;
    int MaxEvent = StateIndex;
    for (int i = StateIndex; i < StatesSize; i++) {
        if ((EventOnset) > (m_BeatsAhead * m_PsiN)) {
            MaxEvent = m_States[i].Position;
            if (MaxEvent == m_CurrentStateIndex) {
                while (MaxEvent >= StatesSize || MaxEvent >= (StateIndex + 3)) {
                    MaxEvent++;
                }
            }
            break;
        }
        EventOnset += m_States[i].Duration * m_PsiN;
    }
    return MaxEvent;
}

// ─────────────────────────────────────
MatrixMap OScofoMDP::CreateMarkovMatrix() {
    MatrixMap P;
    for (int i = m_CurrentStateIndex; i < m_MaxScoreState; i++) {
        for (int j = m_CurrentStateIndex; j < m_MaxScoreState; j++) {
            if ((i + 1) == j) {
                P[i][j] = 1;
            } else {
                P[i][j] = 0;
            }
        }
    }
    return P;
}

// ─────────────────────────────────────
double OScofoMDP::SemiMarkovState(int j, int T, MatrixMap &P) {
    State &StateJ = m_States[j];
    int StateIndex = StateJ.Index;

    // Term 1
    double Sojourn = GetSojournTime(StateJ, T + 1);
    double Obs = StateJ.KLDiv[T];
    double InitialProb = m_InitialProbs[j];
    double Temp1Val = Sojourn * Obs * InitialProb;

    // Term 2
    double MaxVal = -std::numeric_limits<double>::infinity();
    for (int u = 1; u <= T; ++u) {
        double SojournU = GetSojournTime(StateJ, u);
        double Temp2Val = SojournU * StateJ.KLDiv[T - u + 1];
        double MaxInner = -std::numeric_limits<double>::infinity();
        for (int i = m_CurrentStateIndex; i < j; ++i) {
            double JumpProb;
            if ((i + 1) == j) {
                JumpProb = 1;
            } else {
                JumpProb = 0;
            }
            if (i != j) {
                State &StateI = m_States[i];
                double PrevAlphaI = StateI.AlphaT[T - u];
                MaxInner = std::max(MaxInner, JumpProb * PrevAlphaI);
                // printf("Reading value for StateI %d | T: %d | ValueIs: %f\n", j, T - u,
                // PrevAlphaI);
            }
        }
        // printf("\n");
        Temp2Val *= MaxInner;
        MaxVal = std::max(MaxVal, Temp2Val);
    }

    double MaxOverAlphaJ = std::max(Temp1Val, MaxVal);
    StateJ.AlphaT[T] = MaxOverAlphaJ;

    return Obs;
}

// ─────────────────────────────────────
double OScofoMDP::MarkovState(int j, int T, MatrixMap &P) {
    return 0;
}

// ─────────────────────────────────────
void OScofoMDP::RotateObsValues(int Event, int BestEvent, int T) {
    if (T == m_MaxHistory && Event == BestEvent) {
        for (int j = Event; j < m_MaxScoreState + 1; j++) {
            std::copy(m_EventObservations[j].begin() + 1, m_EventObservations[j].end(),
                      m_EventObservations[j].begin());
            std::copy(m_AudioObservations[j].begin() + 1, m_AudioObservations[j].end(),
                      m_AudioObservations[j].begin());
        }
    }

    if (Event != BestEvent) {
        for (int j = Event; j < m_MaxScoreState + 1; j++) {
            m_AudioObservations[j][0] = m_AudioObservations[j][T];
            m_EventObservations[j][0] = m_EventObservations[j][T];
        }
    }
}

// ─────────────────────────────────────
int OScofoMDP::GetEvent(Description &Desc) {
    // ╭─────────────────────────────────────╮
    // │        Update initial values        │
    // ╰─────────────────────────────────────╯
    if (m_CurrentStateIndex == 0 && m_T == 0) {
        m_BPM = m_States[0].BPMExpected;
        m_PsiN = 60 / m_BPM;
        m_MaxAheadSeconds = m_BeatsAhead * m_PsiN;
        m_Kappa = 1;
    }

    // ╭─────────────────────────────────────╮
    // │           States Filter.            │
    // │  Suitably limit J and T (\tau) to   │
    // │                small                │
    // │   homogeneous zones in space and    │
    // │        time during filtering        │
    // │ as function of the latest decoding  │
    // │              position.              │
    // ╰─────────────────────────────────────╯
    m_MaxScoreState = GetMaxLookAhead(m_CurrentStateIndex);

    // ╭─────────────────────────────────────╮
    // │       Get Audio Observations        │
    // ╰─────────────────────────────────────╯
    GetAudioObservations(Desc, m_CurrentStateIndex, m_MaxScoreState);
    printf("Checking Events from %d to %d\n", m_CurrentStateIndex, m_MaxScoreState);

    // ╭─────────────────────────────────────╮
    // │    Do nothing if thereis silence    │
    // │     (need to thing about this)      │
    // ╰─────────────────────────────────────╯
    if (!Desc.PassTreshold || m_CurrentStateIndex == m_States.size()) {
        // TODO: Future I will rethink this
        return m_CurrentStateIndex;
    }

    // ╭─────────────────────────────────────╮
    // │           Get Best Event            │
    // ╰─────────────────────────────────────╯
    MatrixMap P = CreateMarkovMatrix();
    int StateIndex = m_CurrentStateIndex;
    double MaxAlpha = 0;
    double MaxAlphaJ = 0;
    int StateScoreIndex = m_CurrentStateIndex;
    bool AllZero = true;

    for (int i = m_CurrentStateIndex; i < m_MaxScoreState; i++) {
        State &StateJ = m_States[i];
        if (StateJ.MarkovType == SEMIMARKOV) {
            MaxAlpha = SemiMarkovState(i, m_T, P);
        } else if (StateJ.MarkovType == MARKOV) {
            MaxAlpha = MarkovState(i, m_T, P);
        }
        if (MaxAlpha > MaxAlphaJ) {
            AllZero = false;
            MaxAlphaJ = MaxAlpha;
            StateIndex = StateJ.Index;
        }
        // printf("%d -> %d: %f\n", m_States[m_CurrentStateIndex].Position, StateJ.Position,
        //        MaxAlphaJ);
    }

    if (AllZero && m_CurrentStateIndex == 0 && !m_EventDetected) {
        // The piece probably has not started yet.
        m_EventDetected = true;
        for (int j = m_CurrentStateIndex; j < m_MaxScoreState; j++) {
            State &StateJ = m_States[j];
            StateJ.KLDiv.resize(1000, 1);
            StateJ.AlphaT.resize(1000, 1);
        }
        return 0;
    }

    // ╭─────────────────────────────────────╮
    // │  To keep track where we are in the  │
    // │  decoding process, we need to keep  │
    // │          track of the time          │
    // ╰─────────────────────────────────────╯
    // TODO: Needs review
    if (!AllZero) {
        m_TimeInThisEvent += m_BlockDur; // seconds in this event
        m_T += 1;                        // audio block in this event
    }

    // ╭─────────────────────────────────────╮
    // │            Time Decoding            │
    // ╰─────────────────────────────────────╯
    UpdateBPM(StateIndex);

    // ╭─────────────────────────────────────╮
    // │        Return the best event        │
    // ╰─────────────────────────────────────╯
    if (m_CurrentStateIndex != StateIndex) {
        m_CurrentStateIndex = StateIndex;

        return m_States[StateIndex].Position;
    } else {
        return m_States[StateIndex].Position;
    }
}
