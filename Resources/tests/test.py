import os
import librosa
from matplotlib import pyplot as plt


from OScofo import OScofo


this_dir = os.path.dirname(os.path.abspath(__file__))
all_music = os.listdir(this_dir)

for piece_file in all_music:
    if piece_file.endswith('.mp3'):
        event = None  
        FFT_SIZE = 4096
        HOP_SIZE = 1024 
        y, sr = librosa.load(piece_file, sr=None)
        score_file = piece_file.replace('.mp3', '.txt')
        follower = OScofo(sr, FFT_SIZE, HOP_SIZE)
        ok = follower.ParseScore(score_file)
        if not ok:
            print('Error parsing score file')
            continue

        detected_events = {}
        for i in range(0, len(y) - FFT_SIZE, HOP_SIZE):  
            frame = y[i:i + FFT_SIZE]  
            ok = follower.ProcessBlock(frame)  
            if follower.GetEventIndex() != event:
                event = follower.GetEventIndex()
                detected_events[event] = i / sr

        
        print('Detected events:', detected_events)
        plt.figure(figsize=(15, 5))
        plt.plot(y)

        for event, time in detected_events.items():
            plt.axvline(time * sr, color='r', linestyle='--')

        plt.show()






