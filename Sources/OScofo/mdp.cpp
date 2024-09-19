#include "mdp.hpp"
#include "log.hpp"

#include <boost/math/special_functions/bessel.hpp>

#define BUFFER_SIZE 1000

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
OScofoMDP::OScofoMDP(float Sr, float FFTSize, float HopSize) {
    m_HopSize = HopSize;
    m_FFTSize = FFTSize;
    m_Sr = Sr;

    if (m_FFTSize / 2 != m_PitchTemplate.size()) {
        m_PitchTemplate.resize(m_FFTSize / 2);
    }

    m_AccumulationFactor = 0.5;
    m_CouplingStrength = 0.5;
    m_BlockDur = (1 / m_Sr) * HopSize;
    m_TimeInPrevEvent = 0;

    SetTunning(440);
}

// ─────────────────────────────────────
void OScofoMDP::SetScoreStates(States ScoreStates) {
    m_States.clear();
    m_States = ScoreStates;

    // double Value2 = StateJ.In[t] * StateJ.Forward[t - 1] + StateJ.Norm[t - 1];
    // allocate memory for history
    for (int i = 0; i < m_States.size(); i++) {
        m_States[i].Obs.resize(BUFFER_SIZE + 1, 0);
        m_States[i].AlphaT.resize(BUFFER_SIZE + 1, 0);
    }

    m_CurrentStateIndex = -1;
    m_Kappa = 1;
    m_BPM = m_States[0].BPMExpected;
    m_PsiN = 60.0f / m_States[0].BPMExpected;
    m_PsiN1 = 60.0f / m_States[0].BPMExpected;
    m_LastPsiN = 60.0f / m_States[0].BPMExpected;
    m_BeatsAhead = m_States[0].BPMExpected / 60 * 2;
    m_CurrentStateIndex = -1;
    m_SyncStr = 0;

    UpdatePitchTemplate();
    UpdatePhaseValues();
}

// ─────────────────────────────────────
void OScofoMDP::UpdatePitchTemplate() {
    int StateSize = m_States.size();
    m_PitchTemplates.clear();

    for (int h = 0; h < StateSize; h++) {
        if (m_States[h].Valid && m_States[h].Type == NOTE) {
            // TODO: Implement CHORDS
            double Pitch = m_States[h].Freqs[0];
            double RootBinFreq = round(Pitch / (m_Sr / m_FFTSize));
            if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
                continue;
            }
            m_PitchTemplates[RootBinFreq].resize(m_FFTSize / 2);
            double Sigma = m_PitchTemplateSigma;
            for (int k = 1; k <= m_Harmonics; ++k) {
                double harmonicFreqBin = RootBinFreq * k;
                for (size_t i = 0; i < m_FFTSize / 2; ++i) { // FFT bin loop (i)
                    double gaussian = (1 / std::sqrt(2 * M_PI * Sigma)) * std::exp(-std::pow(i - harmonicFreqBin, 2) / (2 * Sigma * Sigma));
                    double envelope = 1 / (std::pow(2, k)); // TODO: FIX THE AMP IN THE SIMILARY FUNCTION
                    double noise = 0.00001 * (rand() % 100) / 100.0;
                    m_PitchTemplates[RootBinFreq][i] += (envelope * gaussian) + noise;
                }
            }
        }
    }
}

// ─────────────────────────────────────
std::vector<double> OScofoMDP::GetPitchTemplate(double Freq, int Harmonics, double Sigma) {
    double Pitch = Freq;
    double RootBinFreq = Pitch / (m_Sr / m_FFTSize);        // Fundamental frequency bin
    std::vector<double> PitchTemplates(m_FFTSize / 2, 0.0); // Initialize with zero

    for (int k = 1; k <= Harmonics; ++k) {
        double harmonicFreqBin = RootBinFreq * k;
        for (size_t i = 0; i < m_FFTSize / 2; ++i) { // FFT bin loop (i)
            double gaussian = (1 / std::sqrt(2 * M_PI * Sigma)) * std::exp(-std::pow(i - harmonicFreqBin, 2) / (2 * Sigma * Sigma));
            double envelope = 1 / (std::pow(2, k)); // TODO: FIX THE AMP IN THE SIMILARY FUNCTION
            double noise = 0.00001 * (rand() % 100) / 100.0;
            PitchTemplates[i] += (envelope * gaussian) + noise;
        }
    }

    return PitchTemplates;
}

