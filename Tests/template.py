import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as signal

# Generate 4096 samples of a sine wave
sampling_rate = 44100  # Hz
num_samples = 4096
frequency = 440  # Hz

time = np.linspace(0, num_samples / sampling_rate, num_samples)
sine_wave = np.sin(2 * np.pi * frequency * time)

# Apply STFT with a window length of 4096 samples
window_length = num_samples
overlap = 0  # No overlap for a single window
frequencies, times, spectrogram = signal.stft(
    sine_wave, sampling_rate, nperseg=window_length, noverlap=overlap
)

# Calculate amplitude spectrum
amplitude_spectrum = np.abs(spectrogram)

# Plot time-domain signal
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(time, sine_wave)
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.title("Sine Wave")

# Plot amplitude spectrum
plt.subplot(2, 1, 2)
plt.plot(
    frequencies, amplitude_spectrum[0]
)  # Only one frequency bin for a single window
plt.xlabel("Frequency (Hz)")
plt.ylabel("Amplitude")
plt.title("Amplitude Spectrum")

plt.tight_layout()
plt.show()
