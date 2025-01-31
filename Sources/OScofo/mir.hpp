#pragma once

#include <vector>

#include <fftw3.h>

#include "log.hpp"
#include "states.hpp"
namespace OScofo {

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class MIR {
  public:
    MIR(float Sr, float WindowSize, float HopSize);
    ~MIR();

    void SetdBTreshold(double dB);
    void GetDescription(std::vector<double> &In, Description &Desc);
    void GetLoudness(std::vector<double> &In, Description &Desc);
    double GetdB();

    // Error handling
    bool HasErrors();
    std::vector<std::string> GetErrorMessage();
    void SetError(const std::string &message);
    void ClearError();

  private:
    // Helpers
    std::vector<double> m_WindowingFunc;
    double Mtof(double Note, double Tunning);
    double Ftom(double Freq, double Tunning);
    double Freq2Bin(double freq, double n, double Sr);

    // FFT
    double *m_FFTIn;
    fftw_complex *m_FFTOut;
    fftw_plan m_FFTPlan;
    void GetFFTDescriptions(std::vector<double> &In, Description &Desc);

    // Env
    double m_dBTreshold = -50;
    void GetRMS(std::vector<double> &In, Description &Desc);
    void GetSpectralFlux(Description &Desc);

    // Audio
    float m_FftSize;
    float m_BlockSize;
    float m_HopSize;
    float m_Sr;
    double m_dB;
    std::vector<double> m_PreviousSpectralPower;

    // Time
    double m_EventTimeElapsed = 0.0; // ms

    // Errors
    bool m_HasErrors = false;
    std::vector<std::string> m_Errors;
};
} // namespace OScofo
