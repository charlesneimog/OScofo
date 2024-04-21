import os

import librosa
import matplotlib.pyplot as plt
import numpy as np

# export QT_QPA_PLATFORM=wayland
os.environ['QT_QPA_PLATFORM'] = 'wayland'


# Load audio file
audio_file = './Resources/Fl-ord-A4-mf.aif'
y, sr = librosa.load(audio_file, sr=None)

# Pre-emphasis
y = np.append(y[0], y[1:] - 0.97 * y[:-1])

# Compute Mel spectrogram
n_fft = 2048
hop_length = 512
n_mels = 40

D = np.abs(librosa.stft(y))**2
S = librosa.feature.mfcc(S=librosa.power_to_db(D), n_mfcc=n_mels)

# Display MFCCs
librosa.display.specshow(S, x_axis='time')
plt.colorbar()
plt.title('MFCC')
plt.show()




