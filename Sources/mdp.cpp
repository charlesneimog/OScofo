#include "follower.hpp"

#include <algorithm>
#include <math.h>

#define MAX_FREQUENCY_DIFFERENCE 40.0 //
#define MAX_QUALITY_DIFFERENCE 0.5

// ==============================================
float FollowerScore::getPitchSimilar(float currentFreq, float stateFreq) {
    // Calculate Euclidean distance between frequencies
    float distance = abs(currentFreq - stateFreq);
    // Normalize distance to range [0, 1]
    float similarity = 1.0 - (distance / MAX_FREQUENCY_DIFFERENCE);
    return similarity;
}

// ==============================================
float FollowerScore::getEnvSimilar(float currentEnv, float stateEnv) {
    // Calculate similarity based on environmental conditions
    // You may need to define your specific method for comparing environmental conditions
    // This is just a placeholder
    if (currentEnv > stateEnv) {
        return 1.0; // High similarity
    } else if (currentEnv == stateEnv) {
        return 0.5; // Medium similarity
    } else {
        return 0.0; // Low similarity
    }
}

// ==============================================
float FollowerScore::calculateSimilarity(float currentFreq, float stateFreq, float currentEnv,
                                         float stateDur) {

    // WARNING:
    float freqWeight = 0.5; // Weight for pitch similarity
    float envWeight = 0.2;  // Weight for environmental similarity

    // Calculate similarities for each factor
    float freqSimilarity = getPitchSimilar(currentFreq, stateFreq);
    // float envSimilarity = getPitchSimilar(currentEnv, stateDur);

    float similarity = freqWeight * freqSimilarity;
    // NOTE: A qualidade sempre é a mesma para todos os eventos analisados

    return similarity;
}

// ==============================================
int FollowerScore::GetEvent(EnvironmentState envState) {
    int eventId;

    // received pitch
    float MIRPitch = envState.pitch;
    float MIRFreq = midi2freq(MIRPitch);
    float MIREnv = envState.env;
    float MIRQuality = envState.min_quality; // pitch quality from sigmund~

    int MDPSize = MDP.states.size();
    State CurState = MDP.states[curEventId];

    if (curEventId == -1) { // First event
        if (MIREnv < 40) {
            return -1;
        }

        // Calculate the probability based on pitch similarity with the first few states in the
        // MDP
        float maxProb = 0.0;
        float firstEventPitch = midi2freq(MDP.states[0].pitch);
        for (int i = 0; i < MDPSize && i < 5; i++) {
            State state = MDP.states[i];
            float stateFreq = midi2freq(state.pitch);
            float stateDur = state.duration;

            // Calculate similarity between current state and state in MDP
            // You may define a function to calculate similarity based on pitch, duration, etc.
            float similarity = calculateSimilarity(MIRFreq, stateFreq, MIREnv, stateDur);

            // Update max probability
            if (similarity > maxProb) {
                maxProb = similarity;
                eventId = i;
                curEventId = eventId;
            }
        }
    } else {
        float maxProb = 0.0;
        std::vector<float> pitchesChecked;
        if (MIREnv < 40) {
            return curEventId + 1;
        }
        for (int i = curEventId; i < curEventId + 5; i++) {
            if (pitchesChecked.size() != 0) {
                if (std::find(pitchesChecked.begin(), pitchesChecked.end(), MDP.states[i].pitch) !=
                    pitchesChecked.end()) {
                    break;
                }
            }

            pitchesChecked.push_back(MDP.states[i].pitch);
            State state = MDP.states[i];
            float stateFreq = midi2freq(state.pitch);
            float stateDur = state.duration;
            float similarity = calculateSimilarity(MIRFreq, stateFreq, MIREnv, stateDur);
            if (similarity > maxProb) {
                maxProb = similarity;
                eventId = i;
                if (curEventId != eventId) {
                    state = MDP.states[curEventId];
                    float duration = state.duration;
                    float bpm = MDP.bpm[curEventId];
                    float durMs = 60000.0f / bpm * duration;

                    post("last event durou %f deveria ter durado %f", elapsedTime, durMs);
                }
                curEventId = eventId;
            }
        }
    }
    return curEventId + 1;
}
