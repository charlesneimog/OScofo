import json
import os

import librosa
import matplotlib.pyplot as plt
import numpy as np

FFT_SIZE = 2048
HOP_SIZE = 2048
SIGMA = 4
SAMPLE_RATE = 48000

class State:
    def __init__(self):
        self.Valid = False
        self.Sr = 44100
        self.WindowSize = 2048
        self.Type = -1
        self.Midi = -1
        self.LiveOnset = -1
        self.TimePhasePrediction = -1
        self.Duration = -1
        self.TimePhase= -1
        self.Bpm= -1
        self.Id = -1

class Score:
    def __init__(self, scorefile):
        self.last_onset = 0
        self.last_phase = 0
        self.ScoreFile = scorefile
        self.MDP=None
        self.States = []
        # self.Parse()


    def Parse(self):
        try:
            with open(self.ScoreFile, 'r') as file:
                lines = file.readlines()
        except FileNotFoundError:
            raise FileNotFoundError("File not found: %s" % self.ScoreFile)
        
        bpm = -1
        line_count = 0
        for line in lines:
            line_count += 1
            # parse line
            if line[0] == '#' or not line.strip() or line[0] == ';':
                continue
            # parse line
            tokens = line.split()
            if tokens[0] == "NOTE":
                state = State()
                state.Type = 0 
                state.Id = len(self.States)
                self.AddNote(state, tokens, bpm, line_count);
                if state.Id == 0:
                    print("BPM: %f" % bpm)
                if not state.Valid:
                    raise ValueError("Invalid note in line %d" % line_count)
                if bpm == -1:
                    raise ValueError("No BPM in line %d" % line_count)
                self.States.append(state)
            elif tokens[0] == "BPM":
                bpm = float(tokens[1])
        return self.States

    def AddNote(self, State, tokens, bpm, line_count):
        if bpm == -1:
            raise ValueError("No BPM in line %d" % line_count)
        if len(tokens) < 3:
            raise ValueError("Invalid note on line %d" % line_count)

        # check if pitch is a number or a string
        if not tokens[1][0].isdigit():
            raise ValueError("Invalid note in line %d" % line_count)
            pass
            # note_name = tokens[1]
            # midi = name_to_midi(note_name)
            # State.Midi = midi
        else:
            State.Midi = float(tokens[1])
            if State.Midi > 127:
                State.Midi *= 0.01

        # check if there is a '/' in the string
        is_ratio = '/' in tokens[2]
        if is_ratio:
            ratio = tokens[2].replace('/', ' ')
            ratio_tokens = ratio.split()
            numerator = float(ratio_tokens[0])
            denominator = float(ratio_tokens[1])
            State.Duration = numerator / denominator
        else:
            State.Duration = float(tokens[2])

        # time phase
        t_n0 = self.last_onset
        t_n1 = t_n0 + State.Duration * 60000 / bpm
        phase0 = self.last_phase
        pulse = 60000 / bpm

        # last_phase = get_time_phase(t_n0, t_n1, phase0, pulse)
        # last_onset = t_n1

        # State.TimePhase = last_phase
        State.Bpm = bpm
        State.Valid = True

        return State


def similaritybetweenspectros(pv, qv):
    klDiv = 0
    for i in range(len(pv)):
        p = pv[i]
        q = qv[i]
        number = 1.0e-50
        if p > number and q > number:
            klDiv += p * np.log(p / q)
    klDiv = np.exp(-0.4 * klDiv)
    return klDiv


def PitchTemplate(Fund, WindowSize, Sr):
    arrLen = WindowSize 
    array = np.zeros(arrLen)
    sigma = SIGMA
    harmonics = 10
    for h in range(harmonics):
        freq = (h + 1) * Fund
        mu = round(freq / (Sr / arrLen))
        amplitude = 1 / (h + 1 ** 2)
        if (amplitude < 0.0000001):
            amplitude = 0
        # print(f"Amplitude {amplitude}")
        for i in range(arrLen):
            x = i
            gaussValue = np.exp(-0.5 * ((x - mu) / sigma) ** 2)
            amp = gaussValue * amplitude
            array[i] += amp / WindowSize
    return array



def plotTemplate():
    array = PitchTemplate(440, FFT_SIZE, SAMPLE_RATE)
    plt.plot(array, marker='o', linestyle='None')  # Adiciona os pontos com bolinhas
    plt.plot(np.arange(FFT_SIZE), array.T)
    plt.title('Curvas Gaussianas')
    plt.xlabel('Ponto')
    plt.ylabel('Amplitude')
    # plt.ylim(0, 1)  # Define os limites do eixo y para garantir que a amplitude esteja entre 0 e 1
    plt.show()
    exit()


