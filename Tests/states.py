import os
from OScofo import OScofo
from matplotlib import pyplot as plt
import math
import numpy as np


def d1(u, state_onset, sigma):
    return math.exp(-((u - state_onset) ** 2) / (2 * sigma**2))  # Wider Gaussian


# Path setup
root = os.path.dirname(os.path.abspath(__file__))
SCORE_FILE = root + "/Test1.txt"

# Constants
BLOCKS_TO_COMPUTE = 500
HOP_SIZE = 512
FFT_SIZE = 4096
SR = 48000
BLOCK_DUR = 1 / SR * HOP_SIZE
sigma = 40  # Increase this for wider, smoother peaks

print(f"Block duration: {BLOCK_DUR:.3f} sec")

# Initialize OScofo and parse score
OpenScofo = OScofo(SR, FFT_SIZE, HOP_SIZE)
OpenScofo.ParseScore(SCORE_FILE)

# Get states and timing details
states = OpenScofo.GetStates()
states_len = len(states) - 1
bpm = states[states_len].BPMExpected
max_time = states[states_len].OnsetExpected + ((60 / bpm) * states[states_len].Duration)
max_t = math.ceil(max_time / BLOCK_DUR)
print(f"Max time (in blocks): {max_t}")

# Define a set of colors (can expand if needed)
colors = plt.cm.viridis(np.linspace(0, 1, len(states)))

# Plot Gaussian peak for each state
for idx, state in enumerate(states):
    state_onset = math.ceil(state.OnsetExpected / BLOCK_DUR)
    state_timeline = []

    # if idx == 6:

    for t in range(0, max_t):
        d1_value = d1(t, state_onset, sigma) * 0.5  # Use wider Gaussian
        state_timeline.append(d1_value)

    # Plot the Gaussian curve for the current state with a different color
    plt.plot(state_timeline, label=f"State {idx}", color=colors[idx])

# Plot configuration
plt.xlabel("Time (in blocks)")
plt.ylabel("Gaussian Peak Value")
plt.title("Smoother and Wider Gaussian Peaks Around Onset")
plt.legend()

# Show the plot
plt.show()
