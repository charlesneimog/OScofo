import librosa
import numpy as np
import music21
import math
import os

from audio import Audio
from score import Score
from tempo import TimeInference
from helpers import Helpers
from markov import MarkovType, EventType

# set current folder as working directory
os.chdir("./Tests")


AUDIO_FILE = "Test0.wav"
SCORE_FILE = "Test0.txt"
SR_AUDIO = 48000
HOP_SIZE = 1024
FFT_SIZE = 4096
BLOCK_DUR = 1 / SR_AUDIO * HOP_SIZE
DB_FOR_SILENCE = -50

print(f"Score: {SCORE_FILE} | Audio: {AUDIO_FILE}")
print(f"SR: {SR_AUDIO} | FFT: {FFT_SIZE} | HOP_SIZE: {HOP_SIZE}")
print(f"Block Dur: {BLOCK_DUR:4f} seconds")

audio = Audio(AUDIO_FILE, FFT_SIZE, SR_AUDIO)
score = Score(SCORE_FILE)
time = TimeInference(score.states)
obs = AudioObservations()

START_POINT = 0

CURRENT_TIME = 0
for i in range(0, audio.len - FFT_SIZE + 1, HOP_SIZE):
    block = audio.samples[i : i + FFT_SIZE]
    CURRENT_TIME += BLOCK_DUR
    if len(block) > FFT_SIZE:
        break
    rms = np.sqrt(np.mean(block**2))
    dB = 20 * math.log10(rms)
    if dB < DB_FOR_SILENCE:
        continue
    if START_POINT == 0:
        CURRENT_TIME = 0
        START_POINT = i

    best_prob = -np.inf
    # get magnitude of the block
    fft_mag = audio.get_spectrogram(block)
    for state in score.states:
        if state.markov_type == MarkovType.SEMIMARKOV:
            print(state)
        elif state.markov_type == MarkovType.MARKOV:
            print(state)


# Helpers(audio.samples, START_POINT).show_start_point()
