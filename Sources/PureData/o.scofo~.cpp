#include <filesystem>

#include <m_pd.h>
#include <OScofo.hpp>

static t_class *OScofoObj;

#ifdef OSCOFO_LUA
int luaopen_pd(lua_State *L);
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
class PdOScofo {
  public:
    t_object PdObject;
    t_sample Sample;
    t_canvas *Canvas;
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
    t_outlet *EventOut;
    t_outlet *TempoOut;
    t_outlet *InfoOut;
};

// ─────────────────────────────────────
static void oscofo_score(PdOScofo *x, t_symbol *s) {
    // check if file exists
    if (!s) {
        pd_error(x, "[o.scofo~] No score file provided");
        return;
    }

    bool ok;
    std::string scorePath = s->s_name;
    if (!std::filesystem::exists(s->s_name)) {
        scorePath = x->PatchDir + "/" + s->s_name;
    }

    ok = x->OpenScofo->ParseScore(scorePath);
    if (ok) {
        logpost(x, 2, "[o.scofo~] Score loaded");
    } else {
        std::vector<std::string> Errors = x->OpenScofo->GetErrorMessage();
        for (auto &error : Errors) {
            pd_error(x, "[o.scofo~] %s", error.c_str());
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
        pd_error(x, "[o.scofo~] Lua error");
        pd_error(x, "[o.scofo~] %s", error.c_str());
        logpost(x, 1, "");
    }
#endif
}

// ─────────────────────────────────────
static void oscofo_start(PdOScofo *x) {
    if (!x->OpenScofo->ScoreIsLoaded()) {
        pd_error(nullptr, "[o.scofo~] Score not loaded");
        return;
    }
    x->OpenScofo->SetCurrentEvent(-1);
    x->Event = -1;

    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, 0);
    x->Following = true;
    logpost(x, 2, "[o.scofo~] Start following");
}

// ─────────────────────────────────────
static void oscofo_set(PdOScofo *x, t_symbol *s, int argc, t_atom *argv) {
    if (argv[0].a_type != A_SYMBOL) {
        pd_error(x, "[o.scofo~] First argument of set method must be a symbol");
        return;
    }
    std::string method = atom_getsymbol(argv)->s_name;
    if (method == "event") {
        int f = atom_getint(argv + 1);
        x->Event = f;
        x->OpenScofo->SetCurrentEvent(f);
    } else if (method == "section") {
        // TODO: set thing like section A, section B, etc.
        pd_error(x, "[o.scofo~] Section method not implemented");
    } else {
        pd_error(x, "[o.scofo~] Unknown method");
    }
}

// ─────────────────────────────────────
static void oscofo_following(PdOScofo *x, t_float f) {
    if (!x->OpenScofo->ScoreIsLoaded()) {
        pd_error(x, "[o.scofo~] Score not loaded");
        return;
    }
    if (f == 1) {
        x->Following = true;
    } else {
        x->Following = false;
    }
}
// ─────────────────────────────────────
static void oscofo_luaexecute(PdOScofo *x, std::string code) {
#if OSCOFO_LUA
    if (!x->OpenScofo->LuaExecute(code)) {
        std::string error = x->OpenScofo->LuaGetError();
        pd_error(x, "[o.scofo~] Lua error");
        pd_error(x, "[o.scofo~] %s", error.c_str());
    }
#endif
}

// ─────────────────────────────────────
static void oscofo_pdsend(PdOScofo *x, std::string r, int argc, t_atom *argv) {
    t_pd *receiver = gensym(r.c_str())->s_thing;
    if (!receiver) {
        pd_error(x, "[o.scofo~] Receiver %s not found", r.c_str());
        return;
    }

    if (argc == 0) {
        pd_bang(receiver);
    } else {
        pd_list(receiver, &s_list, argc, argv);
    }
}

// ─────────────────────────────────────
static t_atom *oscofo_convertargs(PdOScofo *x, OScofo::Action &action) {
    int size = action.PdArgs.size();
    t_atom *PdArgs = new t_atom[size];

    for (int i = 0; i < size; i++) {
        std::variant<float, int, std::string> arg = action.PdArgs[i];
        if (std::holds_alternative<float>(arg)) {
            SETFLOAT(&PdArgs[i], std::get<float>(arg));
        } else if (std::holds_alternative<int>(arg)) {
            SETFLOAT(&PdArgs[i], std::get<int>(arg));
        } else if (std::holds_alternative<std::string>(arg)) {
            SETSYMBOL(&PdArgs[i], gensym(std::get<std::string>(arg).c_str()));
        }
    }
    return PdArgs;
}

// ─────────────────────────────────────
static void oscofo_tickactions(PdOScofo *x) {
    const double CurrentTime = clock_getlogicaltime();
    const double nextBlock = 1000.0 / x->Sr * x->BlockSize;
    const double NextTime = clock_getsystimeafter(nextBlock);

    std::vector<Action>::iterator it = x->Actions.begin();
    while (it != x->Actions.end()) {
        Action &CurAction = *it;
        if (CurrentTime <= CurAction.time && CurAction.time <= NextTime) {
            if (CurAction.isLua) {
                oscofo_luaexecute(x, CurAction.LuaCode);
            } else {
                oscofo_pdsend(x, CurAction.Receiver, CurAction.PdArgsSize, CurAction.PdArgs);
                delete[] CurAction.PdArgs;
            }
            it = x->Actions.erase(it);
        } else {
            ++it;
        }
    }
}

