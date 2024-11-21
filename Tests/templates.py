import os
from OScofo import OScofo
from matplotlib import pyplot as plt
import math
import numpy as np
from scipy.interpolate import interp1d


def d1(u, state_onset, sigma):
    return math.exp(-((u - state_onset) ** 2) / (2 * sigma**2))  # Wider Gaussian


# Path setup
root = os.path.dirname(os.path.abspath(__file__))
SCORE_FILE = root + "/score.txt"

# Constants
BLOCKS_TO_COMPUTE = 500
HOP_SIZE = 512
FFT_SIZE = 4096
SR = 48000
BLOCK_DUR = 1 / SR * HOP_SIZE

# Initialize OScofo and parse score
OpenScofo = OScofo(SR, FFT_SIZE, HOP_SIZE)
OpenScofo.ParseScore(SCORE_FILE)

# Get states and timing details
pitch = OpenScofo.GetPitchTemplate()

# pitch is a dict, get first key and plot it
template = pitch[list(pitch.keys())[0]]

# Plot the template
# Assuming you have the following parameters
m_Sr = 48000  # Sample rate in Hz
m_FFTSize = 4096  # FFT size

# Get just the first 200 bins
# Original data
template = template[:500]
index = np.arange(len(template))

# Interpolate the data to create a smoother curve
smooth_index = np.linspace(
    index.min(), index.max(), 1000
)  # Increase the number of points
interpolator = interp1d(
    index, template, kind="cubic"
)  # Use cubic interpolation for smoothness
smooth_template = interpolator(smooth_index)

# Plot the original and smoothed templates
plt.figure()
plt.suptitle("Template (Smoothed)")

plt.plot(smooth_index, smooth_template, label="Smoothed", linewidth=2)
plt.legend()
plt.show()
