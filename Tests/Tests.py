import os
import unittest

import numpy
import soundfile as sf

from OScofo import OScofo


class ProcessBlock(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.sr = 48000
        cls.windowSize = 4096
        cls.blockSize = 1024
        cls.OScofo = OScofo(48000, 4096, 1024)
        cls.root = os.path.dirname(os.path.abspath(__file__))
        cls.data, cls.fs = sf.read(cls.root + "/Test1.wav")
        if len(cls.data.shape) > 1:
            cls.data = cls.data[:, 0]

    def test_LoadScore(self):
        print("Loading file {}".format(self.root + "/Test1.txt"))
        self.OScofo.ParseScore(self.root + "/Test1.txt")
        print("Score loaded")

    def test_ProcessBlock(self):
        print("Processing Event Index")
        event = -1
        onset = 0
        self.OScofo.SetdBTreshold(-55)
        for i in range(0, len(self.data), self.blockSize):
            audioBlock = self.data[i:i + self.blockSize]
            self.OScofo.ProcessBlock(audioBlock)
            currentEvent = self.OScofo.GetEventIndex()
            if currentEvent != event:
                event = currentEvent
            input("Press Enter to continue...")
            onset += 1 / (self.sr / self.blockSize)
        print("Processing done")


if __name__ == '__main__':
    unittest.main()
