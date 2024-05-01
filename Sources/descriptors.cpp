#include "follower.hpp"

#include <cmath>
#include <vector>

// #include <chrono>
// #include <iostream>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(Follower *Obj, int hopSize, int windowSize, int sr)
    : HopSize(hopSize), WindowSize(windowSize), Sr(sr) {

    x = Obj;
    // work with double?
    FFTIn = (float *)fftwf_malloc(sizeof(float) * WindowSize);
    FFTOut = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * (WindowSize / 2 + 1));
    FFTPlan = fftwf_plan_dft_r2c_1d(WindowSize, nullptr, nullptr, FFTW_ESTIMATE);
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetFFT(std::vector<float> *in, Description *Desc) {
    int n = in->size();
    if (n / 2 + 1 != Desc->SpectralPower.size()) {
        Desc->SpectralPower.resize(n / 2 + 1);
    }
    fftwf_execute_dft_r2c(FFTPlan, in->data(), FFTOut);
    for (int i = 0; i < n / 2 + 1; i++) {
        float real = FFTOut[i][0];
        float imag = FFTOut[i][1];
        Desc->SpectralPower[i] = (real * real + imag * imag) / n;
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
    for (int i = 0; i < Desc->WindowSize; i++) {
        (*in)[i] *= 0.5 * (1 - cos(2 * M_PI * i / (Desc->WindowSize - 1)));
    }

    GetFFT(in, Desc);
}
