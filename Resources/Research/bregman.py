import numpy as np

# Parameters
sample_rate = 44100  # Sample rate in Hz
size = 2048          # Size of the template
num_harmonics = 10   # Number of harmonics

# Frequency components
fundamental_freq = 440  # Fundamental frequency in Hz
harmonics = np.arange(2, num_harmonics + 2) * fundamental_freq  # Harmonic frequencies

# Time vector
t = np.arange(size) / sample_rate

# Generate the template
template = np.zeros(size)
for freq in np.concatenate(([fundamental_freq], harmonics)):
    template += np.sin(2 * np.pi * freq * t)

# Normalize the template
template /= np.max(np.abs(template))

# Plot the template (optional)
import matplotlib.pyplot as plt

plt.plot(t, template)
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('Frequency Domain Template')
plt.show()

