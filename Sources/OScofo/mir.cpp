#include "mir.hpp"

#include <math.h>
#include <vector>

// ╭─────────────────────────────────────╮
// │Constructor and Destructor Functions │
// ╰─────────────────────────────────────╯
OScofoMIR::OScofoMIR(float Sr, float WindowSize, float HopSize) {
    LOGE() << "OScofoMIR::OScofoMIR";

    m_HopSize = HopSize;
    m_WindowSize = WindowSize;
    m_Sr = Sr;

    int WindowHalf = WindowSize / 2;
    m_FFTIn = (double *)fftw_alloc_real(WindowSize);
    m_FFTOut = (fftw_complex *)fftw_alloc_complex(WindowHalf + 1);
    m_FFTPlan = fftw_plan_dft_r2c_1d(m_WindowSize, m_FFTIn, m_FFTOut, FFTW_MEASURE);

    if (m_FFTPlan == nullptr) {
        LOGE() << "OScofoMIR::OScofoMIR fftw_plan_dft_r2c_1d failed";
    }

    LOGE() << "OScofoMIR::OScofoMIR end";
}

// ─────────────────────────────────────
OScofoMIR::~OScofoMIR() {
    fftw_destroy_plan(m_FFTPlan);
    fftw_free(m_FFTIn);
    fftw_free(m_FFTOut);
}

// ╭─────────────────────────────────────╮
// │                Utils                │
// ╰─────────────────────────────────────╯
//  ─────────────────────────────────────
double OScofoMIR::Mtof(double note, double tunning) {
    return tunning * std::pow(2.0, (note - 69) / 12.0);
}

// ─────────────────────────────────────
double OScofoMIR::Ftom(double freq, double tunning) {
    return 69 + 12 * log2(freq / tunning);
}

// ─────────────────────────────────────
double OScofoMIR::Freq2Bin(double freq, double n, double sr) {
    double bin;
    bin = freq * n / sr;
    return round(bin);
}

// ─────────────────────────────────────
// double OScofoMIR::IsSilence() {
//     if (m_Desc < m_dBTreshold) {
//         return false;
//     }
// }

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void OScofoMIR::SetTreshold(double dB) {
    m_dBTreshold = dB;
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void OScofoMIR::GetFFTDescriptions(const std::vector<double> &In, Description &Desc) {
    LOGE() << "OScofoMIR::GetFFTDescriptions";

    int N = In.size();
    int NHalf = N / 2;

    // Resize vectors if necessary
    if (NHalf != Desc.SpectralPower.size()) {
        Desc.SpectralPower.resize(NHalf);
    }

    if (NHalf != Desc.NormSpectralPower.size()) {
        Desc.NormSpectralPower.resize(NHalf);
    }

    // Copy input data and execute FFT
    std::copy(In.begin(), In.end(), m_FFTIn);
    fftw_execute(m_FFTPlan);

    double Real, Imag;
    Desc.MaxAmp = 0;
    Desc.TotalPower = 0;
    double GeometricMeanProduct = 1.0;
    double ArithmeticMeanSum = 0.0;
    double WindowHalfPlusOneRecip = 1.0 / NHalf;

    for (int i = 0; i < NHalf; i++) {
        Real = m_FFTOut[i][0];
        Imag = m_FFTOut[i][1];

        double power = (Real * Real + Imag * Imag) / N;
        Desc.SpectralPower[i] = power;
        Desc.TotalPower += power;

        if (power > Desc.MaxAmp) {
            Desc.MaxAmp = power;
        }
        GeometricMeanProduct *= power;
    }

    for (int i = 0; i < NHalf; i++) {
        ArithmeticMeanSum += Desc.SpectralPower[i];
        Desc.NormSpectralPower[i] = Desc.SpectralPower[i] / Desc.MaxAmp;
    }
    ArithmeticMeanSum *= WindowHalfPlusOneRecip;

    // Calculate Spectral Flatness
    if (ArithmeticMeanSum <= 0) {
        Desc.SpectralFlatness = -1;
    } else {
        GeometricMeanProduct = pow(GeometricMeanProduct, WindowHalfPlusOneRecip);
        Desc.SpectralFlatness = GeometricMeanProduct / ArithmeticMeanSum;
    }

    LOGE() << "end OScofoMIR::GetFFTDescriptions";
}

// ╭─────────────────────────────────────╮
// │                 RMS                 │
// ╰─────────────────────────────────────╯
void OScofoMIR::GetRMS(const std::vector<double> &In, Description &Desc) {
    LOGE() << "OScofoMIR::GetRMS";
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
    if (dB < m_dBTreshold) {
        Desc.PassTreshold = false;
    } else {
        Desc.PassTreshold = true;
    }

    // LogStream() << "m_dbTreshold: " << m_dBTreshold;
    LOGE() << "End OScofoMIR::GetRMS";
}

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void OScofoMIR::GetDescription(const std::vector<double> &In, Description &Desc) {
    LOGE() << "OScofoMIR::GetDescription";
    GetRMS(In, Desc);
    if (!Desc.PassTreshold) {
        return;
    }
    GetFFTDescriptions(In, Desc);
    LOGE() << "end OScofoMIR::GetDescription";
}
