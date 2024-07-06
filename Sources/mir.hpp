#pragma once

#include <vector>

#include <fftw3.h>

#include "log.hpp"

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

// ╭─────────────────────────────────────╮
// │     Music Information Retrieval     │
// ╰─────────────────────────────────────╯
class OScofoMIR {
  public:
    OScofoMIR(float Sr, float WindowSize, float HopSize);
    static double Mtof(double note, double tunning);
    static double Ftom(double freq, double tunning);
    static double Freq2Bin(double freq, double n, double Sr);

    void SetTreshold(double dB);
    struct m_Description {
        double WindowSize;
        double Sr;
        double Freq;
        double Midi;
        double Quality;
        double dB;
        std::vector<double> SpectralPower;
        std::vector<double> NormSpectralPower;
        double TotalPower;
        double MaxAmp;
        double SpectralFlatness;

        // Pitch
        // std::vector<double> SpectralChroma;
        // double HigherChroma;
    };

    void GetDescription(std::vector<double> in, m_Description *Desc, double Tunning);
    void GetMidi(double tunning);

    // Time
    double TimePrediction();
    void ResetElapsedTime();
    void UpdateTempoInEvent();
    double GetEventTimeElapsed();
    double GetTempoInEvent();

  private:
    // Helpers
    std::vector<double> m_WindowingFunc;
    void GetHanning(int WindowSize);

    // FFT
    fftw_complex *m_FFTOut;
    fftw_plan m_FFTPlan;
    void GetFFTDescriptions(std::vector<double> in, m_Description *Desc);

    // Env
    double m_dBTreshold = -80;
    void GetRMS(std::vector<double> in, m_Description *Desc);

    // Audio
    double m_WindowSize;
    double m_BlockSize;
    double m_HopSize;
    double m_Sr;

    // Time
    double m_EventTimeElapsed = 0.0; // ms
};
