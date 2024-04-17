#include "follower.hpp"
#include <cmath>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(int hopSize, int windowSize, int sr)
    : HopSize(hopSize), WindowSize(windowSize), Sr(sr) {
    CreateYin(0.6, -60);
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
    GetRMS(in, Desc);
    GetYin(in, Desc, Tunning);
}
