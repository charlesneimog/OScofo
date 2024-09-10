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

// ╭─────────────────────────────────────╮
// │          Set|Get Functions          │
// ╰─────────────────────────────────────╯
void OScofoMIR::SetTreshold(double dB) {
    m_dBTreshold = dB;
}

// ╭─────────────────────────────────────╮
// │           FFT Descriptors           │
// ╰─────────────────────────────────────╯
void OScofoMIR::GetFFTDescriptions(const std::vector<double> &In, Description &Desc) {
    LOGE() << "OScofoMIR::GetFFTDescriptions";

    int N = In.size();
    int NHalf = N / 2;

    // Resize vectors if necessary
    if (NHalf != Desc.SpectralMag.size()) {
        m_LastPhase1.resize(NHalf);
        m_LastPhase2.resize(NHalf);
        Desc.FFTOut.resize(NHalf);
        Desc.SpectralMag.resize(NHalf);
        Desc.SpectralPhase.resize(NHalf);
        Desc.NormSpectralPower.resize(NHalf);

        std::fill(Desc.FFTOut.begin(), Desc.FFTOut.end(), std::complex<double>(0.0, 0.0));
        std::fill(Desc.SpectralMag.begin(), Desc.SpectralMag.end(), 0);
        std::fill(Desc.SpectralPhase.begin(), Desc.SpectralPhase.end(), 0);
        std::fill(Desc.NormSpectralPower.begin(), Desc.NormSpectralPower.end(), 0);
        std::fill(m_LastPhase1.begin(), m_LastPhase1.end(), 0);
        std::fill(m_LastPhase2.begin(), m_LastPhase2.end(), 0);
    }

    // Copy input data and execute FFT
    std::copy(In.begin(), In.end(), m_FFTIn);
    fftw_execute(m_FFTPlan);

    double Real, Imag;
    double Mag, Phase;
    double SpectralFlux = 0.0;

    Desc.MaxAmp = 0;
    Desc.TotalPower = 0;

    for (int i = 1; i < NHalf; i++) {
        double Real = m_FFTOut[i][0];
        double Imag = m_FFTOut[i][1];
        std::complex<double> Spectro(Real, Imag);

        // Phase e Magnitude
        Mag = (Real * Real + Imag * Imag) / N;
        Phase = atan2(Imag, Real);
        Desc.TotalPower += Mag;
        if (Mag > Desc.MaxAmp) {
            Desc.MaxAmp = Mag;
        }

        if (i > 0) {
            double magDifference = Mag - Desc.SpectralMag[i];
            SpectralFlux += std::max(0.0, magDifference);
        }

        // Salvar valores para a próxima chamada
        Desc.FFTOut[i] = Spectro;
        Desc.SpectralMag[i] = Mag; // <== Last Magnitude
        Desc.SpectralPhase[i] = Phase;
    }

    // printf("SpectralFlux: %f\n", SpectralFlux);

    m_LastPhase2 = m_LastPhase1;
    m_LastPhase1 = Desc.SpectralPhase;

    for (int i = 0; i < NHalf; i++) {
        Desc.NormSpectralPower[i] = Desc.SpectralMag[i] / Desc.MaxAmp;
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
    GetRMS(In, Desc);
    GetFFTDescriptions(In, Desc);

    if (!Desc.PassTreshold) {
        Desc.Silence = true;
    } else {
        Desc.Silence = false;
    }
}
