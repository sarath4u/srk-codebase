import numpy as np

N = 100
lst = np.arange(1, N+1, dtype=int)
susq = np.sum(lst**2)
sqsu = np.sum(lst)**2
print(sqsu - susq)
