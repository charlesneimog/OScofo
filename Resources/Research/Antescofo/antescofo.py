import math
import os
import sys

import librosa
import matplotlib.pyplot as plt
import numpy as np

PLOTKL = False
# PLOTKL =True 

class States:
    def __init__(self):
        self.default()


    def default(self):
        self.Onset = 0.0
        self.Duration = 0.0
        self.PhiN = 0
        self.Bpm = 0
        self.Midi = 70

class Scofo:
    def __init__(self, path, audio):
        self.thisfile = os.path.abspath(__file__)
        self.audio = os.path.join(os.path.dirname(self.thisfile), audio)
        self.path = os.path.join(os.path.dirname(self.thisfile), path)
        self.BestEvent = -1
        self.Bpm = 0
        self.m_Z = 0.5
        self.windowsize = 4096
        self.hopsize = 1024
        self.harmonics = 10
        self.gausian_sigma = 0.3
        self.States = []
        self.data = []
        self.bpm = 0
        self.parse()

    def parse(self):
        with open(self.path, "r") as f:
            self.data = f.readlines()

        event = 0
        lastonset = 0
        for line in self.data:
            line = line.replace("\n", "")
            tokens = line.split(" ")
            if tokens[0] == "NOTE":
                # State.OnsetExpected = LastOnset + State.Duration * (60 / BPM); // in Seconds
                State = States()
                State.Bpm = self.bpm
                duration = float(tokens[2])
                if event == 0:
                    onset = 0
                else:
                    onset = lastonset + (duration * (60 / self.bpm))
                    State.Onset = onset
                    State.Duration = duration
                    lastonset = onset
                event += 1
                State.Midi = int(tokens[1])
                self.States.append(State)
            elif tokens[0] == "BPM":
                print("BPM is " + tokens[1])
                self.bpm = int(tokens[1])

        for i in range(len(self.States) - 1):
            PsiK = 60.0 / self.States[i].Bpm;
            Tn = self.States[i].Onset
            Tn1 = self.States[i + 1].Onset
            PhiN0 = self.States[i].PhiN
            PhiN1 = PhiN0 + ((Tn1 - Tn) / PsiK)
            ModValue =  0.5
            Value = ((PhiN1 + ModValue) % (ModValue * 2)) - ModValue
            self.States[i + 1].PhiN = Value

    def PlotPhiNValues(self):
        phases = []
        for i in range(len(self.States) - 1):
            phases.append(self.States[i].PhiN)

        phases = np.array(phases)

        # Criando a figura e o eixo polar
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='polar')

        # Plotando os valores
        ax.plot(phases, np.ones_like(phases), 'o')  # Marcando os pontos no círculo

        for i, phase in enumerate(phases):
            ax.annotate(str(i +1) + "º nota", color="red", xy=(phase, 1), xytext=(3, 3), textcoords='offset points', fontsize=12)


        # Adicionando título e exibindo o gráfico
        ax.set_title('Gráfico Circular de Fases')
        plt.show()

    def ReadAudio(self, path):
        audio, sr = librosa.load(path, sr=48000)
        self.sr = sr
        self.audio = audio
        self.audiolen = len(audio)


    def GetPitchTemplate(self, freq):
        BINFREQ = round(freq / (self.sr / self.windowsize))
        PitchTemplate = np.zeros(self.windowsize)
        for i in range(self.windowsize):
            for j in range(self.harmonics):
                NewAmp = 1/ (2 ** j)
                num = (i - (BINFREQ * (j + 1))) ** 2
                den = 2 * np.pi * self.gausian_sigma ** 2
                value = num / den
                PitchTemplate[i] += NewAmp * np.exp(-value)
            PitchTemplate[i] = PitchTemplate[i] *  self.MaxAmp
        return PitchTemplate

    def GetRMS(self, audio):
        sumOfSquares = 0.0
        for sample in audio:
            sumOfSquares += sample * sample
        rms = math.sqrt(sumOfSquares / len(audio))
        if rms == 0:
            return -1500
        rmsdB = 20 * math.log10(rms)
        return rmsdB

    def GetPitchSimilarity(self, state):
        StateFreq = 440 * (2 ** ((state.Midi - 69) / 12)) 
        pitch_template = self.GetPitchTemplate(StateFreq)
        KLDiv = 0

        for i in range(self.windowsize // 2):
            P = pitch_template[i] * self.MaxAmp
            Q = self.NormEnergy[i]
            if P > 0 and Q > 0:
                KLDiv += P * math.log(P / Q) - P + Q
            elif P == 0 and Q >= 0:
                KLDiv += Q

        KLDiv = np.exp(-self.m_Z * KLDiv);

        if PLOTKL:
            plt.title(f'Pitch-Template para {StateFreq}Hz')
            plt.plot(pitch_template, color='b', label='Pitch Template')
            plt.plot(self.NormEnergy, color='r', label='Spectrogram')

            plt.xlabel('Index de frequência')
            plt.ylabel('Amplitude')
            plt.legend()
            plt.subplots_adjust(bottom=0.15)

            plt.annotate(f'KL Divergence = {KLDiv}', xy=(0.5, 0.5), xycoords='axes fraction',
                         horizontalalignment='center', verticalalignment='center', fontsize=10)
            plt.subplots_adjust(bottom=0.15)
            plt.show()
        return KLDiv

    def GetReward(self, state) -> float:
        PitchSimilarity = self.GetPitchSimilarity(state)
        return PitchSimilarity

    def GetBestEvent(self):
        if self.BestEvent == -1:
            self.Bpm = self.States[0].Bpm

        self.LookAhead = 2
        BestGuess = self.BestEvent
        BestReward = -1
        EventLookAhead = 0
        StatesSize = len(self.States)
        lastLook = self.CurrentEvent

        while (EventLookAhead < self.LookAhead):
            if (lastLook == StatesSize - 1):
                break
            if (lastLook < 0):
                lastLook = 0

            EventLookAhead += self.States[lastLook].Duration * (60 / self.States[lastLook].Bpm)
            state = self.States[lastLook]
            Reward = self.GetReward(state)
            if Reward > BestReward:
                BestReward = Reward
                BestGuess = lastLook
            lastLook += 1
        return BestGuess

    def Process(self):
        self.ReadAudio(self.audio)
        self.MaxAmp = -2000
        block = 0
        self.CurrentEvent = -1
        self.Onset = 0
        self.DetectedOnsets = []
        for i in range(0, self.audiolen, self.hopsize):
            block += 1
            samples = self.audio[i:i+self.windowsize]
            length = len(samples)
            if length < self.windowsize:
                break
            rmsdB = self.GetRMS(samples)
            if rmsdB < -90:
                continue
            fft = np.fft.fft(samples)
            self.NormEnergy = np.abs(fft[:self.windowsize // 2])
            self.MaxAmp = max(self.NormEnergy)
            self.BestEvent = self.GetBestEvent()
            if self.BestEvent != self.CurrentEvent:
                print("Event {} | Onset {}".format(str(self.BestEvent), self.Onset))
                self.CurrentEvent = self.BestEvent
                self.DetectedOnsets.append(self.Onset)
            self.Onset += (1 / self.sr) * self.hopsize * 1000

        # plot audio with onset markers
        OnsetInSamples = []
        for onset in self.DetectedOnsets:
            onset = onset / 1000
            OnsetInSamples.append(onset * self.sr)


        plt.plot(self.audio)
        plt.vlines(OnsetInSamples, -1, 1, color='r')
        plt.show()




if __name__ == "__main__":
    path = "../../../Tests/Test1.txt"
    audio = "../../../Tests/Test1.wav"
    scofo = Scofo(path, audio)
    scofo.Process()




