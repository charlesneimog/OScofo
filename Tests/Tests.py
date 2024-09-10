import os

import numpy as np
import librosa

from OScofo import OScofo

root = os.path.dirname(os.path.abspath(__file__))


AUDIO_FILE = root + "/Test1.wav"
SCORE_FILE = root + "/Test1.txt"
HOP_SIZE = 1024
FFT_SIZE = 4096
SR = 48000


# Initialize OScofo
OScofo = OScofo(SR, FFT_SIZE, HOP_SIZE)
OScofo.ParseScore(SCORE_FILE)

samples, sr = librosa.load(AUDIO_FILE, sr=SR)

# Process Audio
event = 0
onset = 0
block = 0

print("Max samples: ", np.max(samples))
print("Min samples: ", np.min(samples))


for i in range(0, len(samples), HOP_SIZE):
    audioBlock = samples[i : i + FFT_SIZE]

    if len(audioBlock) != FFT_SIZE:
        print("End of audio")
        break
    if OScofo.ProcessBlock(audioBlock):
        currentEvent = OScofo.GetEventIndex()
        currentBpm = OScofo.GetLiveBPM()

        if currentEvent != event:
            event = currentEvent
            print("\033[91mEvent:", event, "in", onset, f"Bpm: {currentBpm}\033[0m")
        onset += 1 / (SR / HOP_SIZE)
    else:
        raise Exception("Error in processing block")
    block += 1
    # if block > 1000:
    #     print("Max blocks reached")
    #     break
    # input("Press Enter to continue...")
    # print(f"Block time was: {onset}")
    # print("\n")
