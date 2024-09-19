#include <algorithm>
#include <fstream>
#include <math.h>

#include "../OScofo.hpp"

#include <m_pd.h>

static t_class *OScofoObj;

// ─────────────────────────────────────
class PdOScofo {
  public:
    t_object xObj;
    t_sample Sample;
    std::vector<double> inBuffer;
    t_clock *Clock;
    OScofo *OpenScofo;

    int Event;
    std::string PatchDir;

    // Testing
    bool Testing = false;

    // Score
    bool ScoreLoaded = false;
    bool Following = false;
    int CurrentEvent = 0;
    std::vector<double> PitchTemplate;

    // Audio
    double BlockIndex;
    double BlockSize;
    double HopSize;
    double FFTSize;
    double Sr;

    t_outlet *EventIndex;
    t_outlet *Tempo;
    t_outlet *Kappa;
    t_outlet *Debug;
};

// ─────────────────────────────────────
static void Set(PdOScofo *x, t_symbol *s, int argc, t_atom *argv) {
    LOGE() << "PureData Set Methoda";
    if (argv[0].a_type != A_SYMBOL) {
        pd_error(x, "[follower~] First argument of set method must be a symbol");
        return;
    }
    std::string method = atom_getsymbol(argv)->s_name;
    if (method == "sigma") {
        x->OpenScofo->SetPitchTemplateSigma(atom_getfloat(argv + 1));
        post("[follower~] Sigma set to %f", atom_getfloat(argv + 1));
    } else if (method == "harmonics") {
        x->OpenScofo->SetHarmonics(atom_getint(argv + 1));
        post("[follower~] Using pitch template with %d harmonics", atom_getint(argv + 1));
    } else if (method == "threshold") {
        double dB = atom_getfloat(argv + 1);
        x->OpenScofo->SetdBTreshold(dB);
        post("[follower~] Treshold set to %f", atom_getfloat(argv + 1));
    } else if (method == "time") {
        std::string submethod = atom_getsymbol(argv + 1)->s_name;
        if (submethod == "accum") {
            x->OpenScofo->SetTimeAccumFactor(atom_getfloat(argv + 2));
            printf("[follower~] Time accumulation set to %.4f\n", atom_getfloat(argv + 2));
        } else if (submethod == "coupling") {
            x->OpenScofo->SetTimeCouplingStrength(atom_getfloat(argv + 2));
            printf("[follower~] Time coupling set to %.4f\n", atom_getfloat(argv + 2));
        }
    } else if (method == "tunning") {
        x->OpenScofo->SetTunning(atom_getfloat(argv + 1));

    } else if (method == "event") {
        int f = atom_getint(argv + 1);
        x->CurrentEvent = f;
        x->OpenScofo->SetCurrentEvent(f);
    } else {
        pd_error(x, "[follower~] Unknown method");
    }
    LOGE() << "PureData End Set Methoda";
}

// ─────────────────────────────────────
static void Score(PdOScofo *x, t_symbol *s) {
    LOGE() << "PureData Score Method";
    x->ScoreLoaded = false;
    std::string CompletePath = x->PatchDir;
    CompletePath += "/";
    CompletePath += s->s_name;
    std::ifstream file(CompletePath);
    if (!file) {
        pd_error(nullptr, "[o.scofo~] Score file not found");
        return;
    }
    bool ok = x->OpenScofo->ParseScore(CompletePath.c_str());
    if (ok) {
        x->ScoreLoaded = true;
        post("[o.scofo~] Score loaded");
    } else {
        pd_error(nullptr, "[o.scofo~] Error loading score");
    }
    LOGE() << "PureData end Score Method";
}

// ─────────────────────────────────────
static void Start(PdOScofo *x) {
    LOGE() << "PureData Start Method";
    if (!x->OpenScofo->ScoreIsLoaded()) {
        pd_error(nullptr, "[o.scofo~] Score not loaded");
        return;
    }
    x->CurrentEvent = -1;
    x->OpenScofo->SetCurrentEvent(-1);
    outlet_float(x->Tempo, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventIndex, 0);
    x->Following = true;

    LOGE() << "PureData end Start Method";
}

// ─────────────────────────────────────
static void Follow(PdOScofo *x, t_float f) {
    if (!x->OpenScofo->ScoreIsLoaded()) {
        pd_error(x, "[follower~] Score not loaded");
        return;
    }
    if (f == 1) {
        x->Following = true;
    } else {
        x->Following = false;
    }
}

// ─────────────────────────────────────
static void ClockTick(PdOScofo *x) {
    LOGE() << "PureData ClockTick";
    if (x->Event != 0) {
        if (x->Kappa) {
            outlet_float(x->Kappa, x->OpenScofo->GetKappa());
        }
        outlet_float(x->Tempo, x->OpenScofo->GetLiveBPM());
        outlet_float(x->EventIndex, x->Event);
    }

    LOGE() << "PureData ClockTick end";
}

