import matplotlib.pyplot as plt
import numpy as np

ARRAY_SIZE = 2048

def gaussian(x, amplitude, mu, sigma):
    # amp = amplitude * np.exp(-0.5 * ((x - center) / sigma) ** 2)
    return amplitude * np.exp(-((x - mu) ** 2) / (2 * sigma ** 2))


def main(Fund):
    array = np.zeros(2048)
    center = 30 # Center of the Gaussian curve
    sigma = 0.5  # Standard deviation
    harmonics = 10
    decay_const = 0.01
    # for (int i = 0; i < Harmonics; ++i) {
    #     double Freq = freqMultiplier * (i + 1);
    #     int mu = round(Freq * Desc->WindowSize);
    #     double amp =
    #         decayMultiplier * exp(-0.5 * pow(Sigma, 2)); // Precompute common part of the amplitude
    #     for (int j = 0; j < Desc->WindowSize; ++j) {
    #         double x = static_cast<double>(j);
    #         double gaussValue =
    #             exp(-0.5 * pow((x - mu) / Sigma, 2)); // Avoid redundant pow calculations
    #         PitchSpectralTemplate[j] += amp * gaussValue;
    #     }
    #

    for h in range(harmonics):
        h_value = (h + 1) * Fund # Evite redefinir o valor de h
        centerBin = round((h_value * 2048) / 44100)
        for i in range(ARRAY_SIZE):
            x = float(i)
            array[i] += gaussian(x, 0.8, h_value, sigma)



    # Plot the resulting curve
    plt.plot(np.arange(ARRAY_SIZE), array)
    plt.title('Gaussian Curve')
    plt.xlabel('Point')
    plt.ylabel('Amplitude')
    plt.ylim(0, 1)
    plt.show()

if __name__ == "__main__":
    main()

