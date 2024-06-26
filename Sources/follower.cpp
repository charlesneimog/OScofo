#include "follower.hpp"

#include <algorithm>
#include <fstream>
#include <random>

static t_class *FollowerObj;

// ─────────────────────────────────────
void GerenateAnalTemplate(Follower *x, t_symbol *s, t_float sr, t_float fund, t_float h) {
    float *FFTIn;
    fftwf_complex *FFTOut;
    fftwf_plan FFTPlan;
    x->MDP->PitchTemplate.clear();

    FFTIn = (float *)fftwf_malloc(sizeof(float) * x->WindowSize);
    FFTOut = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * (x->WindowSize / 2 + 1));
    FFTPlan = fftwf_plan_dft_r2c_1d(x->WindowSize, nullptr, nullptr, FFTW_ESTIMATE);

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
    std::vector<float> AudioChunk(x->WindowSize, 0);
    for (int i = 0; i < x->WindowSize; i++) {
        AudioChunk[i] = Vec[middle + i].w_float;
    }
    fftwf_execute_dft_r2c(FFTPlan, AudioChunk.data(), FFTOut);

    std::vector<double> SpectralPower(x->WindowSize / 2 + 1, 0);
    for (int i = 0; i < x->WindowSize / 2 + 1; i++) {
        float real = FFTOut[i][0];
        float imag = FFTOut[i][1];
        SpectralPower[i] = ((real * real + imag * imag) / x->WindowSize) / x->WindowSize;
    }

    for (int i = 0; i < h; i++) {
        float pitchHz = fund * (i + 1);
        int bin = round(pitchHz / (sr / x->WindowSize));
        x->MDP->PitchTemplate.push_back(SpectralPower[bin - 1]);
        x->MDP->PitchTemplate.push_back(SpectralPower[bin]);
        x->MDP->PitchTemplate.push_back(SpectralPower[bin + 1]);
    }
    post("[follower~] Template loaded");
}

// ─────────────────────────────────────
// Function to generate samples from a Gaussian distribution centered around bin
std::vector<double> GenerateGaussianSamples(double Mu, double Sigma, int NumPoints) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(Mu, Sigma);

    std::vector<double> samples(NumPoints);
    for (auto &sample : samples) {
        sample = dist(gen);
    }
    return samples;
}

// ─────────────────────────────────────
void GerenatePitchTemplate(Follower *x, t_floatarg f) {
    std::vector<double> Template;
    const double mu1 = 30 * 1;
    const double mu2 = 60 * 1;
    std::vector<double> samples1 = GenerateGaussianSamples(mu1, 1, 1024);
    std::vector<double> samples2 = GenerateGaussianSamples(mu2, 1, 1024);
    std::vector<double> samples;

    samples.reserve(2048);
    samples.insert(samples.end(), samples1.begin(), samples1.end());
    samples.insert(samples.end(), samples2.begin(), samples2.end());

    double sum = 0.0;
    for (int i = 0; i < 2048; i++) {
        sum += samples[i];
    }
    for (int i = 0; i < 2048; i++) {
        samples[i] = samples[i] / sum;
    }

    t_atom *out = new t_atom[2048];
    for (int i = 0; i < 2048; i++) {
        SETFLOAT(out + i, samples[i]);
    }
    outlet_list(x->Tempo, &s_list, 2048, out);
}

// ─────────────────────────────────────
static void SetEvent(Follower *x, t_floatarg f) {
    x->CurrentEvent = f;
    x->MDP->CurrentEvent = f;
}

// ─────────────────────────────────────
static void Start(Follower *x) {
    x->CurrentEvent = -1;
    x->MDP->CurrentEvent = -1;
    x->MDP->ResetLiveBpm();

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
    x->Score->Tunning = f;
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
    x->WindowSize = 2048;
    x->HopSize = 512;
    float overlap = 4;

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

    x->Sr = sys_getsr();

    x->Score = new FollowerScore(x);
    x->MDP = new FollowerMDP(x);
    x->MDP->Tunning = 440;
    x->MIR = new FollowerMIR(x, x->HopSize, x->WindowSize, x->Sr);

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

    // template
    class_addmethod(FollowerObj, (t_method)GerenateAnalTemplate, gensym("template"), A_SYMBOL,
                    A_FLOAT, A_FLOAT, A_FLOAT, 0);
}
