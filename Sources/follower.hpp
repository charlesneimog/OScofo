#pragma once

#include <string>
#include <vector>

#include <m_pd.h>

// FFT
#include <kfr/dft.hpp>

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class FollowerMIR {
  public:
    FollowerMIR(int HopSize, int WindowSize, int Sr);
    static float Mtof(float note, float tunning);
    static float Ftom(float freq, float tunning);
    static float Freq2Bin(t_float freq, t_float n, t_float Sr);
    static unsigned GetPitchBinRanges(std::vector<float> binRanges, t_float thisPitch,
                                      t_float loFreq, t_float hiFreq, t_float pitchTolerance, int n,
                                      t_float sr);

    struct Description {
        float WindowSize;
        float Sr;
        float Tunning = 440;

        float Freq;
        float Midi;
        float Quality;
        float dB;
        float TimeElapsed;
        std::vector<float> SpectralImag;
        std::vector<float> SpectralReal;
        std::vector<float> SpectralPower;

        // Pitch
        std::vector<float> SpectralChroma;
        float HigherChroma;
    };

    void GetDescription(std::vector<float> *in, Description *Desc, float Tunning);
    void GetMidi(float tunning);

    // Time
    float TimePrediction();
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    float GetEventTimeElapsed();
    float GetTempoInEvent();
    float EventTimeElapsed = 0.0; // ms

  private:
    // Pitch
    bool CreateYin(float tolerance, float silence);
    void GetYin(std::vector<float> *in, Description *Desc);
    void AubioYin(std::vector<float> *in, Description *Desc);

    // MFCC
    void GetMFCC(std::vector<float> *in, Description *Desc);
    void GetChroma(std::vector<float> *in, Description *Desc);

    // FFT
    void GetFFT(std::vector<float> *in, Description *Desc);

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
    void ResetLiveBpm();

    // Score States
    struct State {
        float Sr;
        float WindowSize;
        bool Valid;
        int Type;

        int Id;
        float Midi;
        float Duration;
        float TimePhase;
        float Bpm;

        // Time
        float LiveOnset; // ms
        float TimePhasePrediction;
    };
    std::vector<State> States;
    float RValue;

    int GetEvent(std::vector<float> *in, FollowerMIR *MIR);

    float Tunning = 440;
    int CurrentEvent = -1;
    float LastOnset = 0;
    float PhasePrediction = 0;

  private:
    float GetBestEvent(std::vector<State> States, FollowerMIR::Description *Desc);
    float GetSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float GetPitchSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float GetTimeSimilarity(State NextPossibleState, FollowerMIR::Description *Desc);
    float CompareSpectralTemplate(State NextPossibleState, FollowerMIR::Description *Desc);

    // Thing place this
    void GetPitchTemplate(State NextPossibleState);

    FollowerMIR::Description *Desc;
    float MinQualityForNote = 0.9;

    std::vector<float> PitchTemplate;
    std::vector<float> BpmHistory;
    float LiveBpm;
    float LiveTimePhase;
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

    int Name2Midi(std::string note);
    void Parse(FollowerMDP *MDP, const char *score);
    float GetTimePhase(float t_n0, float t_n1, float phase0, float pulse);

  private:
    FollowerMDP::State AddNote(FollowerMDP::State State, std::vector<std::string> tokens, float bpm,
                               int lineCount);

    float lastOnset = 0;
    float lastPhase = 0;
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
