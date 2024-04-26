import matplotlib.pyplot as plt
import numpy as np

# Define fundamental frequency and number of harmonics
fundamental_frequency = 440  # Hz
num_harmonics = 10

# Calculate harmonic frequencies
harmonic_frequencies = [fundamental_frequency * (i + 1) for i in range(num_harmonics)]

# Create frequency vector
frequency_vector = np.linspace(0, max(harmonic_frequencies), 1000)

# Compute amplitudes (example: decreasing amplitudes for harmonics)
fundamental_amplitude = 1.0
harmonic_amplitudes = [fundamental_amplitude / (i + 1) for i in range(num_harmonics)]

# Construct frequency distribution
frequency_distribution = np.zeros_like(frequency_vector)
for i, freq in enumerate(harmonic_frequencies):
    frequency_distribution += harmonic_amplitudes[i] * np.sin(2 * np.pi * freq * frequency_vector)

# Plot frequency distribution
plt.plot(frequency_vector, frequency_distribution)
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude')
plt.title('Frequency Distribution of 440 Hz with 10 Harmonics')
plt.grid(True)
plt.show()

