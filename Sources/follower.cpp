#include "follower.hpp"

#include <algorithm>
#include <fstream>
#include <math.h>

#include <boost/math/special_functions/bessel.hpp>

static t_class *FollowerObj;

// ─────────────────────────────────────
static void TimeValues(Follower *x) {
    if (!x->Score->ScoreLoaded()) {
        return;
    }
}

// ─────────────────────────────────────
static void GerenateAnalTemplate(Follower *x, t_symbol *s, t_float sr, t_float fund, t_float h) {
    double *FFTIn;
    fftw_complex *FFTOut;
    fftw_plan FFTPlan;
    x->MDP->m_PitchTemplate.clear();

    FFTIn = (double *)fftw_malloc(sizeof(double) * x->WindowSize);
    FFTOut = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (x->WindowSize / 2 + 1));
    FFTPlan = fftw_plan_dft_r2c_1d(x->WindowSize, nullptr, nullptr, FFTW_ESTIMATE);

    t_garray *Array;
    int VecSize;
    t_word *Vec;

    if (!(Array = (t_garray *)pd_findbyclass(s, garray_class))) {
        pd_error(x, "[follower~] Array %s not found.", s->s_name);
        return;
    } else if (!garray_getfloatwords(Array, &VecSize, &Vec)) {
        pd_error(x, "[follower~] Bad template for tabwrite '%s'.", s->s_name);
        return;
    }

    // get middle of the array
    int middle = VecSize / 2;
    std::vector<double> AudioChunk(x->WindowSize, 0);
    for (int i = 0; i < x->WindowSize; i++) {
        AudioChunk[i] = Vec[middle + i].w_float;
    }
    fftw_execute_dft_r2c(FFTPlan, AudioChunk.data(), FFTOut);

    std::vector<double> SpectralPower(x->WindowSize / 2 + 1, 0);
    for (int i = 0; i < x->WindowSize / 2 + 1; i++) {
        double real = FFTOut[i][0];
        double imag = FFTOut[i][1];
        SpectralPower[i] = ((real * real + imag * imag) / x->WindowSize) / x->WindowSize;
    }

    for (int i = 0; i < h; i++) {
        double pitchHz = fund * (i + 1);
        int bin = round(pitchHz / (sr / x->WindowSize));
        x->MDP->m_PitchTemplate.push_back(SpectralPower[bin - 1]);
        x->MDP->m_PitchTemplate.push_back(SpectralPower[bin]);
        x->MDP->m_PitchTemplate.push_back(SpectralPower[bin + 1]);
    }
    post("[follower~] Template loaded");
}

// ─────────────────────────────────────
static void Set(Follower *x, t_symbol *s, int argc, t_atom *argv) {
    if (argv[0].a_type != A_SYMBOL) {
        pd_error(x, "[follower~] First argument of set method must be a symbol");
        return;
    }
    std::string method = atom_getsymbol(argv)->s_name;
    if (method == "sigma") {
        x->MDP->SetPitchTemplateSigma(atom_getfloat(argv + 1));
        post("[follower~] Sigma set to %f", atom_getfloat(argv + 1));
    } else if (method == "harmonics") {
        x->MDP->SetHarmonics(atom_getint(argv + 1));
        x->MDP->UpdatePitchTemplate();
        post("[follower~] Using pitch template with %d harmonics", atom_getint(argv + 1));
    } else if (method == "threshold") {
        x->MIR->SetTreshold(atom_getfloat(argv + 1));
        x->MDP->SetTreshold(atom_getfloat(argv + 1));
        post("[follower~] Treshold set to %f", atom_getfloat(argv + 1));
    } else if (method == "time") {
        std::string submethod = atom_getsymbol(argv + 1)->s_name;
        if (submethod == "accum") {
            x->MDP->SetTimeAccumFactor(atom_getfloat(argv + 2));
            printf("[follower~] Time accumulation set to %.4f\n", atom_getfloat(argv + 2));
        } else if (submethod == "coupling") {
            x->MDP->SetTimeCouplingStrength(atom_getfloat(argv + 2));
            printf("[follower~] Time coupling set to %.4f\n", atom_getfloat(argv + 2));
        }

    } else {
        pd_error(x, "[follower~] Unknown method");
    }
}

// ─────────────────────────────────────
static void SetEvent(Follower *x, t_floatarg f) {
    x->CurrentEvent = f;
    x->MDP->SetEvent(f);
}

// ─────────────────────────────────────
static void Start(Follower *x) {
    x->CurrentEvent = -1;
    x->MDP->SetEvent(-1);
    States ScoreStates = x->Score->GetStates();
    x->MDP->SetScoreStates(ScoreStates);
    x->MDP->UpdatePitchTemplate();
    x->MDP->UpdatePhaseValues();

    outlet_float(x->Tempo, ScoreStates[0].BPMExpected);
    outlet_float(x->EventIndex, 0);
}

