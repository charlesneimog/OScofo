import librosa
import numpy as np


class Audio:
    def __init__(self, audiofile, fft_size, sr):
        self.samples, self.sr = librosa.load(audiofile, sr=sr)
        self.fft_size = fft_size
        self.len = len(self.samples)

    def get_spectrogram(self, audio_samples):
        fft = np.fft.fft(audio_samples, n=self.fft_size)
        fft = fft[: int(self.fft_size / 2)]  # Use FFT_SIZE to get half of the fft
        self.magnitude = (np.abs(fft) / self.fft_size) / self.fft_size
        return self.magnitude
