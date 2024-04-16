#include <m_pd.h>

#include <string>
#include <vector>

struct State {
    int id;

    // descriptors
    float pitch;
    float quality;

    // time
    float duration;
};

struct EnvironmentState {
    float pitch;
    float env; // envelope
    float min_quality;
    float time_elapsed;
};

struct MarkovDecisionProcess {
    std::vector<float> bpm;
    std::vector<State> states;
    EnvironmentState environment;
};

class FollowerScore {
  private:
    float midi2freq(float note);
    float freq2midi(float freq);

  public:
    void Parse(const char *score);
    int AddNote(std::vector<std::string> tokens, float bpm, int lineCount);
    void DefineTransitions();
    int GetEvent(EnvironmentState envState);
    int NoteName2Midi(std::string note);

    float getPitchSimilar(float currentFreq, float stateFreq);
    float getEnvSimilar(float currentEnv, float stateEnv);
    float calculateSimilarity(float currentFreq, float stateFreq, float currentEnv, float stateDur);

    MarkovDecisionProcess MDP;
    State *currentState;
    int curEventId = -1;
    float tunning;
    std::vector<float> bpms;

    bool amILost = false;
    int lastGoodEventId = 0;
    float elapsedTime = 0.0f;
};

class Follower {
  public:
    t_object xObj;

    FollowerScore *Score;
    t_clock *Clock;

    float pitchValue;
    float qualityValue;
    float envValue;

    int Event;
    float Sr;
    t_symbol *patchDir;

    bool scoreLoaded = false;
    bool Following = false;

    t_outlet *EventIndex;
    t_outlet *Tempo;

    t_inlet *pitch;
    t_inlet *quality;
    t_inlet *env;

    // functions
    void SetScore(Follower *x, t_symbol *score);
    static t_int *Perform(t_int *w);
    int FindPeaks();

    //
};
