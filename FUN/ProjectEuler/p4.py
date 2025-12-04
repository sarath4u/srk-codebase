from math_utils import isPalindrome

check = 0
digit = 999
output = 0
for ii in range(digit, digit//2, -1):
    for jj in range(digit, digit//2, -1):
        N = ii * jj
        check = isPalindrome(N)
        if check:
            output = max(N, output)
print(output)

