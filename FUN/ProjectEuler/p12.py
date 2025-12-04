from math_utils import triangle_numbers, factor_generator

N = 500
ndivisors = 0
n = 1
while ndivisors <= N:
    num = triangle_numbers(n)[-1]
    ndivisors = len(factor_generator(num))
    n += 1

print(f"The first triangular number with over {N} divisors is the {n-1}th triangular number, {num}")
