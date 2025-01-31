#include "mir.hpp"

#include <algorithm>
#include <math.h>
#include <vector>
#include <numeric>

namespace OScofo {

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
MIR::MIR(float Sr, float FftSize, float HopSize) {
    LOGE() << "OScofoMIR::OScofoMIR";

    m_HopSize = HopSize;
    m_FftSize = FftSize;
    m_Sr = Sr;

    float WindowHalf = FftSize / 2;
    m_FFTIn = (double *)fftw_alloc_real((size_t)FftSize);
    if (!m_FFTIn) {
        SetError("OScofoMIR::OScofoMIR fftw_alloc_real failed");
        return;
    }

    m_FFTOut = (fftw_complex *)fftw_alloc_complex((size_t)WindowHalf + 1);
    if (!m_FFTOut) {
        fftw_free(m_FFTIn); // Free previously allocated memory
        SetError("OScofoMIR::OScofoMIR fftw_alloc_complex failed");
        return;
    }

    m_FFTPlan = fftw_plan_dft_r2c_1d((int)m_FftSize, m_FFTIn, m_FFTOut, FFTW_ESTIMATE);

    // blackman
    m_WindowingFunc.resize((size_t)m_FftSize);
    for (size_t i = 0; i < (size_t)m_FftSize; i++) {
        m_WindowingFunc[i] = 0.5 * (1.0 - cos(2.0 * M_PI * (int)i / ((double)m_FftSize - 1)));
    }
}

// ─────────────────────────────────────
MIR::~MIR() {
    if (m_FFTPlan != nullptr) {
        fftw_destroy_plan(m_FFTPlan);
        m_FFTPlan = nullptr;
    }

    if (m_FFTIn != nullptr) {
        fftw_free(m_FFTIn);
        m_FFTIn = nullptr;
    }
    if (m_FFTOut != nullptr) {
        fftw_free(m_FFTOut);
        m_FFTOut = nullptr;
    }
}

// ╭─────────────────────────────────────╮
// │               Errors                │
// ╰─────────────────────────────────────╯
bool MIR::HasErrors() {
    return m_HasErrors;
}

// ─────────────────────────────────────
std::vector<std::string> MIR::GetErrorMessage() {
    return m_Errors;
}

// ─────────────────────────────────────
void MIR::SetError(const std::string &message) {
    m_HasErrors = true;
    m_Errors.push_back(message);
}

// ─────────────────────────────────────
void MIR::ClearError() {
    m_HasErrors = false;
    m_Errors.clear();
}

// ╭─────────────────────────────────────╮
// │                Utils                │
// ╰─────────────────────────────────────╯
double MIR::Mtof(double note, double tunning) {
    return tunning * std::pow(2.0, (note - 69) / 12.0);
}

// ─────────────────────────────────────
double MIR::Ftom(double freq, double tunning) {
    return 69 + 12 * log2(freq / tunning);
}

// ─────────────────────────────────────
double MIR::Freq2Bin(double Freq, double n, double sr) {
    double bin;
    bin = Freq * n / sr;
    return round(bin);
}

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void MIR::SetdBTreshold(double dB) {
    m_dBTreshold = dB;
}

// ╭─────────────────────────────────────╮
// │          Audio Descriptors          │
// ╰─────────────────────────────────────╯
void MIR::GetLoudness(std::vector<double> &In, Description &Desc) {
    return;
    double totalEnergy = 0.0;
    for (double sample : In) {
        totalEnergy += sample * sample; // Sum of squared amplitudes
    }

    double loudness = totalEnergy / (double)In.size();
    Desc.Loudness = loudness;
}

// ─────────────────────────────────────
void MIR::GetRMS(std::vector<double> &In, Description &Desc) {
    double sumOfSquares = 0.0;
    for (double sample : In) {
        sumOfSquares += sample * sample;
    }
    double rms = std::sqrt(sumOfSquares / (double)In.size());
    double dB = 20.0 * std::log10(rms);
    if (std::isinf(dB)) {
        dB = -100;
    }
    Desc.dB = dB;
    Desc.Amp = 10 * std::pow(10, dB / 20);
    if (dB < m_dBTreshold) {
        Desc.Silence = true;
    } else {
        Desc.Silence = false;
    }
}

// ─────────────────────────────────────
void MIR::GetFFTDescriptions(std::vector<double> &In, Description &Desc) {
    // real audio analisys
    size_t N = In.size();
    size_t NHalf = N / 2;

    if (NHalf != Desc.SpectralPower.size()) {
        Desc.SpectralPower.resize(NHalf);
    }

    if (NHalf != Desc.NormSpectralPower.size()) {
        Desc.NormSpectralPower.resize(NHalf);
    }

    std::copy(In.begin(), In.end(), m_FFTIn);
    fftw_execute(m_FFTPlan);

    // FFT Mag
    Desc.MaxAmp = 0;
    double Real, Imag;
    for (size_t i = 0; i < NHalf; i++) {
        Real = m_FFTOut[i][0];
        Imag = m_FFTOut[i][1];
        Desc.SpectralPower[i] = sqrt(Real * Real + Imag * Imag) / (double)N;
        if (Desc.SpectralPower[i] > Desc.MaxAmp) {
            Desc.MaxAmp = Desc.SpectralPower[i];
        }
    }

    // Normalize Spectral Power
    double sum_power = std::accumulate(Desc.SpectralPower.begin(), Desc.SpectralPower.end(), 0.0);
    for (size_t i = 0; i < NHalf; i++) {
        Desc.NormSpectralPower[i] = (Desc.SpectralPower[i] + 1e-12) / (sum_power + 1e-12);
    }

    const double mean = 1.0 / NHalf; // Sum is 1.0, so mean = 1/N
    double variance = 0.0;
    for (size_t i = 0; i < NHalf; i++) {
        double diff = Desc.NormSpectralPower[i] - mean;
        variance += diff * diff;
    }
    variance /= NHalf;
    Desc.StdDev = std::sqrt(variance);
}

// ─────────────────────────────────────
void MIR::GetSpectralFlux(Description &Desc) {
    if (m_PreviousSpectralPower.empty()) {
        m_PreviousSpectralPower.resize(Desc.SpectralPower.size());
        std::copy(Desc.SpectralPower.begin(), Desc.SpectralPower.end(), m_PreviousSpectralPower.begin());
        Desc.SpectralFlux = 0;
        return;
    }
    double SpectralFlux = 0.0;
    size_t NHalf = Desc.SpectralPower.size();

    // Calculate the flux: sum of positive differences
    for (size_t i = 0; i < NHalf; i++) {
        double Delta = Desc.SpectralPower[i] - m_PreviousSpectralPower[i];
        if (Delta > 0.0) {
            SpectralFlux += Delta;
        }
    }
    std::copy(Desc.SpectralPower.begin(), Desc.SpectralPower.end(), m_PreviousSpectralPower.begin());
    Desc.SpectralFlux = SpectralFlux;
}

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void MIR::GetDescription(std::vector<double> &In, Description &Desc) {
    // apply windowing function
    for (size_t i = 0; i < (size_t)m_FftSize; i++) {
        In[i] *= m_WindowingFunc[i];
    }

    GetLoudness(In, Desc);
    GetRMS(In, Desc);
    GetFFTDescriptions(In, Desc);

    // after FFT, get most descriptors
    bool m_SpectralFlux = true; // TODO: This must be controled inside MDP
    if (m_SpectralFlux) {
        GetSpectralFlux(Desc);
    }
}
} // namespace OScofo
