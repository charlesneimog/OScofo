#pragma once

#include <m_pd.h>

#include <aubio.h>
#include <string>
#include <vector>

// ╭─────────────────────────────────────╮
// │         Utilities Functions         │
// ╰─────────────────────────────────────╯
float Follower_midi2f(float note, float tunning);
float Follower_f2midi(float freq, float tunning);
int Follower_NoteName2Midi(std::string note);

// ─────────────────────────────────────

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class FollowerMIR {
  public:
    FollowerMIR(int HopSize, int WindowSize, int Sr);
    struct Description {
        float Freq;
        float Midi;
        float Quality;
        float dB;
        float TimeElapsed;
    };
    void GetDescription(std::vector<float> *in, Description *Desc, float Tunning);
    void GetMidi(float tunning);

    // Time
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    float GetEventTimeElapsed();
    float GetTempoInEvent();
    float EventTimeElapsed = 0.0; // ms

  private:
    // Pitch
    aubio_pitch_t *YinInstance;
    bool CreateYin(float tolerance, float silence);
    void GetYin(std::vector<float> *in, Description *desc, float Tunning);

    // Env
    void GetRMS(std::vector<float> *in, Description *Desc);

    // Audio
    float WindowSize;
    float BlockSize;
    float HopSize;
    float Sr;
};

// ╭─────────────────────────────────────╮
// │     Markov Description Process      │
// ╰─────────────────────────────────────╯
class FollowerMDP {
  public:
    FollowerMDP();
    void SetMinQualityForNote(float minQuality);
    float GetLiveBpm();
    void SetLiveBpm(float Bpm);

    // Score States
    struct State {
        bool Valid;
        int Type;

        int Id;
        float Midi;
        float Duration;
        float Bpm;
    };

    int GetEvent(std::vector<float> *in, FollowerMIR *MIR);
    float Tunning = 440;
    int CurrentEvent = -1;
    std::vector<State> States;

  private:
    float GetBestEvent(std::vector<State> States, FollowerMIR::Description *Desc);
    float GetSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float GetPitchSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float GetTimeSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);

    FollowerMIR::Description *Desc;
    std::vector<float> BpmHistory;
    float LiveBpm;
    float MinQualityForNote = 0.9;
};

// ╭─────────────────────────────────────╮
// │                Score                │
// ╰─────────────────────────────────────╯

// ─────────────────────────────────────
class FollowerScore {
  public:
    enum EventType {
        SILENCE = 0,
        NOTE,
        // TODO: Add more events
    };

    void Parse(FollowerMDP *MDP, const char *score);

  private:
    FollowerMDP::State AddNote(FollowerMDP::State State, std::vector<std::string> tokens, float bpm,
                               int lineCount);

    float FollowBpm(std::vector<std::string> tokens, int lineCount);
};

// ╭─────────────────────────────────────╮
// │           PureData Object           │
// ╰─────────────────────────────────────╯
class Follower {
  public:
    t_object xObj;
    t_sample Sample;
    std::vector<float> *inBuffer;
    t_clock *Clock;

    //
    FollowerScore *Score;
    FollowerMDP *MDP;
    FollowerMIR *MIR;

    int Event;
    t_symbol *patchDir;

    // Score
    bool ScoreLoaded = false;
    bool Following = false;
    int CurrentEvent = 0;

    // Audio
    int BlockIndex;
    int BlockSize;
    int HopSize;
    int WindowSize;
    int Sr;

    t_outlet *EventIndex;
    t_outlet *Tempo;
};