// ─────────────────────────────────────
static void oscofo_ticknewevent(PdOScofo *x) {
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
                oscofo_pdsend(x, Act.Receiver, Act.PdArgs.size(), PdArgs);
                delete[] PdArgs;
            }
        } else {
            double sysTime = clock_getsystimeafter(time);
            int size = Act.PdArgs.size();
            std::string receiver = Act.Receiver;
            t_atom *PdArgs = oscofo_convertargs(x, Act);
            Action action = {sysTime, Act.isLua, receiver, Act.Lua, PdArgs, size};
            x->Actions.push_back(action);
        }
    }
}

// ─────────────────────────────────────
static t_int *oscofo_perform(t_int *w) {
    PdOScofo *x = (PdOScofo *)(w[1]);
    t_sample *in = (t_sample *)(w[2]);
    int n = static_cast<int>(w[3]);

    if (!x->OpenScofo->ScoreIsLoaded() || !x->Following) {
        return (w + 4);
    }

    x->BlockIndex += n;
    std::copy(x->inBuffer.begin() + n, x->inBuffer.end(), x->inBuffer.begin());
    std::copy(in, in + n, x->inBuffer.end() - n);

    if (x->BlockIndex != x->HopSize) {
        clock_delay(x->ClockActions, 0);
        return (w + 4);
    }

    x->BlockIndex = 0;
    bool ok = x->OpenScofo->ProcessBlock(x->inBuffer);
    if (!ok) {
        std::vector<std::string> Errors = x->OpenScofo->GetErrorMessage();
        for (auto &error : Errors) {
            pd_error(x, "[o.scofo~] %s", error.c_str());
        }
        x->OpenScofo->ClearError();
        return (w + 4);
    }

    clock_delay(x->ClockActions, 0);
    clock_delay(x->ClockEvent, 0);
    return (w + 4);
}

// ─────────────────────────────────────
static void oscofo_adddsp(PdOScofo *x, t_signal **sp) {
    x->BlockSize = sp[0]->s_n;
    x->BlockIndex = 0;
    x->inBuffer.resize((size_t)x->FFTSize, (double)0.0f);
    dsp_add(oscofo_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

// ─────────────────────────────────────
// static void oscofo_processargv(PdOScofo *x, int argc, t_atom *argv) {
//     for (int i = 0; i < argc; i++) {
//         if (argv[i].a_type == A_SYMBOL) {
//             std::string arg = atom_getsymbol(argv + i)->s_name;
//             if (arg == "-fft") {
//                 if (i + 2 < argc) {
//                     x->FFTSize = (int)atom_getint(argv + i + 1);
//                     x->HopSize = (int)atom_getint(argv + i + 2);
//                 } else {
//                     pd_error(x, "[o.scofo~] Window Size and Hop size must be provided");
//                 }
//             }
//         }
//     }
// }

// ─────────────────────────────────────
static void *oscofo_new(void){
    PdOScofo *x = (PdOScofo *)pd_new(OScofoObj);
    if (!x) {
        pd_error(x, "[o.scofo~] Error creating object");
        return nullptr;
    }

    // default parameters
    x->FFTSize = 4096;
    x->HopSize = 1024;
    x->Sr = (int)sys_getsr();
    x->Following = false;
    x->Event = -1;

    // Args
    // oscofo_processargv(x, argc, argv);

    // Outlets
    x->EventOut = outlet_new(&x->PdObject, &s_float);
    x->TempoOut = outlet_new(&x->PdObject, &s_float);
    x->InfoOut = outlet_new(&x->PdObject, &s_anything);

    // Schedule
    x->ClockEvent = clock_new(x, (t_method)oscofo_ticknewevent);
    x->ClockActions = clock_new(x, (t_method)oscofo_tickactions);

    // Current Dir
    x->Canvas = canvas_getcurrent();
    x->PatchDir = canvas_getdir(x->Canvas)->s_name;

    // OScofo Library
    x->OpenScofo = new OScofo::OScofo((float)x->Sr, (float)x->FFTSize, (float)x->HopSize);

    if (x->OpenScofo->HasErrors()) {
        for (auto &error : x->OpenScofo->GetErrorMessage()) {
            pd_error(x, "[o.scofo~] %s", error.c_str());
        }
        x->OpenScofo->ClearError();
    }

#ifdef OSCOFO_LUA
    x->OpenScofo->LuaAddModule("pd", luaopen_pd);
    x->OpenScofo->LuaAddPath(x->PatchDir);
    x->OpenScofo->LuaAddPointer(x, "_pdobj");
#endif
    return (x);
}

// ─────────────────────────────────────
static void oscofo_free(PdOScofo *x) {
    delete x->OpenScofo;
}

// ─────────────────────────────────────
extern "C" void setup_o0x2escofo_tilde(void) {
    OScofoObj = class_new(gensym("o.scofo~"), (t_newmethod)oscofo_new, (t_method)oscofo_free, sizeof(PdOScofo), CLASS_DEFAULT, A_NULL);

    post("[oscofo~] version %d.%d.%d, by Charles K. Neimog", OSCOFO_VERSION_MAJOR, OSCOFO_VERSION_MINOR, OSCOFO_VERSION_PATCH);

    // message methods
    class_addmethod(OScofoObj, (t_method)oscofo_score, gensym("score"), A_SYMBOL, 0);
    class_addmethod(OScofoObj, (t_method)oscofo_start, gensym("start"), A_NULL, 0);
    class_addmethod(OScofoObj, (t_method)oscofo_following, gensym("follow"), A_FLOAT, 0);
    class_addmethod(OScofoObj, (t_method)oscofo_set, gensym("set"), A_GIMME, 0);

    // dsp
    CLASS_MAINSIGNALIN(OScofoObj, PdOScofo, Sample);
    class_addmethod(OScofoObj, (t_method)oscofo_adddsp, gensym("dsp"), A_CANT, 0);
}
