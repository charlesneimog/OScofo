#include "mir.hpp"

#include <cmath>
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
    m_FFTOut = new fftw_complex[WindowHalf];
    m_FFTPlan = fftw_plan_dft_r2c_1d(m_WindowSize, nullptr, nullptr, FFTW_ESTIMATE);
    if (m_FFTPlan == nullptr) {
        LOGE() << "OScofoMIR::OScofoMIR fftw_plan_dft_r2c_1d failed";
    }

    LOGE() << "OScofoMIR::OScofoMIR end";
}

// ─────────────────────────────────────
OScofoMIR::~OScofoMIR() {
    delete[] m_FFTOut;
    fftw_destroy_plan(m_FFTPlan);
}

// ╭─────────────────────────────────────╮
// │                Utils                │
// ╰─────────────────────────────────────╯
//  ─────────────────────────────────────
double OScofoMIR::Mtof(double note, double tunning) {
    return tunning * pow(2.0, (note - 69) / 12.0);
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

    if (NHalf != Desc.SpectralPower.size()) {
        Desc.SpectralPower.resize(NHalf);
    }

    if (NHalf != Desc.NormSpectralPower.size()) {
        Desc.NormSpectralPower.resize(NHalf);
    }

    std::vector<double> inCopy = In;
    fftw_execute_dft_r2c(m_FFTPlan, inCopy.data(), m_FFTOut);

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
        Desc.SpectralPower[i] = (Real * Real + Imag * Imag) / N;
        Desc.TotalPower += Desc.SpectralPower[i];
        if (Desc.SpectralPower[i] > Desc.MaxAmp) {
            Desc.MaxAmp = Desc.SpectralPower[i];
        }
        GeometricMeanProduct *= pow(Desc.SpectralPower[i], WindowHalfPlusOneRecip);
    }

    for (int i = 0; i < NHalf; i++) {
        ArithmeticMeanSum += Desc.SpectralPower[i];
    }
    ArithmeticMeanSum *= WindowHalfPlusOneRecip;

    if (ArithmeticMeanSum <= 0) {
        Desc.SpectralFlatness = -1;
    } else {
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

    LOGE() << "End OScofoMIR::GetRMS";
}

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void OScofoMIR::GetDescription(const std::vector<double> &In, Description &Desc) {
    LOGE() << "OScofoMIR::GetDescription";
    GetRMS(In, Desc);
    if (Desc.dB < m_dBTreshold) {
        return;
    }
    GetFFTDescriptions(In, Desc);
    LOGE() << "end OScofoMIR::GetDescription";
}
