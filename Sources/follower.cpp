#include "follower.hpp"

#include <fstream>

static t_class *FollowerObj;

// ==============================================
static void SetPitch(Follower *x, t_floatarg f) { x->pitchValue = f; }
static void SetQuality(Follower *x, t_floatarg f) { x->qualityValue = f; }
static void SetEnv(Follower *x, t_floatarg f) { x->envValue = f; }
static void SetEvent(Follower *x, t_floatarg f) { x->Score->curEventId = f; }

static void Start(Follower *x) {
  post("follower~ started");
  x->Score->curEventId = -1;
  outlet_float(x->EventIndex, 0);
}

static void Follow(Follower *x, t_floatarg f) { x->Following = f; }

static void Tunning(Follower *x, t_floatarg f) {
  post("A4 set to %f Hz", f);
  x->Score->tunning = f;
}

// ==============================================
static void Score(Follower *x, t_symbol *s) {
  std::string completePath = x->patchDir->s_name;
  completePath += "/";
  completePath += s->s_name;
  // check if file exists
  std::ifstream file(completePath);
  if (!file) {
    pd_error(nullptr, "File not found");
    return;
  }
  x->Score->Parse(completePath.c_str());
  x->scoreLoaded = true;
  post("[follower] Score loaded");
}

// ==============================================
static void ClockTick(Follower *x) { outlet_float(x->EventIndex, x->Event); }

// ==============================================
static t_int *DspPerform(t_int *w) {
  Follower *x = (Follower *)(w[1]);
  float n = (float)(w[2]);

  if (!x->scoreLoaded) {
    post("Score not loaded or following");
    return (w + 3);
  }

  EnvironmentState envState;
  envState.pitch = x->pitchValue;
  envState.env = x->envValue;
  envState.min_quality = x->qualityValue;

  int Event = x->Score->GetEvent(envState);
  float ms = 1000.0f / x->Sr * n; // TODO: CALCULATE THIS ONCE
  x->Score->elapsedTime += ms;
  if (Event == -1) {
    return (w + 3);
  }

  if (Event != x->Event) {
    x->Score->elapsedTime = 0.0f;
    x->Event = Event;
    clock_delay(x->Clock, 0);
  }

  return (w + 3);
}

// ==============================================
static void AddDsp(Follower *x, t_signal **sp) {
  //

  int n = sys_getblksize();
  dsp_add(DspPerform, 2, x, n);
}

// ==============================================
static void *NewFollower(t_symbol *s, int argc, t_atom *argv) {
  Follower *x = (Follower *)pd_new(FollowerObj);
  x->EventIndex = outlet_new(&x->xObj, &s_float);
  x->Tempo = outlet_new(&x->xObj, &s_float);
  // x->pitch = inlet_new(&x->xObj, &x->xObj.ob_pd, &s_float, gensym("_pitch"));
  x->quality =
      inlet_new(&x->xObj, &x->xObj.ob_pd, &s_float, gensym("_quality"));
  x->env = inlet_new(&x->xObj, &x->xObj.ob_pd, &s_float, gensym("_env"));

  t_canvas *canvas = canvas_getcurrent();
  x->patchDir = canvas_getdir(canvas);

  x->Clock = clock_new(x, (t_method)ClockTick);
  x->Event = -1;
  x->Sr = sys_getsr();

  x->Score = new FollowerScore();
  x->Score->elapsedTime = 0;

  return x;
}

// ==============================================
static void *FreeFollower(Follower *x) {
  //
  return nullptr;
}

// ==============================================
extern "C" void follower_tilde_setup(void) {
  FollowerObj = class_new(gensym("follower~"), (t_newmethod)NewFollower,
                          (t_method)FreeFollower, sizeof(Follower),
                          CLASS_DEFAULT, A_GIMME, 0);

  class_addfloat(FollowerObj, (t_method)SetPitch);
  class_addmethod(FollowerObj, (t_method)AddDsp, gensym("dsp"), A_CANT, 0);

  class_addmethod(FollowerObj, (t_method)SetPitch, gensym("_pitch"), A_FLOAT,
                  0);
  class_addmethod(FollowerObj, (t_method)SetQuality, gensym("_quality"),
                  A_FLOAT, 0);
  class_addmethod(FollowerObj, (t_method)SetEnv, gensym("_env"), A_FLOAT, 0);
  class_addmethod(FollowerObj, (t_method)SetEvent, gensym("event"), A_FLOAT, 0);

  class_addmethod(FollowerObj, (t_method)Score, gensym("score"), A_SYMBOL, 0);
  class_addmethod(FollowerObj, (t_method)Follow, gensym("follow"), A_FLOAT, 0);
  class_addmethod(FollowerObj, (t_method)Start, gensym("start"), A_NULL, 0);

  // config
  class_addmethod(FollowerObj, (t_method)Tunning, gensym("tunning"), A_FLOAT,
                  0);
}
