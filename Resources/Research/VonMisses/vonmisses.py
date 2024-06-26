import matplotlib.pyplot as plt
import numpy as np

# get 10 random -pi to pi
angles = np.random.uniform(np.pi - 0.2, np.pi, 200)

# Convert angles to Cartesian coordinates
x = np.cos(angles)
y = np.sin(angles)

# Calculate the mean vector components
R_x = np.mean(x)
R_y = np.mean(y)

# Calculate the resultant length (R)
R = np.sqrt(R_x**2 + R_y**2)
if R < 0.53:
    kappa = 2 * R + R**3 + (5 * R**5) / 6
elif R < 0.85:
    kappa = -0.4 + 1.39 * R + 0.43 / (1 - R)
else:
    kappa = R * (3 - R**2) / (1 - R**2)

# Plot angles and mean vector
plt.figure(figsize=(6, 6))  # Set the figure size

# Plot the random points
plt.scatter(x, y, color='blue', label='Random points')
plt.scatter(R_x, R_y, color='red', label='Mean vector')

# Plot the mean vector as an arrow
# plt.arrow(0, 0, R_x, R_y, width=0.01, color='red', label='Mean vector')

# Set labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Random points and mean vector')

# plot subtitle with kappa  
plt.suptitle(f'Kappa: {kappa:.2f}')

# Add legend
plt.legend()

# Show the plot
plt.grid(True)
plt.show()





