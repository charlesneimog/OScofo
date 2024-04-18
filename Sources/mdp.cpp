#include "follower.hpp"
#include <algorithm>
#include <math.h>
#include <numeric> // for std::accumulate

#define MAX_FREQUENCY_DIFFERENCE 40.0
#define MAX_QUALITY_DIFFERENCE 0.5

// ─────────────────────────────────────
FollowerMDP::FollowerMDP() {
    Desc = new FollowerMIR::Description();
    BpmHistory.assign(20, 1);
}

// ─────────────────────────────────────
void FollowerMDP::SetMinQualityForNote(float minQuality) {
    MinQualityForNote = minQuality;
}

// ─────────────────────────────────────
float FollowerMDP::GetLiveBpm() {
    return LiveBpm;
}

// ─────────────────────────────────────
void FollowerMDP::SetLiveBpm(float Bpm) {
    LiveBpm = Bpm;
}

// ─────────────────────────────────────
void FollowerMDP::ResetLiveBpm() {
    BpmHistory.assign(20, 1);
}

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
float FollowerMDP::GetPitchSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {

    float NextMidi = NextPossibleState.Midi;
    float DescMidi = Desc->Midi;
    float NextFreq = Follower_midi2f(NextMidi, Tunning);
    float DescFreq = Desc->Freq;
    float Distance = abs(DescFreq - NextFreq);
    float Similarity = Distance / MAX_FREQUENCY_DIFFERENCE;
    if (Similarity > 1.0) {
        return 0;
    }
    Similarity = 1.0 - (Distance / MAX_FREQUENCY_DIFFERENCE);
    return Similarity;
    return 0;
}

// ─────────────────────────────────────
float FollowerMDP::GetTimeSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {

    float Similarity = 0.0;
    float CorrectedDur = NextPossibleState.Duration * (60000.0f / LiveBpm);

    if (CurrentEvent == NextPossibleState.Id) {
        float margin = 0.2f * Desc->TimeElapsed;
        float minTime = Desc->TimeElapsed - margin;
        float maxTime = Desc->TimeElapsed + margin;
        if (CorrectedDur >= minTime && CorrectedDur <= maxTime) {
            Similarity = 1.0f; // Adjust weight as needed
        }

    } else if (NextPossibleState.Id == CurrentEvent + 1) {
        // Higher probability if correctedDur is within 20% higher or lower
        // than elapsedTime
        float margin = 0.2f * Desc->TimeElapsed;
        float minTime = Desc->TimeElapsed - margin;
        float maxTime = Desc->TimeElapsed + margin;
        if (CorrectedDur >= minTime && CorrectedDur <= maxTime) {
            Similarity = 1.0f;
        }
    } else if (NextPossibleState.Id > CurrentEvent + 1) {
        // Higher probability if correctedDur is within 20% higher or lower
        // than elapsedTime
        float margin = 0.2f * Desc->TimeElapsed;
        float minTime = Desc->TimeElapsed - margin;
        float maxTime = Desc->TimeElapsed + margin;
        if (CorrectedDur >= minTime && CorrectedDur <= maxTime) {
            Similarity = -100.f;
        }
    }
    return Similarity;
}

// ─────────────────────────────────────
float FollowerMDP::GetSimilarity(State NextPossibleState, FollowerMIR::Description *Desc) {
    float PitchWeight = 0.7;
    float TimeWeight = 0.3;

    float PitchSimilarity = GetPitchSimilarity(NextPossibleState, Desc);
    float TimeSimilarity = GetTimeSimilarity(NextPossibleState, Desc);

    float Similarity = PitchWeight * PitchSimilarity + TimeWeight * TimeSimilarity;

    return PitchSimilarity;
}

// ─────────────────────────────────────
float FollowerMDP::GetBestEvent(std::vector<State> States, FollowerMIR::Description *Desc) {
    float BestGuess = CurrentEvent;
    State CurState = States[CurrentEvent];

    float MaxSimilarity = -1;
    // 3 means that it just look for the next 3 events
    for (int i = CurrentEvent; i < (CurrentEvent + 3); i++) {
        if (i >= States.size() || i < 0) {
            continue;
        }
        State NextPossibleState = States[i];
        float Similarity = GetSimilarity(NextPossibleState, Desc);
        if (Similarity > MaxSimilarity) {
            MaxSimilarity = Similarity;
            BestGuess = i;
        }
    }

    return BestGuess;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(std::vector<float> *in, FollowerMIR *MIR) {
    // CurrentEvent represents the current event index.
    // In line with human understanding, the first note in the score
    // is indexed as 1 instead of 0. This adjustment is made in DspPerform.

    MIR->UpdateTempoInEvent();
    int EventId = CurrentEvent;
    float maxProb = -1;
    float Similarity;

    // MDP States
    State CurState = States[CurrentEvent];

    // Sound Description
    MIR->GetDescription(in, Desc, Tunning);
    Desc->TimeElapsed = MIR->GetEventTimeElapsed();

    if (Desc->dB < -40) {
        return CurrentEvent;
    }

    float BestGuess = GetBestEvent(States, Desc);
    if (BestGuess != CurrentEvent) {
        CurrentEvent = BestGuess;
        float EventTime = MIR->GetEventTimeElapsed();
        float TimeSpan = States[CurrentEvent].Duration * (60000.0f / States[CurrentEvent].Bpm);
        std::rotate(BpmHistory.begin(), BpmHistory.begin() + 1, BpmHistory.end());
        BpmHistory.at(19) = EventTime / TimeSpan;
        float sum = std::accumulate(BpmHistory.begin(), BpmHistory.end(), 0.0);
        LiveBpm = sum / BpmHistory.size() * States[CurrentEvent].Bpm;
        MIR->ResetElapsedTime();
    }
    return CurrentEvent;
}
