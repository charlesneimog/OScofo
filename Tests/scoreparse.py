import os
import librosa


from OScofo import OScofo

os.chdir(os.path.dirname(os.path.abspath(__file__)))


def ordinary_test(test_root, sr, fft_size, hop_size):
    score_file = f"{test_root}/score.txt"
    OpenScofo = OScofo(sr, fft_size, hop_size)
    if OpenScofo.ParseScore(score_file):
        state = OpenScofo.GetStates()[0]




ordinary_test("./", 48000, 4096, 512)
