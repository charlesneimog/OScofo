import matplotlib.pyplot as plt
import numpy as np

# Parameters
num_points = 2048
bin_width = 1
sigma = 1

# Calculate the means based on the center bins
mu1 = 30 * bin_width
mu2 = 60 * bin_width

# Generate samples from the first Gaussian distribution centered around bin 30
samples1 = np.random.normal(mu1, sigma, num_points // 2)

# Generate samples from the second Gaussian distribution centered around bin 60
samples2 = np.random.normal(mu2, sigma, num_points // 2)

# Combine the samples from both distributions
samples = np.concatenate((samples1, samples2))

# Plot the histogram of the combined samples
plt.hist(samples, bins=50, density=True, alpha=0.6, color='g')

# Plot the theoretical probability density functions for both distributions
x = np.linspace(min(mu1, mu2) - 3 * sigma, max(mu1, mu2) + 3 * sigma, 100)

pdf1 = 1 / (sigma * np.sqrt(2 * np.pi)) * np.exp(-0.5 * ((x - mu1) / sigma) ** 2)
plt.plot(x, pdf1, linewidth=2, color='r')

pdf2 = 1 / (sigma * np.sqrt(2 * np.pi)) * np.exp(-0.5 * ((x - mu2) / sigma) ** 2)
plt.plot(x, pdf2, linewidth=2, color='b')

plt.title('Combined Gaussian Distributions (Centered around Bins 30 and 60)')
plt.xlabel('Value')
plt.ylabel('Probability Density')
plt.grid(True)
plt.show()

