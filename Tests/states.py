import os
from OScofo import OScofo
from matplotlib import pyplot as plt
import math
import numpy as np


def d1(u, state_onset, sigma):
    return math.exp(-((u - state_onset) ** 2) / (2 * sigma**2))  # Wider Gaussian


# Path setup
root = os.path.dirname(os.path.abspath(__file__))
SCORE_FILE = root + "/Test0.txt"

# Constants
BLOCKS_TO_COMPUTE = 500
HOP_SIZE = 512
FFT_SIZE = 4096
SR = 48000
BLOCK_DUR = 1 / SR * HOP_SIZE
sigma = 20  # Increase this for wider, smoother peaks

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
    state_timeline = OpenScofo.GetGaussianTimeLine(idx, 1000)
    plt.plot(state_timeline, label=f"State {idx}", color=colors[idx])

# Plot configuration
plt.xlabel("Time (in blocks)")
plt.ylabel("Gaussian Peak Value")
plt.title("Smoother and Wider Gaussian Peaks Around Onset")
plt.legend()

# make y-axis range 0-1
plt.ylim(-0.1, 1.2)

# Show the plot
plt.show()
