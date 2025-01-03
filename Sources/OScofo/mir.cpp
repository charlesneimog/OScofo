#include "mir.hpp"

#include <algorithm>
#include <math.h>
#include <vector>

namespace OScofo {

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
MIR::MIR(float Sr, float FftSize, float HopSize) {
    LOGE() << "OScofoMIR::OScofoMIR";

    m_HopSize = HopSize;
    m_FftSize = FftSize;
    m_Sr = Sr;

    int WindowHalf = FftSize / 2;
    m_FFTIn = (double *)fftw_alloc_real(FftSize);
    if (!m_FFTIn) {
        SetError("OScofoMIR::OScofoMIR fftw_alloc_real failed");
        return;
    }

    m_FFTOut = (fftw_complex *)fftw_alloc_complex(WindowHalf + 1);
    if (!m_FFTOut) {
        fftw_free(m_FFTIn); // Free previously allocated memory
        SetError("OScofoMIR::OScofoMIR fftw_alloc_complex failed");
        return;
    }

    m_FFTPlan = fftw_plan_dft_r2c_1d(m_FftSize, m_FFTIn, m_FFTOut, FFTW_ESTIMATE);

    // blackman
    m_WindowingFunc.resize(m_FftSize);
    for (int i = 0; i < m_FftSize; i++) {
        m_WindowingFunc[i] = 0.5 * (1.0 - cos(2.0 * M_PI * i / (m_FftSize - 1)));
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
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯

void MIR::GetFFTDescriptions(std::vector<double> &In, Description &Desc) {
    int N = In.size();
    int NHalf = N / 2;

    if (NHalf != Desc.SpectralPower.size()) {
        Desc.SpectralPower.resize(NHalf);
    }

    if (NHalf != Desc.NormSpectralPower.size()) {
        Desc.NormSpectralPower.resize(NHalf);
    }

    std::copy(In.begin(), In.end(), m_FFTIn);
    fftw_execute(m_FFTPlan);

    double Real, Imag;
    Desc.MaxAmp = 0;
    Desc.TotalPower = 0;
    std::vector<double> nthRoots(NHalf);
    double GeometricMeanProduct = 1.0;
    double ArithmeticMeanSum = 0.0;
    double WindowHalfPlusOneRecip = 1.0 / NHalf;

    for (int i = 0; i < NHalf; i++) {
        Real = m_FFTOut[i][0];
        Imag = m_FFTOut[i][1];
        Desc.SpectralPower[i] = (Real * Real + Imag * Imag) / N; // Amp
        Desc.TotalPower += Desc.SpectralPower[i];
        if (Desc.SpectralPower[i] > Desc.MaxAmp) {
            Desc.MaxAmp = Desc.SpectralPower[i];
        }
        GeometricMeanProduct *= pow(Desc.SpectralPower[i], WindowHalfPlusOneRecip);
    }

    // Normalize Spectral Power
    for (int i = 0; i < NHalf; i++) {
        ArithmeticMeanSum += Desc.SpectralPower[i];
        Desc.NormSpectralPower[i] = Desc.SpectralPower[i] / Desc.MaxAmp;
    }
    ArithmeticMeanSum *= WindowHalfPlusOneRecip;

    // Spectral Flatness
    if (ArithmeticMeanSum <= 0) {
        Desc.SpectralFlatness = -1;
    } else {
        Desc.SpectralFlatness = GeometricMeanProduct / ArithmeticMeanSum;
    }

    // calculate
}

// ╭─────────────────────────────────────╮
// │              Loudness               │
// ╰─────────────────────────────────────╯
void MIR::GetLoudness(std::vector<double> &In, Description &Desc) {
    return;
    double totalEnergy = 0.0;
    for (double sample : In) {
        totalEnergy += sample * sample; // Sum of squared amplitudes
    }

    double threshold = 1e-6;
    double loudness = totalEnergy / In.size();
    Desc.Loudness = loudness;
}

// ╭─────────────────────────────────────╮
// │                 RMS                 │
// ╰─────────────────────────────────────╯
void MIR::GetRMS(std::vector<double> &In, Description &Desc) {
    double sumOfSquares = 0.0;
    for (double sample : In) {
        sumOfSquares += sample * sample;
    }
    double rms = std::sqrt(sumOfSquares / In.size());
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

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void MIR::GetDescription(std::vector<double> &In, Description &Desc) {
    // apply windowing function
    for (int i = 0; i < m_FftSize; i++) {
        In[i] *= m_WindowingFunc[i];
    }

    GetLoudness(In, Desc);
    GetRMS(In, Desc);
    GetFFTDescriptions(In, Desc);
}
} // namespace OScofo
