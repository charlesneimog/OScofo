#pragma once

#include <vector>

#include <fftw3.h>

#include "log.hpp"
#include "states.hpp"

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class OScofoMIR {
  public:
    OScofoMIR(float Sr, float WindowSize, float HopSize);
    ~OScofoMIR();

    void SetTreshold(double dB);
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    double TimePrediction();
    void GetDescription(const std::vector<double> &In, Description &Desc);
    void GetMidi(double Tunning);
    double GetEventTimeElapsed();
    double GetTempoInEvent();

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
    void GetFFTDescriptions(const std::vector<double> &In, Description &Desc);

    // Env
    double m_dBTreshold = -80;
    void GetRMS(const std::vector<double> &In, Description &Desc);

    // Audio
    double m_WindowSize;
    double m_BlockSize;
    double m_HopSize;
    double m_Sr;

    // Time
    double m_EventTimeElapsed = 0.0; // ms
};