// ─────────────────────────────────────
static void Follow(Follower *x, t_floatarg f) {
    x->Following = f;
}

// ─────────────────────────────────────
static void Tunning(Follower *x, t_floatarg f) {
    post("[follower~] A4 set to %f Hz", f);
    x->MDP->SetTunning(f);
}

// ─────────────────────────────────────
static void Score(Follower *x, t_symbol *s) {
    LOGE() << "PureData Score Method";
    std::string completePath = x->patchDir->s_name;
    completePath += "/";
    completePath += s->s_name;
    std::ifstream file(completePath);
    if (!file) {
        pd_error(nullptr, "[follower~] Score file not found");
        return;
    }
    x->Score->Parse(x->MDP, completePath.c_str());
    States ScoreStates = x->Score->GetStates();
    x->MDP->SetScoreStates(ScoreStates);
    x->MDP->UpdatePitchTemplate();
    x->MDP->UpdatePhaseValues();

    x->ScoreLoaded = true;
    post("[follower~] Score loaded");
}

// ─────────────────────────────────────
static void ClockTick(Follower *x) {
    if (x->Event != 0) {
        outlet_float(x->Tempo, x->MDP->GetLiveBPM());
        outlet_float(x->EventIndex, x->Event);
    }
}

// ─────────────────────────────────────
static t_int *DspPerform(t_int *w) {
    Follower *x = (Follower *)(w[1]);
    t_sample *in = (t_sample *)(w[2]);
    int n = static_cast<int>(w[3]); // Assuming n is an integer

    if (!x->Score->ScoreLoaded()) {
        return (w + 4);
    }

    std::copy(x->inBuffer.begin() + n, x->inBuffer.end(), x->inBuffer.begin());
    std::copy(in, in + n, x->inBuffer.end() - n);

    x->BlockIndex += n;
    if (!x->ScoreLoaded) {
        return (w + 4);
    }

    if (x->BlockIndex != x->HopSize) {
        return (w + 4);
    }

    x->BlockIndex = 0;
    int Event = x->MDP->GetEvent(x, x->MIR) + 1;
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
    LOGE() << "AddDsp";

    x->BlockSize = sp[0]->s_n;
    x->BlockIndex = 0;
    x->inBuffer.resize(x->WindowSize, 0.0f);
    dsp_add(DspPerform, 3, x, sp[0]->s_vec, sp[0]->s_n);
    LOGE() << "AddDsp Successful";
}

// ─────────────────────────────────────
static void *NewFollower(t_symbol *s, int argc, t_atom *argv) {
    LOGE() << "NewFollower";

    Follower *x = (Follower *)pd_new(FollowerObj);
    x->EventIndex = outlet_new(&x->xObj, &s_float);
    x->Tempo = outlet_new(&x->xObj, &s_float);
    x->WindowSize = 4096.0f;
    x->HopSize = 1024.0f;
    x->Sr = sys_getsr();

    double overlap = 4;

    for (int i = 0; i < argc; i++) {
        if (argv[i].a_type == A_SYMBOL || argc >= i + 1) {
            std::string argument = std::string(atom_getsymbol(&argv[i])->s_name);
            if (argument == "-w") {
                if (argv[i + 1].a_type == A_FLOAT) {
                    x->WindowSize = atom_getfloat(&argv[i + 1]);
                    i++;
                }
            }
            if (argument == "-o") {
                if (argv[i + 1].a_type == A_FLOAT) {
                    overlap = atom_getfloat(&argv[i + 1]);
                    post("overlap %f", overlap);
                    i++;
                }
            }
            if (argument == "-test") {
                x->Testing = true;
                x->Debug = outlet_new(&x->xObj, &s_anything);
            }
        }
    }
    if (overlap != 4) {
        x->HopSize = x->WindowSize / overlap;
    }

    t_canvas *canvas = canvas_getcurrent();
    x->patchDir = canvas_getdir(canvas);

    x->Clock = clock_new(x, (t_method)ClockTick);
    x->Event = -1;

    x->Score = new FollowerScore(x); // TODO: rethink about use new
    x->MIR = new FollowerMIR(x);
    x->MDP = new FollowerMDP(x);

    LOGE() << "Returning NewFollower";
    return x;
}

// ─────────────────────────────────────
static void *FreeFollower(Follower *x) {
    LOGE() << "Start Free of NewFollower";
    delete x->Score;
    delete x->MIR;
    delete x->MDP;
    LOGE() << "End Free of NewFollower";
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

    // pitch template
    class_addmethod(FollowerObj, (t_method)Set, gensym("set"), A_GIMME, 0);

    // template
    class_addmethod(FollowerObj, (t_method)GerenateAnalTemplate, gensym("template"), A_SYMBOL,
                    A_FLOAT, A_FLOAT, A_FLOAT, 0);

    class_addbang(FollowerObj, (t_method)TimeValues);
}