// ─────────────────────────────────────
static t_int *DspPerform(t_int *w) {
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
        return (w + 4);
    }
    // process block
    x->BlockIndex = 0;

    // TODO: Implement precomputed window
    // std::vector<double> windowTable(x->WindowSize);
    // double factor = 2.0 * M_PI / (x->WindowSize - 1);
    //
    // for (int i = 0; i < x->WindowSize; i++) {
    //     windowTable[i] = 0.5 * (1.0 - cos(factor * i));
    // }
    //

    for (int i = 0; i < x->FFTSize; i++) {
        x->inBuffer[i] *= 0.5 * (1.0 - cos(2.0 * M_PI * i / (x->FFTSize - 1)));
    }

    bool ok = x->OpenScofo->ProcessBlock(x->inBuffer);
    if (!ok) {
        return (w + 4);
    }
    int Event = x->OpenScofo->GetEventIndex();
    if (Event == 0) {
        return (w + 4);
    }
    if (Event != x->Event) {
        x->Event = Event;
        clock_delay(x->Clock, 0);
    }
    return (w + 4);
}

// ─────────────────────────────────────
static void AddDsp(PdOScofo *x, t_signal **sp) {
    LOGE() << "AddDsp";
    x->BlockSize = sp[0]->s_n;
    x->BlockIndex = 0;
    x->inBuffer.resize(x->FFTSize, 0.0f);
    dsp_add(DspPerform, 3, x, sp[0]->s_vec, sp[0]->s_n);
    LOGE() << "AddDsp Successful";
}

// ─────────────────────────────────────
static void *NewOScofo(t_symbol *s, int argc, t_atom *argv) {
    LOGE() << "NewOScofo";

    PdOScofo *x = (PdOScofo *)pd_new(OScofoObj);
    x->EventIndex = outlet_new(&x->xObj, &s_float);
    x->Tempo = outlet_new(&x->xObj, &s_float);
    x->FFTSize = 4096.0f;
    x->HopSize = 1024.0f;
    x->Sr = sys_getsr();
    double overlap = 4;
    for (int i = 0; i < argc; i++) {
        if (argv[i].a_type == A_SYMBOL || argc >= i + 1) {
            std::string argument = std::string(atom_getsymbol(&argv[i])->s_name);
            if (argument == "-w") {
                if (argv[i + 1].a_type == A_FLOAT) {
                    x->FFTSize = atom_getfloat(&argv[i + 1]);
                    i++;
                }
            }
            if (argument == "-o") {
                if (argv[i + 1].a_type == A_FLOAT) {
                    overlap = atom_getfloat(&argv[i + 1]);
                    i++;
                }
            }
            if (argument == "-kappa") {
                x->Kappa = outlet_new(&x->xObj, &s_float);
                // TODO: Output value of SyncStrengh
            }
        }
    }
    if (overlap != 4) {
        x->HopSize = x->FFTSize / overlap;
    }
    t_canvas *canvas = canvas_getcurrent();
    x->PatchDir = canvas_getdir(canvas)->s_name;

    x->Clock = clock_new(x, (t_method)ClockTick);
    x->Event = 0;

    x->OpenScofo = new OScofo(x->Sr, x->FFTSize, x->HopSize);
    x->Following = false;

    LOGE() << "Returning NewOScofo";
    return x;
}

// ─────────────────────────────────────
static void *FreeOScofo(PdOScofo *x) {
    LOGE() << "Start Free of NewOScofo";
    delete x->OpenScofo;
    LOGE() << "End Free of NewOScofo";
    return nullptr;
}

// ─────────────────────────────────────
extern "C" void setup_o0x2escofo_tilde(void) {
    OScofoObj = class_new(gensym("o.scofo~"), (t_newmethod)NewOScofo, (t_method)FreeOScofo, sizeof(OScofo), CLASS_DEFAULT, A_GIMME, 0);

    CLASS_MAINSIGNALIN(OScofoObj, PdOScofo, Sample);
    class_addmethod(OScofoObj, (t_method)AddDsp, gensym("dsp"), A_CANT, 0);
    class_addmethod(OScofoObj, (t_method)Score, gensym("score"), A_SYMBOL, 0);
    class_addmethod(OScofoObj, (t_method)Start, gensym("start"), A_NULL, 0);
    class_addmethod(OScofoObj, (t_method)Follow, gensym("follow"), A_FLOAT, 0);
    class_addmethod(OScofoObj, (t_method)Set, gensym("set"), A_GIMME, 0);
}
