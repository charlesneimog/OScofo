import os
from pydub import AudioSegment
import numpy as np

from OScofo import OScofo


this_dir = os.path.dirname(os.path.abspath(__file__))
all_music = os.listdir(this_dir)

for piece_file in all_music:
    if piece_file.endswith('.mp3'):
        event = 0
        print('Processing:', piece_file)
        FFT_SIZE = 2048
        HOP_SIZE = 512 
        audio = AudioSegment.from_mp3(piece_file)
        audio_mono = audio.set_channels(1)
        samples = np.array(audio_mono.get_array_of_samples(), dtype=np.float64)
        samples /= 32768.0  
        samples *= 4
        score_file = piece_file.replace('.mp3', '.txt')
        follower = OScofo(48000, FFT_SIZE, HOP_SIZE)
        ok = follower.ParseScore(score_file)
        if not ok:
            print('Error parsing score file')
            continue

        event = None  
        for i in range(0, len(samples) - FFT_SIZE, HOP_SIZE):  
            frame = samples[i:i + FFT_SIZE]  
            ok = follower.ProcessBlock(frame)  
            if follower.GetEventIndex() != event:
                event = follower.GetEventIndex()
                print('Event:', event)
