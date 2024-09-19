import matplotlib.pyplot as plt
import librosa
import numpy as np
import os

from OScofo import OScofo  # Assuming OScofo is your class

# Create an OScofo object
HOP_SIZE = 512
FFT_SIZE = 4096
SR = 48000
BIN_PLOT = 2048

# Ensure THISFILE is correctly defined for your environment
THISFILE = os.path.dirname(os.path.abspath(__file__))

# Plotting the result
plt.figure(figsize=(10, 5))


def GetSpectrogram():
    y, sr = librosa.load(os.path.join(THISFILE, "flute.wav"), sr=SR)
    signalSize = round(len(y) / 2)
    samples = (
        y[signalSize : signalSize + FFT_SIZE]
        if signalSize + FFT_SIZE < len(y)
        else y[signalSize:]
    )
    fft = np.fft.fft(samples, n=FFT_SIZE)
    fft = fft[: FFT_SIZE // 2]  # Use half of the fft for plotting
    magnitude = np.abs(fft) / FFT_SIZE
    return magnitude


# Initialize OScofo
OpenScofo = OScofo(SR, FFT_SIZE, HOP_SIZE)

# Get the pitch template for A4 (440 Hz)
spc = OpenScofo.GetPitchTemplate(440.0, 15, 1)
# Get the spectrogram from the audio file
audio = GetSpectrogram()

# Normalize both spectra for easier comparison (optional)
spc /= np.max(spc)
audio /= np.max(audio)

# Plot only the first 200 bins, using both lines and points
plt.plot(
    spc[:BIN_PLOT], color="red", marker="o", label="Pitch Template (A4)", markersize=4
)
plt.plot(
    audio[:BIN_PLOT], color="blue", marker="x", label="Audio Spectrogram", markersize=4
)

# Set plot details
plt.title("Overlapped Spectrum (First 200 Bins): Single Note A4 (440 Hz)")
plt.xlabel("Frequency (bins)")
plt.ylabel("Amplitude")
plt.xlim(0, BIN_PLOT)  # Limit x-axis to first 200 bins
plt.gca().set_yticklabels([])  # Hide y-tick labels
plt.legend()

plt.tight_layout()
plt.show()