// ─────────────────────────────────────
void OScofoMDP::UpdatePhaseValues() {
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
double OScofoMDP::GetKappa() {
    return m_Kappa;
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
int OScofoMDP::GetTunning() {
    return m_Tunning;
}

// ─────────────────────────────────────
void OScofoMDP::SetCurrentEvent(int Event) {
    m_CurrentStateIndex = Event;
    m_EventDetected = false;
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
int OScofoMDP::GetMaxLookAhead(int StateIndex) {
    // BUG: NOT WORKING
    int StatesSize = m_States.size();
    int MaxEvent = StateIndex;
    double EventOnset = 0;

    for (int i = StateIndex; i < StatesSize; i++) {
        if ((EventOnset) > (m_BeatsAhead * m_PsiN)) {
            MaxEvent = m_States[i].Position;
            if (MaxEvent == m_CurrentStateIndex) {
                while (MaxEvent < StateIndex + 1 && MaxEvent < StatesSize) {
                    MaxEvent++;
                }
            }
            break;
        }
        EventOnset += m_States[i].Duration * m_PsiN;
        MaxEvent = i;
    }
    return MaxEvent;
}

// ─────────────────────────────────────
void OScofoMDP::UpdateBPM(int StateIndex) {
    if (StateIndex == m_CurrentStateIndex) {
        m_TimeInPrevEvent += m_BlockDur;
        m_T += 1;
        return;
    } else {
        if (StateIndex == 0) {
            double PsiK = 60 / m_States[0].BPMExpected;
            m_LastPsiN = PsiK;
            m_PsiN = PsiK;
            m_PsiN1 = PsiK;
            m_States[0].OnsetObserved = 0;
            m_BPM = m_States[0].BPMExpected;
            m_CurrentStateOnset = 0;
            m_LastTn = 0;
            m_TimeInPrevEvent = 0;
            return;
        } else {
            m_TimeInPrevEvent += m_BlockDur;
            m_LastTn = m_CurrentStateOnset;
            m_CurrentStateOnset += m_TimeInPrevEvent;
        }
    }

    // Cont (2010), Large and Palmer (1999) and Large and Jones (2002)
    State &LastState = m_States[StateIndex - 1];
    State &CurrentState = m_States[StateIndex];
    State &NextState = m_States[StateIndex + 1];

    double IOISeconds = m_CurrentStateOnset - m_LastTn;
    double LastPhiN = LastState.IOIPhiN;
    double LastHatPhiN = LastState.IOIHatPhiN;
    double HatPhiN = CurrentState.IOIHatPhiN;
    double PhiNExpected = LastPhiN + ((m_CurrentStateOnset - m_LastTn) / m_PsiN);
    CurrentState.IOIHatPhiN = PhiNExpected;
    CurrentState.OnsetObserved = m_CurrentStateOnset;

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
    double Tn1 = m_CurrentStateOnset + CurrentState.Duration * PsiN1;
    double PhiN1 = ModPhases((Tn1 - m_CurrentStateOnset) / PsiN1);
    NextState.IOIHatPhiN = PhiN1;

    // Update all next expected onsets
    NextState.OnsetExpected = Tn1;
    double LastOnsetExpected = Tn1;

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

    // Update Values for next calls
    m_BPM = 60.0f / m_PsiN;
    m_LastPsiN = m_PsiN;
    m_PsiN = PsiN1;

    if (StateIndex != m_CurrentStateIndex) {
        m_TimeInPrevEvent = 0;
        // m_T = 0;
    }
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
void OScofoMDP::GetAudioObservations(Description &Desc, int FirstStateIndex, int LastStateIndex, int T) {
    for (int j = FirstStateIndex; j <= LastStateIndex; j++) {
        if (j < 0) {
            continue;
        }
        State &StateJ = m_States[j];
        int BufferIndex = (T % BUFFER_SIZE);
        if (StateJ.Type == NOTE) {
            double KL = GetPitchSimilarity(StateJ, Desc);
            StateJ.Obs[BufferIndex] = KL;
        } else if (StateJ.Type == REST) {
            StateJ.Obs[BufferIndex] = 1 - Desc.Amp;
        }
    }
}

// ─────────────────────────────────────
double OScofoMDP::GetPitchSimilarity(State &State, Description &Desc) {
    double KLDiv = 0.0;

    // TODO: Implement CHORDS
    double RootBinFreq = round(State.Freqs[0] / (m_Sr / m_FFTSize));
    PitchTemplateArray PitchTemplate;

    if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
        PitchTemplate = m_PitchTemplates[RootBinFreq];
    } else {
        throw std::runtime_error("PitchTemplate not found for " + std::to_string(State.Freqs[0]) + ", this should not happen, please report");
    }

    for (size_t i = 0; i < m_FFTSize / 2; i++) {
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
double OScofoMDP::GetInitialDistribution(int CurrentState, int j) {
    int Size = m_MaxScoreState - CurrentState;
    std::vector<double> InitialProb(Size);

    int i = -1;
    double Dur = 0;
    double Sum = 0;
    for (int i = m_CurrentStateIndex; i < m_MaxScoreState; i++) {
        int index = i - m_CurrentStateIndex;
        double DurProb = exp(-0.5 * (Dur / m_BeatsAhead));
        double LastDur = Dur / m_BeatsAhead;
        InitialProb[index] = DurProb;
        Dur += m_States[j].Duration;
        Sum += DurProb;
    }

    // normalize
    for (int i = 0; i < Size; i++) {
        InitialProb[i] /= Sum;
    }

    int index = j - m_CurrentStateIndex;

    return InitialProb[index];
}

// ─────────────────────────────────────
double OScofoMDP::GetTransProbability(int i, int j) {
    // simplest markov
    if (i + 1 == j) {
        return 1;
    } else {
        return 0;
    }
}

// ─────────────────────────────────────
double OScofoMDP::GetSojournTime(State &State, int u) {
    double T = m_LastTn + (m_BlockDur * u);
    double Duration = State.Duration;
    double Sojourn = std::exp(-(T - m_LastTn) / (m_PsiN1 * Duration));
    return Sojourn;
}

// ─────────────────────────────────────
int OScofoMDP::GetMaxUForJ(State &StateJ) {
    double MaxU = StateJ.Duration / m_BlockDur;
    int MaxUInt = round(MaxU);
    return MaxUInt;
}

// ─────────────────────────────────────
int OScofoMDP::Inference(int CurrentState, int MaxState, int T) {
    double MaxValue = -std::numeric_limits<double>::infinity();
    int BestState = CurrentState;

    // Initialize AlphaT buffer with a fixed size and rotate indices
    for (auto &state : m_States) {
        if (state.AlphaT.size() != BUFFER_SIZE) {
            state.AlphaT.resize(BUFFER_SIZE, 0);
        }
    }

    for (int j = CurrentState; j <= MaxState; j++) {
        if (j < 0)
            continue;
        State &StateJ = m_States[j];
        int bufferIndex = T % BUFFER_SIZE; // Circular buffer index
        if (StateJ.Markov == SEMIMARKOV) {
            if (T == 0) {
                StateJ.AlphaT[bufferIndex] = StateJ.Obs[bufferIndex] * GetSojournTime(StateJ, T + 1) * StateJ.InitProb;
            } else {
                double Obs = StateJ.Obs[bufferIndex];
                double MaxAlpha = -std::numeric_limits<double>::infinity();
                for (int u = 1; u <= std::min(T, GetMaxUForJ(StateJ)); u++) {
                    double ProbPrevObs = 1.0;
                    for (int v = 1; v < u; v++) {
                        int PrevIndex = (bufferIndex - v + BUFFER_SIZE) % BUFFER_SIZE;
                        ProbPrevObs *= StateJ.Obs[PrevIndex];
                    }
                    double Sur = GetSojournTime(StateJ, u);

                    double MaxTrans = -std::numeric_limits<double>::infinity();
                    for (int i = CurrentState - 1; i <= j; i++) {
                        if (i >= 0 && i != j) {
                            State &StateI = m_States[i];
                            int PrevIndex = (bufferIndex - u + BUFFER_SIZE) % BUFFER_SIZE;
                            MaxTrans = std::max(MaxTrans, GetTransProbability(i, j) * StateI.AlphaT[PrevIndex]);
                        }
                    }
                    double MaxResult = ProbPrevObs * Sur * MaxTrans;
                    MaxAlpha = std::max(MaxAlpha, MaxResult);
                }
                StateJ.AlphaT[bufferIndex] = Obs * MaxAlpha;
            }
        }
        // Handle Markov
        else if (StateJ.Markov == MARKOV) {
            if (T == 0) {
                StateJ.AlphaT[bufferIndex] = StateJ.Obs[bufferIndex] * StateJ.InitProb;
            } else {
                double Obs = StateJ.Obs[bufferIndex];
                double MaxAlpha = -std::numeric_limits<double>::infinity();
                for (int i = CurrentState - 1; i <= j; i++) {
                    if (i >= 0) {
                        int prevIndex = (bufferIndex - 1 + BUFFER_SIZE) % BUFFER_SIZE;
                        double Value = GetTransProbability(i, j) * m_States[i].AlphaT[prevIndex];
                        MaxAlpha = std::max(MaxAlpha, Value);
                    }
                }
                StateJ.AlphaT[bufferIndex] = Obs * MaxAlpha;
            }
        }

        if (StateJ.AlphaT[bufferIndex] > MaxValue) {
            MaxValue = StateJ.AlphaT[bufferIndex];
            BestState = j;
        }
    }

    return BestState;
}

// ─────────────────────────────────────
int OScofoMDP::GetEvent(Description &Desc) {
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
    GetAudioObservations(Desc, m_CurrentStateIndex - 1, m_MaxScoreState, m_T);

    // ╭─────────────────────────────────────╮
    // │    Do nothing if thereis silence    │
    // │     (need to thing about this)      │
    // ╰─────────────────────────────────────╯
    if (Desc.Silence || m_CurrentStateIndex == m_States.size()) {
        if (m_CurrentStateIndex == -1) {
            return 0;
        }
        // TODO: Future I will rethink this
        return m_States[m_CurrentStateIndex].Position;
    }

    // ╭─────────────────────────────────────╮
    // │           Get Best Event            │
    // ╰─────────────────────────────────────╯
    int StateIndex = m_CurrentStateIndex;
    double MaxAlpha = 0;

    double Survival = 0;
    if (m_CurrentStateIndex > -1) {
        Survival = GetSojournTime(m_States[m_CurrentStateIndex], m_T);
    }

    double AlphaSum = 0;
    for (int j = m_CurrentStateIndex; j < m_MaxScoreState; j++) {
        State &StateJ = m_States[j];
        StateJ.InitProb = GetInitialDistribution(m_CurrentStateIndex, j);
    }

    StateIndex = Inference(m_CurrentStateIndex, m_MaxScoreState, m_T);

    if (StateIndex == -1) {
        return 0;
    }

    // ╭─────────────────────────────────────╮
    // │            Time Decoding            │
    // ╰─────────────────────────────────────╯
    UpdateBPM(StateIndex);

    // ╭─────────────────────────────────────╮
    // │        Return the best event        │
    // ╰─────────────────────────────────────╯
    if (m_CurrentStateIndex == StateIndex) {
        return m_States[StateIndex].Position;
    } else {
        m_CurrentStateIndex = StateIndex;
        return m_States[StateIndex].Position;
    }
}
