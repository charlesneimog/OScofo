import matplotlib.pyplot as plt
import numpy as np
from scipy.fft import fft, fftfreq
from scipy.optimize import curve_fit
from scipy.signal import find_peaks
from scipy.stats import norm

# Generate sample audio signal (you would replace this with your own audio data)
fs = 1000  # Sampling frequency (Hz)
t = np.arange(0, 1, 1/fs)  # Time array
f1 = 50  # Frequency of first peak (Hz)
f2 = 150  # Frequency of second peak (Hz)
audio_signal = np.sin(2 * np.pi * f1 * t) + 0.5 * np.sin(2 * np.pi * f2 * t)

# Perform FFT to get frequency spectrum
n = len(audio_signal)
frequencies = fftfreq(n, 1/fs)
spectrum = fft(audio_signal)

# Identify peaks
peaks, _ = find_peaks(np.abs(spectrum), height=100)  # Adjust height threshold as needed

# Fit normal distributions to peaks
def normal_function(x, mean, std_dev, amplitude):
    return amplitude * norm.pdf(x, mean, std_dev)

peak_params = []
for peak_index in peaks:
    peak_frequency = frequencies[peak_index]
    peak_magnitude = np.abs(spectrum[peak_index])
    
    # Estimate initial parameters for curve fitting
    initial_mean = peak_frequency
    initial_std_dev = 10  # Adjust as needed
    initial_amplitude = peak_magnitude
    
    # Fit normal distribution
    try:
        popt, _ = curve_fit(normal_function, frequencies, np.abs(spectrum), 
                             p0=[initial_mean, initial_std_dev, initial_amplitude])
        peak_params.append(popt)
    except RuntimeError:
        # If curve fitting fails, skip this peak
        continue

# Plot original spectrum
plt.figure(figsize=(10, 6))
plt.plot(frequencies, np.abs(spectrum), label='Original Spectrum')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Magnitude')
plt.title('Frequency Spectrum')
plt.legend()

# Plot fitted normal distributions
for params in peak_params:
    mean, std_dev, amplitude = params
    plt.plot(frequencies, normal_function(frequencies, *params), '--', label=f'Peak Fit (μ={mean}, σ={std_dev})')

plt.legend()
plt.show()

