#include "follower.hpp"

#include <algorithm>
#include <fstream>

static t_class *FollowerObj;

// ─────────────────────────────────────
static void SetEvent(Follower *x, t_floatarg f) {
    x->CurrentEvent = f;
    x->MDP->CurrentEvent = f;
}

// ─────────────────────────────────────
static void Start(Follower *x) {
    x->CurrentEvent = -1;
    x->MDP->CurrentEvent = -1;
    outlet_float(x->EventIndex, 0);
}

// ─────────────────────────────────────
static void Follow(Follower *x, t_floatarg f) {
    x->Following = f;
}

// ─────────────────────────────────────
static void MinQuality(Follower *x, t_floatarg f) {
    x->MDP->SetMinQualityForNote(f);
}
// ─────────────────────────────────────
static void Tunning(Follower *x, t_floatarg f) {
    post("[follower~] A4 set to %f Hz", f);
    x->MDP->Tunning = f;
}

// ─────────────────────────────────────
static void Score(Follower *x, t_symbol *s) {
    std::string completePath = x->patchDir->s_name;
    completePath += "/";
    completePath += s->s_name;
    // check if file exists
    std::ifstream file(completePath);
    if (!file) {
        pd_error(nullptr, "[follower~] Score file not found");
        return;
    }
    x->Score->Parse(x->MDP, completePath.c_str());
    x->MDP->GetLiveBpm();
    x->ScoreLoaded = true;
    post("[follower~] Score loaded");
}

// ─────────────────────────────────────
static void ClockTick(Follower *x) {
    outlet_float(x->EventIndex, x->Event);
    outlet_float(x->Tempo, x->MDP->GetLiveBpm());
}

// ─────────────────────────────────────
static t_int *DspPerform(t_int *w) {
    Follower *x = (Follower *)(w[1]);
    float *in = (t_sample *)(w[2]);
    float n = (float)(w[3]);

    std::rotate(x->inBuffer->begin(), x->inBuffer->begin() + n, x->inBuffer->end());
    for (int i = 0; i < n; i++) {
        x->inBuffer->at(x->WindowSize - n + i) = in[i];
    }
    x->BlockIndex += n;
    if (!x->ScoreLoaded) {
        return (w + 4);
    }

    if (x->BlockIndex != x->HopSize) {
        return (w + 4);
    }

    x->BlockIndex = 0;
    int Event = x->MDP->GetEvent(x->inBuffer, x->MIR) + 1;
    if (Event == -1) {
        return (w + 4);
    }
    if (Event != x->Event) {
        x->Event = Event;
        clock_delay(x->Clock, 0);
    }

    return (w + 4);
}

// ─────────────────────────────────────
static void AddDsp(Follower *x, t_signal **sp) {
    x->BlockSize = sp[0]->s_n;
    x->BlockIndex = 0;
    x->inBuffer = new std::vector<float>(x->WindowSize, 0.0f);
    dsp_add(DspPerform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

// ─────────────────────────────────────
static void *NewFollower(t_symbol *s, int argc, t_atom *argv) {
    Follower *x = (Follower *)pd_new(FollowerObj);
    x->EventIndex = outlet_new(&x->xObj, &s_float);
    x->Tempo = outlet_new(&x->xObj, &s_float);

    t_canvas *canvas = canvas_getcurrent();
    x->patchDir = canvas_getdir(canvas);

    x->Clock = clock_new(x, (t_method)ClockTick);
    x->Event = -1;

    x->WindowSize = 2048;
    x->HopSize = 256;
    x->Sr = sys_getsr();

    x->Score = new FollowerScore();
    x->MDP = new FollowerMDP();
    x->MIR = new FollowerMIR(x->HopSize, x->WindowSize, x->Sr);

    return x;
}

// ─────────────────────────────────────
static void *FreeFollower(Follower *x) {
    delete x->Score;
    delete x->MIR;
    delete x->MDP;
    return nullptr;
}

// ─────────────────────────────────────
extern "C" void follower_tilde_setup(void) {
    FollowerObj = class_new(gensym("follower~"), (t_newmethod)NewFollower, (t_method)FreeFollower,
                            sizeof(Follower), CLASS_DEFAULT, A_GIMME, 0);

    CLASS_MAINSIGNALIN(FollowerObj, Follower, Sample);
    class_addmethod(FollowerObj, (t_method)AddDsp, gensym("dsp"), A_CANT, 0);

    class_addmethod(FollowerObj, (t_method)SetEvent, gensym("event"), A_FLOAT, 0);

    class_addmethod(FollowerObj, (t_method)Score, gensym("score"), A_SYMBOL, 0);
    class_addmethod(FollowerObj, (t_method)Follow, gensym("follow"), A_FLOAT, 0);
    class_addmethod(FollowerObj, (t_method)Start, gensym("start"), A_NULL, 0);

    // config
    class_addmethod(FollowerObj, (t_method)Tunning, gensym("tunning"), A_FLOAT, 0);
    class_addmethod(FollowerObj, (t_method)MinQuality, gensym("quality"), A_FLOAT, 0);
}
