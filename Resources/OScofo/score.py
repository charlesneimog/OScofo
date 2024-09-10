import os
import music21

from markov import MarkovType, EventType, State


class Score:
    def __init__(self, score):
        self.states = []
        if os.path.exists(score):
            self.score = score
        else:
            raise FileNotFoundError

        # read score file
        with open(score, "r") as file:
            self.score = file.read()

        # make semi-markov chain
        lines = self.score.split("\n")
        bpm = 0
        score_index = 0
        previous_phrase = 0
        previous_onset = 0
        for line in lines:
            newstate = State()
            tokens = line.split(" ")
            if tokens[0] == "BPM":
                bpm = int(tokens[1])
            elif tokens[0] == "NOTE":
                score_index += 1
                newstate.score_index = score_index

                # Time Observations
                psik = 60 / float(bpm)
                newstate.bpm = bpm
                newstate.dur = float(tokens[2])
                newstate.onset = (newstate.dur * psik) + previous_onset
                newstate.phase = previous_phrase + (
                    (newstate.onset - previous_onset) / psik
                )
                previous_onset = newstate.onset
                previous_phrase = newstate.phase

                # Pitch
                newstate.pitch = float(tokens[1])
                newstate.template = self.get_pitch_template(newstate.pitch)
                newstate.dur = float(tokens[2])

                # Markov
                newstate.event_type = EventType.NOTE
                newstate.markov_type = MarkovType.SEMIMARKOV

                self.states.append(newstate)

                # Transition Event (dummy silence)
                trans_event = self.get_trans_event(score_index)
                self.states.append(trans_event)

    def get_pitch_template(self, midi):
        pitch = music21.pitch.Pitch(midi)
        freq = pitch.frequency

        pass

    def get_trans_event(self, index):
        newstate = State()
        newstate.pitch = 0
        newstate.score_index = index
        newstate.dur = 0
        newstate.event_type = EventType.TRANSITION
        newstate.markov_type = MarkovType.MARKOV
        return newstate
