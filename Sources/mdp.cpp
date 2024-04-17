#include "follower.hpp"
#include <algorithm>
#include <math.h>

#define MAX_FREQUENCY_DIFFERENCE 40.0 //
#define MAX_QUALITY_DIFFERENCE 0.5

void FollowerMDP::SetMinQualityForNote(float minQuality) {
    MinQualityForNote = minQuality;
}

// ==============================================
float FollowerMDP::GetPitchSimilar(float currentFreq, float stateFreq) {
    float distance = abs(currentFreq - stateFreq);
    float similarity = distance / MAX_FREQUENCY_DIFFERENCE;
    if (similarity > 1.0) {
        return 0;
    }
    similarity = 1.0 - (distance / MAX_FREQUENCY_DIFFERENCE);
    return similarity;
}

// ==============================================
float FollowerMDP::CalculateSimilarity(float currentFreq, float stateFreq) {
    // WARNING:
    float freqWeight = 0.5; // Weight for pitch similarity
    float freqSimilarity = GetPitchSimilar(currentFreq, stateFreq);
    float similarity = freqSimilarity;
    return similarity;
}

// ==============================================
int FollowerMDP::GetEvent(FollowerMIR::Description *Desc) {
    int eventId;
    float similarity;

    // // received pitch
    float MIRFreq = Desc->Freq;

    pd_float(gensym("freq")->s_thing, MIRFreq);
    pd_float(gensym("quality")->s_thing, Desc->Quality);

    float MIRPitch = Follower_f2midi(MIRFreq, Tunning);
    int MDPSize = States.size();
    if (MDPSize == 0) {
        pd_error(NULL, "No states, check your score");
        return -1;
    }

    if (Desc->dB < -70) {
        return CurrentEvent + 1;
    }

    if (CurrentEvent == -1) { // First event
        if (States[0].type == FollowerScore::NOTE) {
            if (Desc->Quality < MinQualityForNote) {
                return CurrentEvent + 1;
            }
        }
        float maxProb = 0.0;
        for (int i = 0; i < MDPSize && i < 5; i++) {
            State State = States[i];
            float StateFreq = Follower_midi2f(State.pitch, Tunning);
            float Similarity = CalculateSimilarity(MIRFreq, StateFreq);
            if (Similarity > maxProb) {
                maxProb = similarity;
                eventId = i;
                CurrentEvent = eventId;
            }
        }

    } else {
        if (States[0].type == FollowerScore::NOTE) {
            if (Desc->Quality < MinQualityForNote) {
                // TODO: must be defined by the user
                return CurrentEvent + 1;
            }
        }
        float maxProb = 0.0;
        std::vector<float> pitchesChecked;
        for (int i = CurrentEvent; i < CurrentEvent + 5; i++) {
            if (pitchesChecked.size() != 0) {
                if (std::find(pitchesChecked.begin(), pitchesChecked.end(),
                              States[i].pitch) != pitchesChecked.end()) {
                    break;
                }
            }

            pitchesChecked.push_back(States[i].pitch);
            State state = States[i];
            float stateFreq = Follower_midi2f(state.pitch, Tunning);
            float stateDur = state.duration;
            similarity = CalculateSimilarity(MIRFreq, stateFreq);
            if (similarity > maxProb) {
                maxProb = similarity;
                eventId = i;
                if (CurrentEvent != eventId) {
                    state = States[CurrentEvent];
                    float duration = state.duration;
                    // float bpm = bpm[curEventId];
                    // float durMs = 60000.0f / bpm * duration;
                }
                CurrentEvent = eventId;
            }
        }
    }
    return CurrentEvent + 1;
}
