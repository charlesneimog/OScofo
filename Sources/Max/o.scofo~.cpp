#include <filesystem>

#include <ext.h>
#include <z_dsp.h>
#include <OScofo.hpp>

static t_class *oscofo_class = nullptr;
#ifdef OSCOFO_LUA
int luaopen_max(lua_State *L);
#endif

// ─────────────────────────────────────
struct Action {
    double time;
    bool isLua;
    std::string Receiver;
    std::string LuaCode;
    t_atom *PdArgs;
    int PdArgsSize;
};

// ─────────────────────────────────────
class MaxOScofo {
  public:
    t_pxobject MaxObject;
    t_sample Sample;
    std::string PatchDir;

    // Clock
    t_clock *ClockEvent;
    t_clock *ClockInfo;
    t_clock *ClockActions;

    // Actions
    std::vector<Action> Actions;

    // OScofo
    OScofo::OScofo *OpenScofo;
    int Event;
    float Tempo;
    bool Following;

    // Audio
    std::vector<double> inBuffer;
    int FFTSize;
    int HopSize;
    int BlockSize;
    int Sr;
    int BlockIndex;

    // Outlet
    void *EventOut;
    void *TempoOut;
    void *InfoOut;
};

// ─────────────────────────────────────
static void oscofo_assist(MaxOScofo *x, void *b, long m, long a, char *s) {
    if (m == ASSIST_OUTLET) {
        switch (a) {
        case 0:
            snprintf(s, 256, "Score Event Index");
            break;
        case 1:
            snprintf(s, 256, "Tempo in BPM of the current performance");
            break;
        case 2:
            snprintf(s, 256, "List of values defined by @info attribute");
            break;
        }
    } else {
        switch (a) {
        case 0:
            snprintf(s, 256, "Signal Input");
            break;
        }
    }
}

// ─────────────────────────────────────
static void oscofo_score(MaxOScofo *x, t_symbol *s) {
    // check if file exists
    if (!s) {
        object_error((t_object *)x, "[o.scofo~] No score file provided");
        return;
    }

    bool ok;
    std::string scorePath = s->s_name;
    if (!std::filesystem::exists(s->s_name)) {
        scorePath = x->PatchDir + "/" + s->s_name;
    }

    ok = x->OpenScofo->ParseScore(scorePath);
    if (ok) {
        object_post((t_object *)x, "[o.scofo~] Score loaded");
    } else {
        std::vector<std::string> Errors = x->OpenScofo->GetErrorMessage();
        for (auto &error : Errors) {
            object_post((t_object *)x, "[o.scofo~] %s", error.c_str());
        }
        x->OpenScofo->ClearError();
        return;
    }

    x->OpenScofo->SetCurrentEvent(-1);
    x->Event = -1;
    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, 0);

    // Update Audio
    x->FFTSize = x->OpenScofo->GetFFTSize();
    x->HopSize = x->OpenScofo->GetHopSize();
    x->inBuffer.resize(x->FFTSize, 0.0f);

    // Get Lua Code

#ifdef OSCOFO_LUA
    std::string LuaCode = x->OpenScofo->GetLuaCode();
    bool result = x->OpenScofo->LuaExecute(LuaCode.c_str());
    if (!result) {
        std::string error = x->OpenScofo->LuaGetError();
        object_error((t_object *)x, "[o.scofo~] Lua error");
        object_error((t_object *)x, "[o.scofo~] %s", error.c_str());
    }
#endif
}

// ─────────────────────────────────────
static void oscofo_start(MaxOScofo *x) {
    if (!x->OpenScofo->ScoreIsLoaded()) {
        object_error((t_object *)x, "[o.scofo~] Score not loaded");
        return;
    }
    x->OpenScofo->SetCurrentEvent(-1);
    x->Event = -1;

    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, 0);
    x->Following = true;
    object_post((t_object *)x, "[o.scofo~] Start following");
}

// ─────────────────────────────────────
static void oscofo_set(MaxOScofo *x, t_symbol *s, long argc, t_atom *argv) {
    if (argv[0].a_type != A_SYM) {
        object_error((t_object *)x, "First argument must be a symbol");
        return;
    }

    std::string method = atom_getsym(argv)->s_name;
    if (method == "event") {
        long f = atom_getlong(argv + 1);
        x->Event = f;
        x->OpenScofo->SetCurrentEvent(f);
        object_post((t_object *)x, "Event set to %d", (int)f);
    } else {
        object_error((t_object *)x, "[follower~] Unknown method");
    }
}

