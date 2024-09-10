import os

from enum import Enum


class EventType(Enum):
    NOTE = 1
    TRANSITION = 2


class MarkovType(Enum):
    SEMIMARKOV = 1
    MARKOV = 2


class State:
    def __init__(self):
        self.pitch = ""
        self.dur = 0
        self.bpm = 0
        self.markov_type = ""
        self.event_type = ""
        self.event_index = 0
        self.score_index = 0
        self.onset = 0
        self.phase = 0
        self.IOI = 0
        self.type = ""

    def __str__(self):
        if self.markov_type == MarkovType.SEMIMARKOV:
            return f"<SEMI-MARKOV NOTE {self.pitch}>"
        elif self.markov_type == MarkovType.MARKOV:
            return f"<MARKOV NOTE {self.pitch}>"

        return f"<{self.event_type} NOTE {self.pitch}>"

    def __repr__(self):
        return self.__str__()
