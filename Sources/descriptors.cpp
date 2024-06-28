#include "follower.hpp"

#include <cmath>
#include <vector>

#include <algorithm>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(Follower *Obj) {
    LOGE() << "FollowerMIR::FollowerMIR";

    m_HopSize = Obj->HopSize;
    m_WindowSize = Obj->WindowSize;
    m_Sr = Obj->Sr;
    m_x = Obj;

    // work with double?
    m_FFTIn = (float *)fftwf_malloc(sizeof(float) * m_WindowSize);
    m_FFTOut = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * (m_WindowSize / 2 + 1));
    m_FFTPlan = fftwf_plan_dft_r2c_1d(m_WindowSize, nullptr, nullptr, FFTW_ESTIMATE);

    LOGE() << "FollowerMIR::FollowerMIR end";
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetFFT(std::vector<float> in, m_Description *Desc) {

    int n = in.size();

    if (n / 2 + 1 != Desc->SpectralPower.size()) {
        Desc->SpectralPower.resize(n / 2 + 1);
    }

    if (n / 2 + 1 != Desc->NormSpectralPower.size()) {
        Desc->NormSpectralPower.resize(n / 2 + 1);
    }

    fftwf_execute_dft_r2c(m_FFTPlan, in.data(), m_FFTOut);

    float Real, Imag;
    Desc->MaxAmp = 0;
    for (int i = 0; i < n / 2 + 1; i++) {
        Real = m_FFTOut[i][0];
        Imag = m_FFTOut[i][1];
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

// ╭─────────────────────────────────────╮
// │                 RMS                 │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetRMS(std::vector<float> in, m_Description *Desc) {
    double sumOfSquares = 0.0;
    for (float sample : in) {
        sumOfSquares += sample * sample;
    }
    double rms = std::sqrt(sumOfSquares / in.size());
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
    m_EventTimeElapsed = 0;
}

void FollowerMIR::UpdateTempoInEvent() {
    m_EventTimeElapsed += 1000 / m_Sr * m_HopSize;
}

float FollowerMIR::GetEventTimeElapsed() {
    return m_EventTimeElapsed;
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
void FollowerMIR::GetDescription(std::vector<float> in, m_Description *Desc, float Tunning) {
    Desc->WindowSize = m_WindowSize;
    Desc->Sr = m_Sr;
    Desc->Tunning = Tunning;

    GetRMS(in, Desc);
    if (Desc->dB < -40) {
        return;
    }

    GetFFT(in, Desc);
}