// ─────────────────────────────────────
static void oscofo_following(MaxOScofo *x, long f) {
    if (!x->OpenScofo->ScoreIsLoaded()) {
        object_error((t_object *)x, "Score not loaded");
        return;
    }
    if (f == 1) {
        x->Following = true;
        object_post((t_object *)x, "Following!");
    } else {
        object_post((t_object *)x, "Not Following!");
        x->Following = false;
    }
}

// ─────────────────────────────────────
static void oscofo_luaexecute(MaxOScofo *x, std::string code) {
#ifdef OSCOFO_LUA
    if (!x->OpenScofo->LuaExecute(code)) {
        std::string error = x->OpenScofo->LuaGetError();
        object_error((t_object *)x, "[o.scofo~] Lua error");
        object_error((t_object *)x, "[o.scofo~] %s", error.c_str());
    }
#endif
}

// ─────────────────────────────────────
static void oscofo_maxsend(MaxOScofo *x, std::string r, int argc, t_atom *argv) {
    t_symbol *sym = gensym(r.c_str());
    t_object *receiver = sym->s_thing;
    if (receiver == nullptr){
        object_error((t_object *)x, "Receiver '%s' not found", r.c_str());
        return;
    }

    if (argc == 0) {
        object_method(receiver, gensym("bang"));
    } else {
        object_method_typed(receiver, gensym("list"), argc, argv, nullptr);
    }
}
// ─────────────────────────────────────
static t_atom *oscofo_convertargs(MaxOScofo *x, OScofo::Action &action) {
    int size = action.PdArgs.size();
    t_atom *PdArgs = new t_atom[size];

    for (int i = 0; i < size; i++) {
        std::variant<float, int, std::string> arg = action.PdArgs[i];
        if (std::holds_alternative<float>(arg)) {
            atom_setfloat(&PdArgs[i], std::get<float>(arg));
        } else if (std::holds_alternative<int>(arg)) {
            atom_setlong(&PdArgs[i], std::get<int>(arg));
        } else if (std::holds_alternative<std::string>(arg)) {
            atom_setsym(&PdArgs[i], gensym(std::get<std::string>(arg).c_str()));
        }
    }
    return PdArgs;
}

// ─────────────────────────────────────
static void oscofo_tickactions(MaxOScofo *x) {
    const double CurrentTime = gettime();
    const double nextBlock = 1000.0 / x->Sr * x->BlockSize;
    const double NextTime = CurrentTime + nextBlock;

    std::vector<Action>::iterator it = x->Actions.begin();
    while (it != x->Actions.end()) {
        Action &CurAction = *it;
        if ((CurrentTime <= CurAction.time && CurAction.time <= NextTime) || CurAction.time < CurrentTime) {
            if (CurAction.isLua) {
                oscofo_luaexecute(x, CurAction.LuaCode);
            } else {
                oscofo_maxsend(x, CurAction.Receiver, CurAction.PdArgsSize, CurAction.PdArgs);
                delete[] CurAction.PdArgs;
            }
            it = x->Actions.erase(it);
        } else {
            ++it;
        }
    }
}

// ─────────────────────────────────────
static void oscofo_ticknewevent(MaxOScofo *x) {
    int PrevEvent = x->Event;
    x->Event = x->OpenScofo->GetEventIndex();
    if (PrevEvent == x->Event || x->Event == 0) {
        return;
    }

    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, x->OpenScofo->GetEventIndex());
    OScofo::ActionVec Actions = x->OpenScofo->GetEventActions(x->Event - 1);

    for (OScofo::Action &Act : Actions) {
        double time = Act.Time;
        if (!Act.AbsoluteTime) {
            Act.Time = 60.0 / x->OpenScofo->GetLiveBPM() * Act.Time * 1000;
            time = Act.Time;
        }
        if (time == 0) {
            if (Act.isLua) {
                oscofo_luaexecute(x, Act.Lua);
            } else {
                t_atom *PdArgs = oscofo_convertargs(x, Act);
                oscofo_maxsend(x, Act.Receiver, Act.PdArgs.size(), PdArgs);
                delete[] PdArgs;
            }
        } else {
            double actionTime = gettime() + time;
            int size = Act.PdArgs.size();
            std::string receiver = Act.Receiver;
            t_atom *PdArgs = oscofo_convertargs(x, Act);
            Action action = {actionTime, Act.isLua, receiver, Act.Lua, PdArgs, size};
            x->Actions.push_back(action);
        }
    }
}

