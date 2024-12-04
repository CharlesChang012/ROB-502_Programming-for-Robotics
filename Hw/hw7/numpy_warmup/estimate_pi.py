import numpy as np


def estimate_pi(N):
    pi_estimate = None
    # --- Your code here 
    x = np.random.uniform(-0.5, 0.5, N)
    y = np.random.uniform(-0.5, 0.5, N)

    p_inCircle = (x**2 + y**2 <= 0.5**2)
    N_circle = np.sum(p_inCircle)

    pi_estimate = 4*N_circle/N
    # ---

    return pi_estimate


if __name__ == "__main__":
    N = 1000
    approx_pi = estimate_pi(N)
    print(f'Estimate of pi is {approx_pi}')