#include "follower.hpp"

#include <algorithm>
#include <cmath>
#include <limits.h>

// ╭─────────────────────────────────────╮
// │           Init Functions            │
// ╰─────────────────────────────────────╯

FollowerMIR::FollowerMIR(int hopSize, int windowSize, int sr)
    : HopSize(hopSize), WindowSize(windowSize), Sr(sr) {
    // CreateYin(0.6, -60);
}

// ╭─────────────────────────────────────╮
// │            Yin Algorithm            │
// ╰─────────────────────────────────────╯
/*
This code is from aubio Library. We copy it here just because we don't need to do FFT twice.
*/
bool FollowerMIR::CreateYin(float tolerance, float silence) {
    // fvec_t *out = new_fvec(1);
    // YinInstance = new_aubio_pitch("yinfast", WindowSize, WindowSize, Sr);
    // if (YinInstance == nullptr) {
    //     return false;
    // }
    // aubio_pitch_set_tolerance(YinInstance, tolerance);
    // aubio_pitch_set_silence(YinInstance, silence);
    // aubio_pitch_set_unit(YinInstance, "Hz");
    return true;
}

// ─────────────────────────────────────
void FollowerMIR::GetYin(std::vector<float> *in, Description *Desc) {
    //

    // if (YinInstance == nullptr) {
    //     Desc->Freq = 0;
    //     Desc->Quality = 0;
    //     return;
    // }
    // fvec_t *pitch = new_fvec(1);
    // fvec_t AubioIn;
    // AubioIn.length = in->size();
    // AubioIn.data = new smpl_t[AubioIn.length];
    // std::copy(in->begin(), in->end(), AubioIn.data);
    // smpl_t freq, quality, envelope;
    // aubio_pitch_do(YinInstance, (const fvec_t *)&AubioIn, pitch);
    // freq = fvec_get_sample(pitch, 0);
    // quality = aubio_pitch_get_confidence(YinInstance);
    // Desc->Freq = freq;
    // Desc->Midi = Mtof(freq, Desc->Tunning);
    // Desc->Quality = quality;

    return;
}

// ─────────────────────────────────────

