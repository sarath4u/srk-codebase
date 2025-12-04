from math_utils import collatz_sequence

start = 13
end = 1000000
cmax = 0
result = 0
for ii in range(start, end, 1):
    chain = len(collatz_sequence(ii))
    if chain > cmax:
        cmax = chain
        result = ii
print(result)
