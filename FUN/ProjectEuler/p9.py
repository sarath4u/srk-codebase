import math
from math_utils import is_square

N = 1000

for a in range(1, N//2 - 0):
    for b in range(a + 1, N//2):
        c2 = a*a + b*b
        if is_square(c2):
            c = math.sqrt(c2)
            if a + b + c == 1000:
                print(a, b, c, a*b*c)
