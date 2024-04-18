#include "follower.hpp"
#include <cmath>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(int hopSize, int windowSize, int sr)
    : HopSize(hopSize), WindowSize(windowSize), Sr(sr) {

    // Pitch
    CreateYin(0.6, -60);

    // Notes
    smpl_t silence, minioi_ms, release_drop;
    notes = new_aubio_notes("default", windowSize, hopSize, Sr);

    // SPectrogram
    fftIn = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * windowSize);
    fftOut = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * windowSize);
}

// ╭─────────────────────────────────────╮
// │            Yin Algorithm            │
// ╰─────────────────────────────────────╯
bool FollowerMIR::CreateYin(float tolerance, float silence) {
    fvec_t *out = new_fvec(1);
    YinInstance = new_aubio_pitch("yinfast", WindowSize, WindowSize, Sr);
    if (YinInstance == nullptr) {
        return false;
    }
    aubio_pitch_set_tolerance(YinInstance, tolerance);
    aubio_pitch_set_silence(YinInstance, silence);
    aubio_pitch_set_unit(YinInstance, "Hz");
    return true;
}

// ─────────────────────────────────────
void FollowerMIR::GetYin(std::vector<float> *in, Description *Desc, float Tunning) {
    if (YinInstance == nullptr) {
        Desc->Freq = 0;
        Desc->Quality = 0;
        return;
    }
    fvec_t *pitch = new_fvec(1);
    fvec_t AubioIn;
    AubioIn.length = in->size();
    AubioIn.data = new smpl_t[AubioIn.length];
    std::copy(in->begin(), in->end(), AubioIn.data);
    smpl_t freq, quality, envelope;
    aubio_pitch_do(YinInstance, (const fvec_t *)&AubioIn, pitch);
    freq = fvec_get_sample(pitch, 0);
    quality = aubio_pitch_get_confidence(YinInstance);
    Desc->Freq = freq;
    Desc->Midi = Follower_f2midi(freq, Tunning);
    Desc->Quality = quality;

    return;
}

// ╭─────────────────────────────────────╮
// │                Notes                │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetNotes(std::vector<float> *in, Description *Desc) {
    fvec_t *pitch = new_fvec(5);
    fvec_t AubioIn;
    AubioIn.length = in->size();
    AubioIn.data = new smpl_t[AubioIn.length];
    std::copy(in->begin(), in->end(), AubioIn.data);
    smpl_t freq, quality, envelope;
    aubio_notes_do(notes, (const fvec_t *)&AubioIn, pitch);
    freq = fvec_get_sample(pitch, 0);
    post("freq is %f", freq);
}
// ╭─────────────────────────────────────╮
// │          MFCC Observation           │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetMFCC(std::vector<float> *in, Description *Desc) {
    if (YinInstance == nullptr) {
        Desc->Freq = 0;
        Desc->Quality = 0;
        return;
    }
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯

void FollowerMIR::GetSpectrogram(std::vector<float> *in, Description *Desc) {
    int n = in->size();
    fftw_plan fftPlan = fftw_plan_dft_1d(n, fftIn, fftOut, FFTW_FORWARD, FFTW_ESTIMATE);
    for (int i = 0; i < n; ++i) {
        fftIn[i][0] = (*in)[i];
        fftOut[i][1] = 0.0;
    }
    fftw_execute(fftPlan);
    std::vector<float> out(n);
    Desc->Spectrogram = fftOut;
}

// ╭─────────────────────────────────────╮
// │                 RMS                 │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetRMS(std::vector<float> *in, Description *Desc) {
    double sumOfSquares = 0.0;
    for (float sample : *in) {
        sumOfSquares += sample * sample;
    }
    double rms = std::sqrt(sumOfSquares / in->size());
    float reference = 1.0;
    float dB = 20.0 * std::log10(rms / reference);
    if (std::isinf(dB)) {
        dB = -100;
    }
    Desc->dB = dB;
}

// ╭─────────────────────────────────────╮
// │                Time                 │
// ╰─────────────────────────────────────╯

/*
 * LARGE and JONES. The Dynamics of Attending: How People Track Time-Varying Events. 1999.

*/
float FollowerMIR::TimePrediction() {

    return 0;
}

void FollowerMIR::ResetElapsedTime() {
    EventTimeElapsed = 0;
}

void FollowerMIR::UpdateTempoInEvent() {
    EventTimeElapsed += 1000 / Sr * HopSize;
}

float FollowerMIR::GetEventTimeElapsed() {
    return EventTimeElapsed;
};

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetDescription(std::vector<float> *in, Description *Desc, float Tunning) {
    GetNotes(in, Desc);
    GetRMS(in, Desc);
    GetYin(in, Desc, Tunning);
    // GetSpectrogram(in, Desc);
}
