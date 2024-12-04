#include "mdp.hpp"
#include "log.hpp"

#include <boost/math/special_functions/bessel.hpp>

#define BUFFER_SIZE 1000

namespace OScofo {

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
MDP::MDP(float Sr, float FFTSize, float HopSize) {
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
void MDP::SetScoreStates(States ScoreStates) {
    if (ScoreStates.size() == 0) {
        throw std::runtime_error("ScoreStates is empty");
        return;
    }

    m_States.clear();
    m_States = ScoreStates;

    for (int i = 0; i < m_States.size(); i++) {
        m_States[i].Obs.resize(BUFFER_SIZE + 1, 0);
        m_States[i].Forward.resize(BUFFER_SIZE + 1, 0);
    }

    m_CurrentStateIndex = -1;
    m_Kappa = 1;
    m_BPM = m_States[0].BPMExpected;
    m_PsiN = 60.0f / m_States[0].BPMExpected;
    m_PsiN1 = 60.0f / m_States[0].BPMExpected;
    m_LastPsiN = 60.0f / m_States[0].BPMExpected;
    m_BeatsAhead = m_States[0].BPMExpected / 60 * m_SecondsAhead;
    m_CurrentStateIndex = -1;
    m_SyncStr = 0;

    UpdatePitchTemplate();
    UpdatePhaseValues();
}

// ─────────────────────────────────────
void MDP::UpdatePitchTemplate() {
    int StateSize = m_States.size();
    m_PitchTemplates.clear();

    for (int h = 0; h < StateSize; h++) {
        if (m_States[h].Type == NOTE || m_States[h].Type == TRILL) {
            for (auto Pitch : m_States[h].Freqs) {
                double RootBinFreq = round(Pitch / (m_Sr / m_FFTSize));
                if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
                    continue;
                }
                m_PitchTemplates[RootBinFreq].resize(m_FFTSize / 2);
                double Sigma = m_PitchTemplateSigma;

                for (int k = 1; k <= m_Harmonics; ++k) {
                    double harmonicFreqBin = RootBinFreq * k;
                    double harmonicFreqHz = harmonicFreqBin * (m_Sr / m_FFTSize);
                    // make sigma be constant for all harmonics (from logarithm to linear)
                    double HSigma = Sigma;
                    for (size_t i = 0; i < m_FFTSize / 2; ++i) { // FFT bin loop (i)
                        double gaussian = (1 / std::sqrt(2 * M_PI * HSigma)) * std::exp(-std::pow(i - harmonicFreqBin, 2) / (2 * HSigma * HSigma));
                        double envelope = 1 / (std::pow(2, k)); // TODO: FIX THE AMP IN THE SIMILARY FUNCTION
                        double noise = 0.00001 * (rand() % 100) / 100.0;
                        m_PitchTemplates[RootBinFreq][i] += (envelope * gaussian) + noise;
                    }
                }
            }
        }
    }
}

// ─────────────────────────────────────
std::unordered_map<double, PitchTemplateArray> MDP::GetPitchTemplate() {
    if (m_PitchTemplates.size() == 0) {
        throw std::runtime_error("PitchTemplates is empty");
    }
    return m_PitchTemplates;
}

// ─────────────────────────────────────
void MDP::UpdatePhaseValues() {
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void MDP::ClearStates() {
    m_States.clear();
}
// ─────────────────────────────────────
double MDP::GetLiveBPM() {
    return m_BPM;
}

// ─────────────────────────────────────
double MDP::GetKappa() {
    return m_Kappa;
}

// ─────────────────────────────────────
void MDP::SetBPM(double BPM) {
    m_BPM = BPM;
}

// ─────────────────────────────────────
void MDP::SetdBTreshold(double dB) {
    m_dBTreshold = dB;
}

// ─────────────────────────────────────
void MDP::SetTunning(double Tunning) {
    m_Tunning = Tunning;
}

// ─────────────────────────────────────
void MDP::SetHarmonics(int Harmonics) {
    m_Harmonics = Harmonics;
}

// ─────────────────────────────────────
int MDP::GetTunning() {
    return m_Tunning;
}

// ─────────────────────────────────────
void MDP::SetCurrentEvent(int Event) {
    m_CurrentStateIndex = Event;
    m_EventDetected = false;
}

// ─────────────────────────────────────
int MDP::GetStatesSize() {
    return m_States.size();
}
// ─────────────────────────────────────
void MDP::AddState(MacroState State) {
    m_States.push_back(State);
}
// ─────────────────────────────────────
MacroState MDP::GetState(int Index) {
    return m_States[Index];
}

// ─────────────────────────────────────
void MDP::SetPitchTemplateSigma(double f) {
    m_PitchTemplateSigma = f;
}

// ─────────────────────────────────────
void MDP::SetTimeAccumFactor(double f) {
    m_AccumulationFactor = f;
}

// ─────────────────────────────────────
void MDP::SetTimeCouplingStrength(double f) {
    m_CouplingStrength = f;
}

// ╭─────────────────────────────────────╮
// │            Time Decoding            │
// ╰─────────────────────────────────────╯
double MDP::InverseA2(double SyncStrength) {
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
double MDP::CouplingFunction(double Phi, double PhiMu, double Kappa) {
    // Equation 2b from Large and Palmer (2002)
    double ExpKappa = exp(Kappa);
    double PhiNDiff = Phi - PhiMu;
    double CosTerm = cos(TWO_PI * PhiNDiff);
    double SinTerm = sin(TWO_PI * PhiNDiff);
    double PhiN = (1 / (TWO_PI * ExpKappa)) * exp(Kappa * CosTerm) * SinTerm;
    return PhiN;
}

// ─────────────────────────────────────
double MDP::ModPhases(double Phase) {
    // Following Cont (2010) conventions
    Phase = fmod(Phase + M_PI, TWO_PI);
    if (Phase < 0) {
        Phase += TWO_PI;
    }
    return Phase - M_PI;
}

// ─────────────────────────────────────
int MDP::GetMaxJIndex(int StateIndex) {
    if (StateIndex == -1) {
        return 1;
    }

    int StatesSize = m_States.size();
    double TimeInCurrEvt = m_States[StateIndex].Duration - (m_TimeInPrevEvent + m_BlockDur);
    double EventOnset = TimeInCurrEvt;
    int MaxJ = StateIndex + 1;
    for (int i = StateIndex + 1; i < m_States.size(); i++) {
        if (EventOnset > m_SecondsAhead) {
            MaxJ = i;
            break;
        } else {
            EventOnset += m_States[i].Duration;
        }
    }
    return MaxJ;
}

// ─────────────────────────────────────
double MDP::UpdatePsiN(int StateIndex) {
    if (StateIndex == m_CurrentStateIndex) {
        m_TimeInPrevEvent += m_BlockDur;
        m_Tau += 1;
        return m_PsiN;
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
            m_Tau = 0;
            return m_PsiN;
        } else {
            m_TimeInPrevEvent += m_BlockDur;
            m_LastTn = m_CurrentStateOnset;
            m_CurrentStateOnset += m_TimeInPrevEvent;
        }
    }

    // Cont (2010), Large and Palmer (1999) and Large and Jones (2002)
    MacroState &LastState = m_States[StateIndex - 1];
    MacroState &CurrentState = m_States[StateIndex];
    MacroState &NextState = m_States[StateIndex + 1];

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
        MacroState &FutureState = m_States[i];
        MacroState &PreviousFutureState = m_States[(i - 1)];
        double Duration = PreviousFutureState.Duration;
        double FutureOnset = LastOnsetExpected + Duration * PsiN1;

        FutureState.OnsetExpected = FutureOnset;
        LastOnsetExpected = FutureOnset;
    }

    // Update Values for next calls
    m_BPM = 60.0f / m_PsiN;
    m_LastPsiN = m_PsiN;

    if (StateIndex != m_CurrentStateIndex) {
        m_TimeInPrevEvent = 0;
        m_Tau = 0;
    }
    return PsiN1;
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
void MDP::GetAudioObservations(Description &Desc, int FirstStateIndex, int LastStateIndex, int T) {
    for (int j = FirstStateIndex; j <= LastStateIndex; j++) {
        if (j < 0) {
            continue;
        }
        MacroState &StateJ = m_States[j];
        int BufferIndex = (T % BUFFER_SIZE);
        if (StateJ.Type == NOTE) {
            double KL = GetPitchSimilarity(StateJ.Freqs[0], Desc);
            StateJ.Obs[BufferIndex] = KL;
        } else if (StateJ.Type == REST) {
            StateJ.Obs[BufferIndex] = Desc.Amp;
        } else if (StateJ.Type == TRILL) {
            double bestProb = 0;
            for (int i = 0; i < StateJ.Freqs.size(); i++) {
                double KL = GetPitchSimilarity(StateJ.Freqs[i], Desc);
                if (KL > bestProb) {
                    bestProb = KL;
                }
            }
            StateJ.Obs[BufferIndex] = bestProb;
        }
    }
}

// ─────────────────────────────────────
double MDP::GetPitchSimilarity(double Freq, Description &Desc) {
    double KLDiv = 0.0;

    // TODO: Implement CHORDS
    double RootBinFreq = round(Freq / (m_Sr / m_FFTSize));
    PitchTemplateArray PitchTemplate;

    if (m_PitchTemplates.find(RootBinFreq) != m_PitchTemplates.end()) {
        PitchTemplate = m_PitchTemplates[RootBinFreq];
    } else {
        throw std::runtime_error("PitchTemplate not found for " + std::to_string(Freq) + ", this should not happen, please report");
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

    KLDiv = exp(-m_PitchScalingFactor * KLDiv);

    return KLDiv;
}
// ─────────────────────────────────────
std::vector<double> MDP::GetInitialDistribution() {
    int Size = m_MaxScoreState - m_CurrentStateIndex;
    std::vector<double> InitialProb(Size);

    double Dur = 0;
    double Sum = 0;

    for (int i = 0; i < Size; i++) {
        double DurProb = exp(-0.5 * (Dur / m_BeatsAhead));
        InitialProb[i] = DurProb;
        Dur += m_States[m_CurrentStateIndex + i].Duration; // Accumulate duration
        Sum += DurProb;
    }

    // Normalize
    for (int i = 0; i < Size; i++) {
        InitialProb[i] /= Sum;
    }

    return InitialProb;
}

double MDP::GetInitialDistribution(int CurrentState, int j) {
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
double MDP::GetTransProbability(int i, int j) {
    // simplest markov
    if (i + 1 == j) {
        return 1;
    } else {
        return 0;
    }
}

// ─────────────────────────────────────
double MDP::GetSojournTime(MacroState &State, int u) {
    double T = m_LastTn + (m_BlockDur * u);
    double Duration = State.Duration;
    double Sojourn = std::exp(-(T - m_LastTn) / (m_PsiN1 * Duration));
    return Sojourn;
}

// ─────────────────────────────────────
int MDP::GetMaxUForJ(MacroState &StateJ) {
    double MaxU = StateJ.Duration / m_BlockDur;
    int MaxUInt = round(MaxU);
    return MaxUInt;
}

// ─────────────────────────────────────
double MDP::GaussianProbTimeOnset(int j, int T, double Sigma) {
    MacroState &StateJ = m_States[j];
    double Onset = std::ceil((StateJ.OnsetExpected - m_LastTn) / m_BlockDur);
    double Gaussian = std::exp(-((T - Onset) * (T - Onset)) / (2 * Sigma * Sigma));
    return Gaussian + 1e-100; // 1e-10.5;
}

// ─────────────────────────────────────
void MDP::SemiMarkov(MacroState &StateJ, int CurrentState, int j, int T, int bufferIndex) {
    if (T == 0) {
        StateJ.Forward[bufferIndex] = StateJ.Obs[bufferIndex] * GetSojournTime(StateJ, T + 1) * StateJ.InitProb;
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
            for (int i = CurrentState; i <= j; i++) {
                if (i < 0) {
                    continue;
                }
                MacroState &StateI = m_States[i];
                if (i != j) {
                    int PrevIndex = (T - u) % BUFFER_SIZE;
                    MaxTrans = std::max(MaxTrans, GetTransProbability(i, j) * StateI.Forward[PrevIndex]);
                } else {
                    // TODO: Using the concept of semimarkov of Guédon, maybe here we can create sub-audio-descriptions
                    int PrevIndex = (T - u) % BUFFER_SIZE;
                    MaxTrans = std::max(MaxTrans, StateJ.Forward[PrevIndex]);
                }
            }
            double MaxResult = ProbPrevObs * Sur * MaxTrans;
            MaxAlpha = std::max(MaxAlpha, MaxResult);
        }
        StateJ.Forward[bufferIndex] = Obs * MaxAlpha;
    }
}

// ─────────────────────────────────────
void MDP::Markov(MacroState &StateJ, int CurrentState, int j, int T, int bufferIndex) {
    if (T == 0) {
        StateJ.Forward[bufferIndex] = StateJ.Obs[bufferIndex] * StateJ.InitProb;
    } else {
        double Obs = StateJ.Obs[bufferIndex];
        double MaxAlpha = -std::numeric_limits<double>::infinity();
        for (int i = CurrentState; i <= j; i++) {
            if (i >= 0) {
                int prevIndex = (bufferIndex - 1 + BUFFER_SIZE) % BUFFER_SIZE;
                double Value = GetTransProbability(i, j) * m_States[i].Forward[prevIndex];
                MaxAlpha = std::max(MaxAlpha, Value);
            }
        }
        StateJ.Forward[bufferIndex] = Obs * MaxAlpha;
    }
}

// ─────────────────────────────────────
int MDP::Inference(int CurrentState, int MaxState, int T) {
    double MaxValue = -std::numeric_limits<double>::infinity();
    int BestState = CurrentState;
    int bufferIndex = T % BUFFER_SIZE;

    for (int j = CurrentState; j <= MaxState; j++) {
        if (j < 0)
            continue;
        MacroState &StateJ = m_States[j];

        if (StateJ.Markov == SEMIMARKOV) {
            SemiMarkov(StateJ, CurrentState, j, T, bufferIndex);
        } else if (StateJ.Markov == MARKOV) {
            Markov(StateJ, CurrentState, j, T, bufferIndex);
        }

        if (StateJ.Forward[bufferIndex] > MaxValue) {
            MaxValue = StateJ.Forward[bufferIndex];
            BestState = j;
        }
    }
    return BestState;
}

// ─────────────────────────────────────
int MDP::GetEvent(Description &Desc) {
    m_MaxScoreState = GetMaxJIndex(m_CurrentStateIndex);
    GetAudioObservations(Desc, m_CurrentStateIndex - 1, m_MaxScoreState, m_Tau);

    if (Desc.Silence || m_CurrentStateIndex == m_States.size()) {
        if (m_CurrentStateIndex == -1) {
            return 0;
        }
        return m_States[m_CurrentStateIndex].ScorePos;
    }

    if (m_Tau == 0) {
        std::vector<double> InitialProb = GetInitialDistribution();
        for (int j = m_CurrentStateIndex; j < m_MaxScoreState; j++) {
            MacroState &StateJ = m_States[j];
            StateJ.InitProb = InitialProb[j - m_CurrentStateIndex];
        }
    }

    // Inference
    int StateIndex = Inference(m_CurrentStateIndex, m_MaxScoreState, m_Tau);
    if (StateIndex == -1) {
        return 0;
    }
    m_PsiN = UpdatePsiN(StateIndex); // Time Update

    // Return Score Position
    if (m_CurrentStateIndex == StateIndex) {
        m_CurrentStateIndex = StateIndex;
        return m_States[StateIndex].ScorePos;
    } else {
        m_CurrentStateIndex = StateIndex;
        return m_States[StateIndex].ScorePos;
    }
}
} // namespace OScofo
