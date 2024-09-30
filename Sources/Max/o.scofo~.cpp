#include <ext.h>
#include <z_dsp.h>

#include <OScofo.hpp>

static t_class *oscofo_class = nullptr;

class MaxOScofo {
  public:
    t_pxobject MaxObject;

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

    int CurrentEvent;
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
    x->ScoreLoaded = false;
    bool WasFollowing = x->Following;
    x->Following = false;
    std::string CompletePath = x->PatchDir;
    CompletePath += "/";
    CompletePath += s->s_name;
    object_post((t_object *)x, "Loading score %s", CompletePath.c_str());
    bool ok;
    try {
        ok = x->OpenScofo->ParseScore(CompletePath.c_str());
    } catch (std::exception &e) {
        object_error((t_object *)x, "Error parsing score, %s.", e.what());
        return;
    }

    x->ScoreLoaded = true;
    x->Following = WasFollowing;
    object_post((t_object *)x, "Score loaded");
}

// ─────────────────────────────────────
static void oscofo_set(MaxOScofo *x, t_symbol *s, long argc, t_atom *argv) {
    if (argv[0].a_type != A_SYM) {
        object_error((t_object *)x, "First argument must be a symbol");
        return;
    }

    std::string method = atom_getsym(argv)->s_name;
    if (method == "sigma") {
        float sigma = atom_getfloat(argv + 1);
        x->OpenScofo->SetPitchTemplateSigma(sigma);
        object_post((t_object *)x, "Sigma set to %f", sigma);
    } else if (method == "harmonics") {
        long harmonics = atom_getlong(argv + 1);
        x->OpenScofo->SetHarmonics(harmonics);
        object_post((t_object *)x, "Using pitch template with %d harmonics", harmonics);
    } else if (method == "threshold") {
        double dB = atom_getfloat(argv + 1);
        x->OpenScofo->SetdBTreshold(dB);
        object_post((t_object *)x, "Treshold set to %f", atom_getfloat(argv + 1));
    } else if (method == "tunning") {
        float tunning = atom_getfloat(argv + 1);
        x->OpenScofo->SetTunning(tunning);
        object_post((t_object *)x, "Tunning set to %f", tunning);
    } else if (method == "event") {
        long f = atom_getlong(argv + 1);
        x->CurrentEvent = f;
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
static void oscofo_start(MaxOScofo *x) {
    x->Following = false;
    if (!x->OpenScofo->ScoreIsLoaded()) {
        object_error((t_object *)x, "Score not loaded");
        return;
    }
    x->CurrentEvent = -1;
    x->OpenScofo->SetCurrentEvent(-1);
    outlet_float(x->TempoOut, x->OpenScofo->GetLiveBPM());
    outlet_float(x->EventOut, 0);
    x->Following = true;
}

// ─────────────────────────────────────
static void oscofo_tickevent(MaxOScofo *x) {
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
static void oscofo_tickinfo(MaxOScofo *x) {
    if (x->InfoLoaded) {
        t_atom Info[x->Info.size()];
        for (int i = 0; i < x->Info.size(); i++) {
            double value = 0;
            if (x->Info[i] == "kappa") {
                value = x->OpenScofo->GetKappa();
            } else if (x->Info[i] == "db") {
                value = x->OpenScofo->GetdBValue();
            }
            atom_setfloat(Info, value);
        }
        outlet_list(x->InfoOut, nullptr, x->Info.size(), Info);
        return;
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
        return;
    }
    clock_delay(x->ClockEvent, 0);
    clock_delay(x->ClockInfo, 0);
    return;
}

// ─────────────────────────────────────
static void oscofo_dsp64(MaxOScofo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags) {
    x->BlockSize = maxvectorsize;
    x->BlockIndex = 0;
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
    for (int i = 0; i < argc; i++) {
        if (argv[i].a_type == A_SYM || argc >= i + 1) {
            std::string argument = std::string(atom_getsym(&argv[i])->s_name);
            if (argument == "@info") {
                x->InfoOut = outlet_new(x, "list");
                int k = 0;
                for (int j = i + 1; j < argc; j++) {
                    if (argv[j].a_type == A_SYM) {
                        x->Info.push_back(atom_getsym(&argv[j])->s_name);
                    }
                    x->InfoLoaded = true;
                    k++;
                }
            }
        }
    }
    dsp_setup((t_pxobject *)x, 1);

    x->TempoOut = outlet_new(x, "float"); // tempo outlet
    x->EventOut = outlet_new(x, "int");   // event outlet
    x->ClockEvent = clock_new(x, (method)oscofo_tickevent);
    x->ClockInfo = clock_new(x, (method)oscofo_tickinfo);
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