// void aubio_pitchyinfast_do(aubio_pitchyinfast_t *o, const fvec_t *input, fvec_t *out) {
//     const smpl_t tol = o->tol;
//     fvec_t *yin = o->yin;
//     const uint_t length = yin->length;
//     uint_t B = o->tmpdata->length;
//     uint_t W = o->yin->length; // B / 2
//     fvec_t tmp_slice, kernel_ptr;
//     uint_t tau;
//     sint_t period;
//     smpl_t tmp2 = 0.;
//
//     // compute r_t(0) + r_t+tau(0)
//     {
//         fvec_t *squares = o->tmpdata;
//         fvec_weighted_copy(input, input, squares);
// #if 0
//     for (tau = 0; tau < W; tau++) {
//       tmp_slice.data = squares->data + tau;
//       tmp_slice.length = W;
//       o->sqdiff->data[tau] = fvec_sum(&tmp_slice);
//     }
// #else
//         tmp_slice.data = squares->data;
//         tmp_slice.length = W;
//         o->sqdiff->data[0] = fvec_sum(&tmp_slice);
//         for (tau = 1; tau < W; tau++) {
//             o->sqdiff->data[tau] = o->sqdiff->data[tau - 1];
//             o->sqdiff->data[tau] -= squares->data[tau - 1];
//             o->sqdiff->data[tau] += squares->data[W + tau - 1];
//         }
// #endif
//         fvec_add(o->sqdiff, o->sqdiff->data[0]);
//     }
//     // compute r_t(tau) = -2.*ifft(fft(samples)*fft(samples[W-1::-1]))
//     {
//         fvec_t *compmul = o->tmpdata;
//         fvec_t *rt_of_tau = o->samples_fft;
//         aubio_fft_do_complex(o->fft, input, o->samples_fft);
//         // build kernel, take a copy of first half of samples
//         tmp_slice.data = input->data;
//         tmp_slice.length = W;
//         kernel_ptr.data = o->kernel->data + 1;
//         kernel_ptr.length = W;
//         fvec_copy(&tmp_slice, &kernel_ptr);
//         // reverse them
//         fvec_rev(&kernel_ptr);
//         // compute fft(kernel)
//         aubio_fft_do_complex(o->fft, o->kernel, o->kernel_fft);
//         // compute complex product
//         compmul->data[0] = o->kernel_fft->data[0] * o->samples_fft->data[0];
//         for (tau = 1; tau < W; tau++) {
//             compmul->data[tau] = o->kernel_fft->data[tau] * o->samples_fft->data[tau];
//             compmul->data[tau] -= o->kernel_fft->data[B - tau] * o->samples_fft->data[B - tau];
//         }
//         compmul->data[W] = o->kernel_fft->data[W] * o->samples_fft->data[W];
//         for (tau = 1; tau < W; tau++) {
//             compmul->data[B - tau] = o->kernel_fft->data[B - tau] * o->samples_fft->data[tau];
//             compmul->data[B - tau] += o->kernel_fft->data[tau] * o->samples_fft->data[B - tau];
//         }
//         // compute inverse fft
//         aubio_fft_rdo_complex(o->fft, compmul, rt_of_tau);
//         // compute square difference r_t(tau) = sqdiff - 2 * r_t_tau[W-1:-1]
//         for (tau = 0; tau < W; tau++) {
//             yin->data[tau] = o->sqdiff->data[tau] - 2. * rt_of_tau->data[tau + W];
//         }
//     }
//
//     // now build yin and look for first minimum
//     fvec_zeros(out);
//     yin->data[0] = 1.;
//     for (tau = 1; tau < length; tau++) {
//         tmp2 += yin->data[tau];
//         if (tmp2 != 0) {
//             yin->data[tau] *= tau / tmp2;
//         } else {
//             yin->data[tau] = 1.;
//         }
//         period = tau - 3;
//         if (tau > 4 && (yin->data[period] < tol) && (yin->data[period] < yin->data[period + 1]))
//         {
//             o->peak_pos = (uint_t)period;
//             out->data[0] = fvec_quadratic_peak_pos(yin, o->peak_pos);
//             return;
//         }
//     }
//     // use global minimum
//     o->peak_pos = (uint_t)fvec_min_elem(yin);
//     out->data[0] = fvec_quadratic_peak_pos(yin, o->peak_pos);
// }
// ─────────────────────────────────────
void FollowerMIR::AubioYin(std::vector<float> *in, Description *Desc) {
    const float tol = 0.6;
    const int length = Desc->WindowSize;
    int B = Desc->WindowSize;
    int W = Desc->WindowSize / 2;
    std::vector<float> yin(Desc->WindowSize, 0);

    std::vector<float> RealFFTPart = Desc->SpectralReal;
    std::vector<float> ImagFFTPart = Desc->SpectralImag;
    std::vector<float> PowerFFT = Desc->SpectralPower;

    // Rewrite aubio_pitchyinfast_do without redoing FFT

    // compute r_t(0) + r_t+tau(0)
    {
        std::vector<float> squares(Desc->WindowSize, 0);
        for (int i = 0; i < Desc->WindowSize; i++) {
            squares[i] = in->at(i) * in->at(i);
        }
        std::vector<float> sqdiff(Desc->WindowSize, 0);
        sqdiff[0] = squares[0];
        for (int i = 1; i < Desc->WindowSize; i++) {
            sqdiff[i] = sqdiff[i - 1] + squares[i];
        }
    }
    // compute r_t(tau) = -2.*ifft(fft(samples)*fft(samples[W-1::-1]))
    {
        std::vector<float> compmul(Desc->WindowSize, 0);
        std::vector<float> rt_of_tau(Desc->WindowSize, 0);
        // build kernel, take a copy of first half of samples
        std::vector<float> kernel(Desc->WindowSize, 0);
        std::copy(in->begin(), in->begin() + W, kernel.begin());
        // reverse them
        std::reverse(kernel.begin(), kernel.end());
        // compute fft(kernel)
        // compute complex product
        compmul[0] = RealFFTPart[0] * RealFFTPart[0] + ImagFFTPart[0] * ImagFFTPart[0];
        for (int i = 1; i < W; i++) {
            compmul[i] = RealFFTPart[i] * RealFFTPart[i] + ImagFFTPart[i] * ImagFFTPart[i];
            compmul[i] -=
                RealFFTPart[B - i] * RealFFTPart[B - i] + ImagFFTPart[B - i] * ImagFFTPart[B - i];
        }
        compmul[W] = RealFFTPart[W] * RealFFTPart[W] + ImagFFTPart[W] * ImagFFTPart[W];
        for (int i = 1; i < W; i++) {
            compmul[B - i] =
                RealFFTPart[B - i] * RealFFTPart[i] + ImagFFTPart[B - i] * ImagFFTPart[i];
            compmul[B - i] +=
                RealFFTPart[i] * RealFFTPart[B - i] + ImagFFTPart[i] * ImagFFTPart[B - i];
        }
        // compute inverse fft
        // compute square difference r_t(tau) = sqdiff - 2 * r_t_tau[W-1:-1]
        for (int i = 0; i < W; i++) {
            rt_of_tau[i] = PowerFFT[i] - 2 * compmul[i + W];
        }
    }

    // now build yin and look for first minimum
    std::vector<float> out(1, 0);
    float tmp2 = 0;
    for (int i = 1; i < length; i++) {
        tmp2 += yin[i];
        if (tmp2 != 0) {
            yin[i] *= i / tmp2;
        } else {
            yin[i] = 1;
        }
        int period = i - 3;
        if (i > 4 && (yin[period] < tol) && (yin[period] < yin[period + 1])) {
            Desc->Freq = i;
            Desc->Quality = yin[i];
            return;
        }
    }
    // use global minimum
    Desc->Freq = std::min_element(yin.begin(), yin.end()) - yin.begin();
    post("freq is %f", Desc->Freq);
}

