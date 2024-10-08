#include <OScofo.hpp>

#include <m_pd.h>

static t_class *OScofoObj;

// ─────────────────────────────────────
class PdOScofo {
  public:
    t_object PdObject;
    t_sample Sample;

    // Clock
    t_clock *ClockEvent;
    t_clock *ClockInfo;

    // OScofo
    OScofo::OScofo *OpenScofo;
    int Event;
    float Tempo;
    int EventIndex;
    bool Following;
    std::string PatchDir;

    bool ScoreLoaded;
    std::vector<std::string> Info;
    bool InfoLoaded = true;

    // Audio
    std::vector<double> inBuffer;
    float FFTSize;
    float HopSize;
    float BlockSize;
    float Sr;
    unsigned BlockIndex;

    // Outlet
    t_outlet *EventOut;
    t_outlet *TempoOut;
    t_outlet *InfoOut;
};

// ─────────────────────────────────────
static void oscofo_score(PdOScofo *x, t_symbol *s) {
    x->ScoreLoaded = false;
    std::string CompletePath = x->PatchDir;
    CompletePath += "/";
    CompletePath += s->s_name;
    post("[o.scofo~] Loading score %s", CompletePath.c_str());
    bool ok;
    try {
        ok = x->OpenScofo->ParseScore(CompletePath.c_str());
    } catch (std::exception &e) {
        pd_error(nullptr, "[o.scofo~] Error parsing score, %s.", e.what());
        return;
    }
    if (ok) {
        x->ScoreLoaded = true;
        post("[o.scofo~] Score loaded");
    } else {
        pd_error(nullptr, "[o.scofo~] Error loading score");
    }
}

// ─────────────────────────────────────
static void oscofo_set(PdOScofo *x, t_symbol *s, int argc, t_atom *argv) {
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
    } else if (method == "tunning") {
        x->OpenScofo->SetTunning(atom_getfloat(argv + 1));

    } else if (method == "event") {
        int f = atom_getint(argv + 1);
        x->Event = f;
        x->OpenScofo->SetCurrentEvent(f);
    } else {
        pd_error(x, "[follower~] Unknown method");
    }
}

// ─────────────────────────────────────
static void oscofo_following(PdOScofo *x, t_float f) {
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
static void oscofo_start(PdOScofo *x) {
    if (!x->OpenScofo->ScoreIsLoaded()) {
        pd_error(nullptr, "[o.scofo~] Score not loaded");
        return;
    }
    x->OpenScofo->SetCurrentEvent(-1);
    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, 0);
    x->Following = true;
}

// ─────────────────────────────────────
static void oscofo_tickevent(PdOScofo *x) {
    int PrevEvent = x->Event;
    x->Event = x->OpenScofo->GetEventIndex();
    if (PrevEvent == x->Event) {
        return;
    }
    if (x->Event != 0) {
        outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
        outlet_float(x->EventOut, x->OpenScofo->GetEventIndex());
    }
}

// ─────────────────────────────────────
static void oscofo_tickinfo(PdOScofo *x) {
    if (x->InfoLoaded) {
        t_atom Info[x->Info.size()];
        for (int i = 0; i < x->Info.size(); i++) {
            double value = 0;
            if (x->Info[i] == "kappa") {
                value = x->OpenScofo->GetKappa();
            } else if (x->Info[i] == "db") {
                value = x->OpenScofo->GetdBValue();
            }
            SETFLOAT(&Info[i], value);
        }
        outlet_list(x->InfoOut, nullptr, x->Info.size(), Info);
        return;
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
        return (w + 4);
    }

    x->BlockIndex = 0;
    bool ok = x->OpenScofo->ProcessBlock(x->inBuffer);
    if (!ok) {
        return (w + 4);
    }
    clock_delay(x->ClockEvent, 0);
    clock_delay(x->ClockInfo, 0);
    return (w + 4);
}

// ─────────────────────────────────────
static void oscofo_adddsp(PdOScofo *x, t_signal **sp) {
    x->BlockSize = sp[0]->s_n;
    x->BlockIndex = 0;
    x->inBuffer.resize(x->FFTSize, 0.0f);
    dsp_add(oscofo_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

// ─────────────────────────────────────
static void *oscofo_new(t_symbol *s, int argc, t_atom *argv) {
    PdOScofo *x = (PdOScofo *)pd_new(OScofoObj);
    if (!x) {
        pd_error(nullptr, "[o.scofo~] Error creating object");
        return nullptr;
    }

    x->EventOut = outlet_new(&x->PdObject, &s_float); // event outlet
    x->TempoOut = outlet_new(&x->PdObject, &s_float); // tempo outlet

    double overlap = 4;
    for (int i = 0; i < argc; i++) {
        if (argv[i].a_type == A_SYMBOL || argc >= i + 1) {
            std::string argument = std::string(atom_getsymbol(&argv[i])->s_name);
            if (argument == "-info" || argument == "@info") {
                x->InfoOut = outlet_new(&x->PdObject, &s_list);
                int k = 0;
                for (int j = i + 1; j < argc; j++) {
                    if (argv[j].a_type == A_SYMBOL) {
                        x->Info.push_back(atom_getsymbol(&argv[j])->s_name);
                    }
                    x->InfoLoaded = true;
                    k++;
                }
            }
        }
    }

    x->ClockEvent = clock_new(x, (t_method)oscofo_tickevent);
    x->ClockInfo = clock_new(x, (t_method)oscofo_tickinfo);
    x->FFTSize = 4096.0f;
    x->HopSize = 1024.0f;
    x->Sr = sys_getsr();
    x->Following = false;
    x->Event = -1;

    t_canvas *canvas = canvas_getcurrent();
    x->PatchDir = canvas_getdir(canvas)->s_name;

    x->OpenScofo = new OScofo::OScofo(x->Sr, x->FFTSize, x->HopSize);
    return (x);
}

// ─────────────────────────────────────
static void oscofo_free(PdOScofo *x) {
    delete x->OpenScofo;
}

// ─────────────────────────────────────
extern "C" void setup_o0x2escofo_tilde(void) {
    OScofoObj = class_new(gensym("o.scofo~"), (t_newmethod)oscofo_new, (t_method)oscofo_free, sizeof(PdOScofo), CLASS_DEFAULT, A_GIMME, 0);

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
