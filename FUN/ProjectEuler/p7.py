from math_utils import isPrime

N      = 10001
count  = 1
pCount = 1
while pCount <= N:
    count += 1
    if isPrime(count):
        pCount += 1
print(count)

