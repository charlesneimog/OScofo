import matplotlib.pyplot as plt
import librosa
import numpy as np
import os
import csv

from OScofo import OScofo

# Create an OScofo object
HOP_SIZE = 512
FFT_SIZE = 4096
SR = 48000
BIN_PLOT = 2048

os.chdir(os.path.dirname(os.path.abspath(__file__)))
plt.figure(figsize=(10, 5))

PIECE = "BWV-1013"


def open_expected_csv(root):
    csv_file = f"{root}/expected.csv"
    with open(csv_file, mode="r") as file:
        reader = csv.reader(file)
        reader_list = list(reader)

    expected_dict = {}
    for row in list(reader_list):
        expected_dict[int(row[1])] = float(row[0])
    return expected_dict


def get_spectrogram():
    y, sr = librosa.load(f"./{PIECE}/audio.wav", sr=SR)
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
if not OpenScofo.ParseScore(f"./{PIECE}/score.txt"):
    raise Exception("Error parsing score file")

# Get the pitch template for A4 (440 Hz)
state = OpenScofo.GetStates()[4]
dict_exp = open_expected_csv(f"./{PIECE}")[4]

print(state.Freqs)

exit()

spc_template = OpenScofo.GetPitchTemplate(440.0, 15, 1)
spc_audio = get_spectrogram()

# Normalize both spectra for easier comparison (optional)
spc_template /= np.max(spc_template)
spc_audio /= np.max(spc_audio)


# Plot only the first 200 bins, using both lines and points
plt.plot(
    spc_template[:BIN_PLOT],
    color="red",
    marker="o",
    label="Pitch Template (A4)",
    markersize=4,
)
plt.plot(
    spc_audio[:BIN_PLOT],
    color="blue",
    marker="x",
    label="Audio Spectrogram",
    markersize=4,
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
