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
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    double TimePrediction();

    void GetDescription(std::vector<double> &In, Description &Desc);
    void GetMidi(double Tunning);
    double GetEventTimeElapsed();
    double GetTempoInEvent();
    double GetdB();

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
    double m_dBTreshold = -60;
    void GetRMS(std::vector<double> &In, Description &Desc);

    // Audio
    double m_FftSize;
    double m_BlockSize;
    double m_HopSize;
    double m_Sr;
    double m_dB;

    // Time
    double m_EventTimeElapsed = 0.0; // ms
};
} // namespace OScofo
