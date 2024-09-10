class TimeInference:
    def __init__(self, states):
        self.states = states
        self.update_phrase()
        print(self.states)

        pass

    def update_phrase(
        self,
    ):
        psi_k = 60 / self.states[0].bpm
        self.states[0].phase_expected = 0
        for i in range(0, len(self.states) - 1):
            tn = self.states[i].onset
            tn1 = self.states[i + 1].onset
            phi_n0 = self.states[i].phase
            phi_n1 = phi_n0 + ((tn1 - tn) / psi_k)
            self.states[i + 1].phase = phi_n1
