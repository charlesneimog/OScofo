#include "follower.hpp"

#include <cmath>
#include <vector>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯
FollowerMIR::FollowerMIR(Follower *Obj) {
    LOGE() << "FollowerMIR::FollowerMIR";

    m_HopSize = Obj->HopSize;
    m_WindowSize = Obj->WindowSize;
    m_Sr = Obj->Sr;
    m_x = Obj;

    m_FFTOut = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (m_WindowSize / 2 + 1));
    m_FFTPlan = fftw_plan_dft_r2c_1d(m_WindowSize, nullptr, nullptr, FFTW_ESTIMATE);

    LOGE() << "FollowerMIR::FollowerMIR end";
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void FollowerMIR::SetTreshold(double dB) {
    m_dBTreshold = dB;
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetFFT(std::vector<double> in, m_Description *Desc) {

    int n = in.size();

    if (n / 2 + 1 != Desc->SpectralPower.size()) {
        Desc->SpectralPower.resize(n / 2 + 1);
    }

    if (n / 2 + 1 != Desc->NormSpectralPower.size()) {
        Desc->NormSpectralPower.resize(n / 2 + 1);
    }

    std::vector<double> inCopy = in;
    fftw_execute_dft_r2c(m_FFTPlan, inCopy.data(), m_FFTOut);

    double Real, Imag;
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
void FollowerMIR::GetRMS(std::vector<double> in, m_Description *Desc) {
    double sumOfSquares = 0.0;
    for (double sample : in) {
        sumOfSquares += sample * sample;
    }
    double rms = std::sqrt(sumOfSquares / in.size());
    double dB = 20.0 * std::log10(rms);
    if (std::isinf(dB)) {
        dB = -100;
    }
    Desc->dB = dB;
}

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetDescription(std::vector<double> in, m_Description *Desc, double Tunning) {
    Desc->WindowSize = m_WindowSize;
    Desc->Sr = m_Sr;

    GetRMS(in, Desc);

    if (Desc->dB < m_dBTreshold) {
        return;
    }
    for (int i = 0; i < m_WindowSize; i++) {
        in[i] *= 0.5 * (1.0 - cos(2.0 * M_PI * i / (m_WindowSize - 1)));
    }

    GetFFT(in, Desc);
}