if __name__ == "__main__":
    # global FFT_SIZE, SIGMA, SAMPLE_RATE

    # ╭──────────────────────────────────────╮
    # │            Main Variables            │
    # ╰──────────────────────────────────────╯
    FFT_SIZE = 2048
    HOP_SIZE = int(FFT_SIZE / 4)
    SIGMA = 1
    plot = False 
    # ──────────────────────────────────────

    # Piece
    n_fft = FFT_SIZE
    hop_length = HOP_SIZE
    jsonFile = os.path.join(os.path.dirname(os.path.realpath(__file__)), "test.json")
    with open(jsonFile, 'r') as json_file:
        jsonData = json.load(json_file)
    pieces = jsonData.keys()
    piecesNames = list(pieces)


    # Process
    for i in range(len(piecesNames)):
        print(f"\n===== Decoding Piece: {piecesNames[i]} =====\n")

        PieceTestDict = jsonData[piecesNames[i]]
        thisScriptFolder = os.path.dirname(os.path.realpath(__file__))
        score = os.path.join(thisScriptFolder, PieceTestDict['score'])
        myScore = Score(score)
        MDPStates = myScore.Parse()
        print("Score parsed")

        # open audio
        audio = os.path.join(thisScriptFolder, PieceTestDict['audio'])
        y, sr = librosa.load(audio, sr=None)
        if sr != SAMPLE_RATE:
            print(f"Audio Sample Rate: {sr}")
            print(f"Script Sample Rate: {SAMPLE_RATE}")
            raise ValueError("Audio Sample Rate and script sample rate must be the same")

        print("Audio loaded\n")
        EventNumber = -1
        EventOnsets = []
        EventDetected = []
        EventDict = {}

        # make numpy fft for stft
        for hop in range(0, len(y), hop_length):
            onsetMs = hop / sr * 1000
            frame = y[hop:hop + n_fft]
            frameRms = np.sqrt(np.mean(frame ** 2))

            # apply hanning 
            frame = frame * np.hanning(len(frame))


            if len(frame) < n_fft:
                # add zeros to the end of the frame
                for i in range(n_fft - len(frame)):
                    frame = np.append(frame, 0)
            fft = np.fft.fft(frame)
            magnitude = np.abs(fft) / n_fft
            mean_squared_magnitude = np.mean(magnitude)
            rms = np.sqrt(mean_squared_magnitude)
            if (rms == 0):
                rms_db = -200
            else:
                rms_db = 20 * np.log10(rms)
            magnitude = magnitude / n_fft
            if (rms_db < -50):
                continue

            s = 0
            newEvent = -1
            if (EventNumber == -1):
                for i in range(3):
                    pitchMidi = MDPStates[i].Midi
                    pitchFreq = librosa.midi_to_hz(pitchMidi)
                    pitchTemplate = PitchTemplate(pitchFreq, n_fft, sr)
                    s_hat = similaritybetweenspectros(magnitude, pitchTemplate)
                    if s_hat > s:
                        s = s_hat
                        newEvent = i

                    # print(f"EventNumber: {i} | S: {s_hat}")
            else:
                for i in range(EventNumber, EventNumber + 3):
                    if i > len(MDPStates) - 1:
                        continue
                    pitchMidi = MDPStates[i].Midi
                    pitchFreq = librosa.midi_to_hz(pitchMidi)
                    pitchTemplate = PitchTemplate(pitchFreq, n_fft, sr)
                    s_hat = similaritybetweenspectros(magnitude, pitchTemplate)
                    if s_hat > s:
                        s = s_hat
                        newEvent = i
                    # print(f"EventNumber: {i} | S: {s_hat}")



            if newEvent != EventNumber and s > 0.0001:
                EventOnsets.append(onsetMs)
                EventDetected.append(s)
                EventNumber = newEvent
                print(f"\033[32mDecoding Audio... Event {EventNumber + 1} | S: {s:.4f} | Onset: {int(onsetMs)} \033[0m", end="\r")
                # Add to EventDict
                EventDict[EventNumber] = onsetMs

        #╭──────────────────────────────────────╮
        #│             Get Results              │
        #╰──────────────────────────────────────╯
        if plot:
            plt.figure(figsize=(10, 4))
            plt.plot(np.arange(len(y)) / sr, y, color='b')
            plt.xlabel('Time (s)')
            plt.ylabel('Amplitude')
            plt.title('Audio Waveform')
            plt.grid(True)

            # Plot the detected event onsets with event number ID
            for i, onset in enumerate(EventOnsets):
                plt.axvline(x=onset / 1000, color='r', linestyle='--', linewidth=2)
                plt.text(onset / 1000, max(y), str(i), color='r', verticalalignment='bottom', horizontalalignment='center')

            plt.tight_layout()
            plt.show()

        print("\n\n")
        # compare onset of detected events with the score
        lenEvents = PieceTestDict["n"]
        totalDiference = 0
        for i in range(lenEvents):
            if i in EventDict:
                difference = EventDict[i] - PieceTestDict['events'][str(i)] * 1000
                formatted_difference = "{:+07.1f}".format(difference)
                formatted_i = str(i).zfill(2)  # Pad 'i' with leading zeros to ensure it has two digits
                onset = "{:+06.1f}".format(EventDict[i])
                scoreEvent = "{:+06.1f}".format(EventDict[i])
                totalDiference += abs(difference)
                cor = ''
                # red
                if abs(difference) < 30:
                    cor = "\033[92m"
                # yellow 
                elif abs(difference) < 60:
                    cor = "\033[93m"

                # red
                else:
                    cor = "\033[91m"

                reset = "\033[0m"
                print(f"{cor}Event {formatted_i} | Detected: {onset} | Score: {scoreEvent} | Diff: {formatted_difference}{reset}")
            else:
                red_color_code = "\033[91m"
                reset_color_code = "\033[0m"
                print(f"{red_color_code}Event {i} | Detected:  None  | Score: {PieceTestDict['events'][str(i)] * 1000}  |{reset_color_code}")

        print("\nTotal Difference: ", int(totalDiference), "\n")

