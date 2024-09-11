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
        cls.root = os.path.dirname(os.path.abspath(__file__))

    def test_ProcessScore1(self):
        # Load Audio
        self.data, self.fs = sf.read(self.root + "/Test1.wav")
        if len(self.data.shape) > 1:
            self.data = self.data[:, 0]

        # Initialize OScofo
        self.OScofo = OScofo(48000, 4096, 1024)
        self.OScofo.ParseScore(self.root + "/Test1.txt")

        # Process Audio
        event = -1
        onset = 0
        for i in range(0, len(self.data), self.blockSize):
            audioBlock = self.data[i : i + self.windowSize]
            if len(audioBlock) != self.windowSize:
                break

            if self.OScofo.ProcessBlock(audioBlock):
                currentEvent = self.OScofo.GetEventIndex()
                if currentEvent != event:
                    event = currentEvent
                    print("Event: ", event, " at ", onset)
                onset += 1 / (self.sr / self.blockSize)
            else:
                raise Exception("Error in processing block")
        print("Processing done")


if __name__ == "__main__":
    unittest.main()
