#include "follower.hpp"

#include <cmath>
#include <vector>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(int hopSize, int windowSize, int sr)
    : HopSize(hopSize), WindowSize(windowSize), Sr(sr) {
    // CreateYin(0.6, -60);
    const kfr::dft_plan<kfr::fbase> dft(WindowSize);
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetFFT(std::vector<float> *in, Description *Desc) {
    int n = in->size();
    Desc->SpectralReal.clear();
    Desc->SpectralImag.clear();
    Desc->SpectralPower.clear();

    // ─────────────────────────────────────
    t_sample *real_in = new t_sample[n];
    for (int i = 0; i < n; i++) {
        real_in[i] = (*in)[i]; // TODO: add windowing function here
    }

    // ─────────────────────────────────────
    // FFT
    t_sample *imag_in = new t_sample[n];
    mayer_fft(WindowSize, real_in, imag_in); // not fast
    for (int i = 0; i < n; i++) {
        Desc->SpectralImag.push_back(imag_in[i]);
        Desc->SpectralReal.push_back(real_in[i]);
    }

    // ─────────────────────────────────────
    // Power
    int num_bins = n / 2;
    for (int i = 0; i < n; i++) {
        Desc->SpectralPower.push_back((real_in[i] * real_in[i] + imag_in[i] * imag_in[i]) / n);
        // normalized power
    }

    // ─────────────────────────────────────
    // Free Memory
    delete[] real_in;
    delete[] imag_in;
}

// ─────────────────────────────────────
float getMaxElement(const std::vector<float> &vec) {
    if (vec.empty()) {
        return 0.0f; // or any other appropriate default value
    }

    float maxVal = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] > maxVal) {
            maxVal = vec[i];
        }
    }

    return maxVal;
}

// ─────────────────────────────────────
void FollowerMIR::GetChroma(std::vector<float> *in, Description *Desc) {
    int ChromaClasses = 12;

    Desc->SpectralChroma.clear();
    Desc->SpectralChroma.resize(ChromaClasses, 0);
    Desc->HigherChroma = 0;

    float MaximaMidiDiff = 0.25;
    float Tolerance = float(12) / float(ChromaClasses) * MaximaMidiDiff;
    std::vector<float> Chroma(ChromaClasses, 0);
    float HigherChroma = 0;
    for (int i = 0; i < ChromaClasses; i++) {
        float Interval = 12.0 / ChromaClasses;
        float Fund = 21 + i; // 21 == A0
        float Energy = 0.0f;
        float IndexChroma = fmod(Fund, 12);
        for (int j = 1; j < 12; j++) { // A2-A10
            float HzFund = Mtof(Fund + (j * 12), Desc->Tunning);
            float BinFund = Freq2Bin(HzFund, Desc->WindowSize, Desc->Sr);
            if (BinFund > (Desc->WindowSize / 2) - 2 || BinFund < 1) {
                break;
            }
            float BinAmpA = Desc->SpectralPower[BinFund - 1];
            float BinAmpB = Desc->SpectralPower[BinFund];
            float BinAmpC = Desc->SpectralPower[BinFund + 1];
            float p = 0.5 * (BinAmpA - BinAmpC) / (BinAmpA - 2 * BinAmpB + BinAmpC);
            float DescFreq = Desc->Sr / Desc->WindowSize * (BinFund + p);
            float DescMidi = Ftom(DescFreq, Desc->Tunning);
            float Diff = fabs(DescMidi - (Fund + (j * 12)));
            Energy += Desc->SpectralPower[BinFund];
        }

        Desc->SpectralChroma[IndexChroma] = Energy;
        if (Energy > HigherChroma) {
            Desc->HigherChroma = IndexChroma;
            HigherChroma = Energy;
        }
    }
    // post("higherChroma %f", Desc->HigherChroma);
}

// ╭─────────────────────────────────────╮
// │                 RMS                 │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetRMS(std::vector<float> *in, Description *Desc) {
    double sumOfSquares = 0.0;
    for (float sample : *in) {
        sumOfSquares += sample * sample;
    }
    double rms = std::sqrt(sumOfSquares / in->size());
    float reference = 1.0;
    float dB = 20.0 * std::log10(rms / reference);
    if (std::isinf(dB)) {
        dB = -100;
    }
    Desc->dB = dB;
}

// ╭─────────────────────────────────────╮
// │      Antescofo Time Prediction      │
// ╰─────────────────────────────────────╯

// ╭─────────────────────────────────────╮
// │                Time                 │
// ╰─────────────────────────────────────╯
/*
 * LARGE and JONES. The Dynamics of Attending: How People Track Time-Varying Events. 1999.

*/
float FollowerMIR::TimePrediction() {

    return 0;
}

void FollowerMIR::ResetElapsedTime() {
    EventTimeElapsed = 0;
}

void FollowerMIR::UpdateTempoInEvent() {
    EventTimeElapsed += 1000 / Sr * HopSize;
}

float FollowerMIR::GetEventTimeElapsed() {
    return EventTimeElapsed;
};

// ─────────────────────────────────────
float BesselFunction(float x) {
    int n = 1000;        // Number of intervals for numerical integration
    double h = M_PI / n; // Width of each interval
    double sum = 0.0;
    // Use the trapezoidal rule for numerical integration
    for (int i = 0; i <= n; ++i) {
        double theta = i * h;
        double term = exp(x * cos(theta));
        if (i == 0 || i == n) {
            sum += 0.5 * term;
        } else {
            sum += term;
        }
    }

    return sum * h / M_PI;
}

// ╭─────────────────────────────────────╮
// │            Main Function            │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetDescription(std::vector<float> *in, Description *Desc, float Tunning) {
    Desc->WindowSize = WindowSize;
    Desc->Sr = Sr;
    Desc->Tunning = Tunning;
    GetRMS(in, Desc);
    if (Desc->dB < -40) {
        return;
    }
    // apply hanning to in
    for (int i = 0; i < Desc->WindowSize; i++) {
        (*in)[i] *= 0.5 * (1 - cos(2 * M_PI * i / (Desc->WindowSize - 1)));
    }

    GetFFT(in, Desc);
    GetChroma(in, Desc);
}
