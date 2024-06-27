#include "follower.hpp"

#include <cmath>
#include <vector>

#include <algorithm>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(Follower *Obj) {
    LOGE() << "FollowerMIR::FollowerMIR";

    HopSize = Obj->HopSize;
    WindowSize = Obj->WindowSize;
    Sr = Obj->Sr;
    x = Obj;

    // work with double?
    FFTIn = (float *)fftwf_malloc(sizeof(float) * WindowSize);
    FFTOut = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * (WindowSize / 2 + 1));
    FFTPlan = fftwf_plan_dft_r2c_1d(WindowSize, nullptr, nullptr, FFTW_ESTIMATE);

    LOGE() << "FollowerMIR::FollowerMIR end";
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetFFT(std::vector<float> *in, Description *Desc) {

    int n = in->size();

    if (n / 2 + 1 != Desc->SpectralPower.size()) {
        Desc->SpectralPower.resize(n / 2 + 1);
    }

    if (n / 2 + 1 != Desc->NormSpectralPower.size()) {
        Desc->NormSpectralPower.resize(n / 2 + 1);
    }

    fftwf_execute_dft_r2c(FFTPlan, in->data(), FFTOut);

    float Real, Imag;
    Desc->MaxAmp = 0;
    for (int i = 0; i < n / 2 + 1; i++) {
        Real = FFTOut[i][0];
        Imag = FFTOut[i][1];
        Desc->SpectralPower[i] = (Real * Real + Imag * Imag) / n;
        if (Desc->SpectralPower[i] > Desc->MaxAmp) {
            Desc->MaxAmp = Desc->SpectralPower[i];
        }
    }

    // normalize using the maximum value
    for (int i = 0; i < n / 2 + 1; i++) {
        Desc->NormSpectralPower[i] = Desc->SpectralPower[i] / Desc->MaxAmp;
    }
}

// ─────────────────────────────────────
float getMaxElement(const std::vector<float> &vec) {
    if (vec.empty()) {
        return 0.0f; // or any other appropriate default value
    }
    float maxVal = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] > maxVal) {
            maxVal = vec[i];
        }
    }
    return maxVal;
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
// │      Antescofo Time Prediction      │
// ╰─────────────────────────────────────╯

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

// ─────────────────────────────────────
float BesselFunction(float x) {
    int n = 1000;        // Number of intervals for numerical integration
    double h = M_PI / n; // Width of each interval
    double sum = 0.0;
    // Use the trapezoidal rule for numerical integration
    for (int i = 0; i <= n; ++i) {
        double theta = i * h;
        double term = exp(x * cos(theta));
        if (i == 0 || i == n) {
            sum += 0.5 * term;
        } else {
            sum += term;
        }
    }

    return sum * h / M_PI;
}

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetDescription(std::vector<float> *in, Description *Desc, float Tunning) {
    Desc->WindowSize = WindowSize;
    Desc->Sr = Sr;
    Desc->Tunning = Tunning;

    GetRMS(in, Desc);

    if (Desc->dB < -40) {
        return;
    }
    // apply hanning to in
    // for (int i = 0; i < Desc->WindowSize; i++) {
    //     (*in)[i] *= 0.5 * (1 - cos(2 * M_PI * i / (Desc->WindowSize - 1)));
    GetFFT(in, Desc);
}
