import numpy as np
from scipy.optimize import root_scalar
from scipy.special import iv


# Define the function for which we need to find the root
def ratio_bessel(lambda_val, r):
    return iv(1, lambda_val) / iv(0, lambda_val) - r

# Parameters
r = 1  # Example value for r

# Use a numerical solver to find lambda
solution = root_scalar(ratio_bessel, args=(r,), bracket=[0.1, 10], method='brentq')

# Output the result
lambda_value = solution.root if solution.converged else "Solution did not converge"
print(lambda_value)