// ─────────────────────────────────────
static void oscofo_perform64(MaxOScofo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags,
                             void *userparam) {
    if (!x->OpenScofo->ScoreIsLoaded() || !x->Following) {
        return;
    }

    x->BlockIndex += sampleframes;
    std::copy(x->inBuffer.begin() + sampleframes, x->inBuffer.end(), x->inBuffer.begin());
    std::copy(ins[0], ins[0] + sampleframes, x->inBuffer.end() - sampleframes);
    if (x->BlockIndex != x->HopSize) {
        return;
    }

    x->BlockIndex = 0;
    bool ok = x->OpenScofo->ProcessBlock(x->inBuffer);
    if (!ok) {
        std::vector<std::string> Errors = x->OpenScofo->GetErrorMessage();
        for (auto &error : Errors) {
            object_error((t_object *)x, "[o.scofo~] %s", error.c_str());
        }
        x->OpenScofo->ClearError();
        return;
    }
    clock_delay(x->ClockActions, 0);
    clock_delay(x->ClockEvent, 0);
    return;
}

// ─────────────────────────────────────
static void oscofo_dsp64(MaxOScofo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags) {
    x->BlockSize = maxvectorsize;
    x->BlockIndex = 0;
    x->Sr = samplerate;
    post("Sample Rate: %f", samplerate);
    x->inBuffer.resize(x->FFTSize, 0.0f);
    object_method(dsp64, gensym("dsp_add64"), x, oscofo_perform64, 0, NULL);
}

// ─────────────────────────────────────
static void *oscofo_new(t_symbol *s, long argc, t_atom *argv) {
    MaxOScofo *x = (MaxOScofo *)object_alloc(oscofo_class);
    if (!x) {
        object_error((t_object *)x, "Error creating object");
        return nullptr;
    }
    double overlap = 4;

    dsp_setup((t_pxobject *)x, 1);

    x->TempoOut = outlet_new(x, "float"); // tempo outlet
    x->EventOut = outlet_new(x, "int");   // event outlet
    x->ClockEvent = clock_new(x, (method)oscofo_ticknewevent);
    x->ClockActions = clock_new(x, (method)oscofo_tickactions);
    x->FFTSize = 4096.0f;
    x->HopSize = 1024.0f;
    x->Sr = sys_getsr();
    x->Following = false;
    x->Event = -1;

    char PatchPath[MAX_PATH_CHARS];
    short PathId = path_getdefault();
    path_toabsolutesystempath(PathId, NULL, PatchPath);
    x->PatchDir = PatchPath;

    x->OpenScofo = new OScofo::OScofo(x->Sr, x->FFTSize, x->HopSize);
    if (x->OpenScofo->HasErrors()) {
        for (auto &error : x->OpenScofo->GetErrorMessage()) {
            object_error((t_object *)x, "[o.scofo~] %s", error.c_str());
        }
        x->OpenScofo->ClearError();
    }

#ifdef OSCOFO_LUA
    x->OpenScofo->LuaAddModule("max", luaopen_max);   
    x->OpenScofo->LuaAddPath(x->PatchDir);
    x->OpenScofo->LuaAddPointer(x, "_maxobj");
#endif

    return (x);
}

// ─────────────────────────────────────
static void oscofo_free(MaxOScofo *x) {
    delete x->OpenScofo;
}

// ─────────────────────────────────────
void ext_main(void *r) {
    t_class *c = class_new("o.scofo~", (method)oscofo_new, (method)dsp_free, (long)sizeof(MaxOScofo), 0L, A_GIMME, 0);

    object_post(nullptr, "[oscofo~] version %d.%d.%d, by Charles K. Neimog", OSCOFO_VERSION_MAJOR, OSCOFO_VERSION_MINOR, OSCOFO_VERSION_PATCH);
    // message methods
    class_addmethod(c, (method)oscofo_set, "set", A_GIMME, 0);
    class_addmethod(c, (method)oscofo_score, "score", A_SYM, 0);
    class_addmethod(c, (method)oscofo_following, "follow", A_LONG, 0);
    class_addmethod(c, (method)oscofo_start, "start", A_NOTHING, 0);

    // user methods
    class_addmethod(c, (method)stdinletinfo, "inletinfo", A_CANT, 0);
    class_addmethod(c, (method)oscofo_assist, "assist", A_CANT, 0);

    // dsp methods
    class_addmethod(c, (method)oscofo_dsp64, "dsp64", A_CANT, 0);

    // register the class
    class_dspinit(c);
    class_register(CLASS_BOX, c);
    oscofo_class = c;
}
