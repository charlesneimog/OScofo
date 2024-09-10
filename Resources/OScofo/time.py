class TimeInference:
    def __init__(self, states):
        self.states = states
        self.update_phrase()
        print(self.states)

        pass

    def update_phrase(
        self,
    ):
        for i in range(0, len(self.states) - 1):
            print(self.states[i])