// ╭─────────────────────────────────────╮
// │          MFCC Observation           │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetMFCC(std::vector<float> *in, Description *Desc) {
    // if (YinInstance == nullptr) {
    //     Desc->Freq = 0;
    //     Desc->Quality = 0;
    //     return;
    // }
}

// ╭─────────────────────────────────────╮
// │          Pitch Observation          │
// ╰─────────────────────────────────────╯
void FollowerMIR::GetFFT(std::vector<float> *in, Description *Desc) {
    int n = in->size();
    Desc->SpectralReal.clear();
    Desc->SpectralImag.clear();

    t_sample *real_in = new t_sample[n];
    for (int i = 0; i < n; i++) {
        real_in[i] = (*in)[i]; // TODO: add windowing function here
    }
    t_sample *imag_in = new t_sample[n];
    mayer_fft(WindowSize, real_in, imag_in);
    for (int i = 0; i < n / 2; i++) {
        Desc->SpectralImag.push_back(imag_in[i]);
        Desc->SpectralReal.push_back(real_in[i]);
    }

    // Power
    for (int i = 0; i < n / 2; i++) {
        Desc->SpectralPower.push_back(real_in[i] * real_in[i] + imag_in[i] * imag_in[i]);
    }
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
    float lowFreq = 80;         // TODO: Define LowFrequncy
    float higherFreq = 8000;    // TODO: Define HigherFrequncy
    float pitchTolerance = 0.1; // TODO: Define PitchFrequncy
    int ChromaClasses = 12;     // TODO: Define in Object also

    std::vector<float> chromaSums(ChromaClasses, 0.0);
    std::vector<float> binRanges;

    for (int i = 0; i < ChromaClasses; i++) {
        unsigned cardinality = 0;
        float thisPitch = 23;

        // Initialize binRanges
        binRanges.clear();
        binRanges.resize(64, ULONG_MAX);

        while (Mtof(thisPitch, Desc->Tunning) < lowFreq)
            thisPitch += 12.0;

        int j = 0;
        while (mtof(thisPitch) < higherFreq) {
            float thisFreq = Mtof(thisPitch - pitchTolerance, Desc->Tunning);
            binRanges[j] = thisFreq * Desc->WindowSize / Desc->Sr;
            binRanges[j + 1] = thisFreq * Desc->WindowSize / Desc->Sr;
            cardinality++;
            thisPitch += 12.0;
            j += 2;
        }

        j = 0;
        while (binRanges[j] != ULONG_MAX) {
            int k, numBins;

            // just in case j+1 is somehow ULONG_MAX, abort
            if (binRanges[j + 1] == ULONG_MAX)
                break;

            numBins = binRanges[j + 1] - binRanges[j] + 1;

            // sum all the energy in the binRange for thisPitch
            for (k = 0; k < numBins; k++) {
                float thisEnergy = (*in)[binRanges[j] + k];

                if (thisEnergy >= 0.1)
                    chromaSums[i] += thisEnergy;
            }

            j += 2;
            chromaSums[i] /= cardinality;
        }
    }
    // Normalize chromaSums
    float maxEnergySum = getMaxElement(chromaSums);

    if (maxEnergySum > 0.0) {
        for (int i = 0; i < ChromaClasses; i++) {
            chromaSums[i] /= maxEnergySum;
            printf("Chroma %d: %f\n", i, chromaSums[i]);
        }
    }
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
    // Implementação inline da cópia ponderada
    for (int i = 0; i < in->size(); i++) {
        in->at(i) = in->at(i) * 0.54 - 0.46 * std::cos(2 * M_PI * i / in->size());
    }

    if (Desc->dB < -40) {
        return;
    }
    // GetYin(in, Desc);
    GetFFT(in, Desc);
    AubioYin(in, Desc);
    // GetChroma(in, Desc);
}
