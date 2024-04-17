#include "follower.hpp"
#include <algorithm>
#include <math.h>

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

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
float FollowerMDP::CalculateSimilarity(State NextPossibleState,
                                       FollowerMIR::Description *Desc) {

    // Pitch
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
}

// ─────────────────────────────────────
float FollowerMDP::GetBestEvent(std::vector<State> States,
                                FollowerMIR::Description *Desc) {

    State CurState = States[CurrentEvent];

    float MaxSimilarity = -1;
    for (int i = CurrentEvent; i < (CurrentEvent + 3); i++) {
        if (i >= States.size() || i < 0) {
            continue;
        }
        State NextPossibleState = States[i];
        float Similarity = CalculateSimilarity(NextPossibleState, Desc);
        if (Similarity > MaxSimilarity) {
            post("Similarity: %f | event: %d", Similarity, i);
            MaxSimilarity = Similarity;
            CurrentEvent = i;
        }
    }

    return CurrentEvent;
}

// ─────────────────────────────────────
int FollowerMDP::GetEvent(std::vector<float> *in, FollowerMIR *MIR) {
    // CurrentEvent represents the current event index.
    // In line with human understanding, the first note in the score
    // is indexed as 1 instead of 0. This adjustment is made in DspPerform.

    int EventId = CurrentEvent;
    float maxProb = -1;
    float Similarity;

    // MDP States
    State CurState = States[CurrentEvent];

    // Sound Description
    MIR->GetDescription(in, Desc, Tunning);

    if (Desc->dB < -40) {
        return CurrentEvent;
    }

    if (States[0].Type == FollowerScore::NOTE) {
        if (Desc->Quality < MinQualityForNote) {
            return CurrentEvent;
        }
    }
    return GetBestEvent(States, Desc);
}
