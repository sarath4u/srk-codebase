import math
import numpy as np
def factor_generator(N):
    """
    Generates all the factors of a number
    """
    Nroot = round(N**0.5)
    factors = [] 
    for ii in range(1, Nroot+1):
        if N%ii == 0: factors += [ii, N//ii]
    return(factors)

def isPrime(N):
    """
    Checks if a number is prime or not
    """
    flist = factor_generator(N)
    if len(flist) > 2:
        return 0
    else:
        return 1
def prime_finder(N):
    """
    Generates all the prime factors of a number
    """
    factors = factor_generator(N)
    plist = []
    for ii in factors:
        if isPrime(ii): plist.append(ii)
    return sorted(plist)

def prime_lister(N):
    """
    Lists all the prime numbers below a number
    """
    plist = []
    for ii in range(1, N):
        if isPrime(ii): plist.append(ii)
    return plist

def isPalindrome(N):
    """
    Returns true if the given number is a Palindrome
    """
    nlist = list(str(N))
    llist = len(nlist)
    count = 0
    for ii in range(llist):
        if nlist[ii] == nlist[llist-ii-1]:
            count += 1
        else:
            return(0)
    if count >= llist//2: return(1)
    

def hcf_iterate(numbers, p):
    """
    helper function for computing hcf
    """
    new_numbs  = []
    new_mults  = []
    fact_found = False
    for n in numbers:
        ans = n % p
        if ans == 0:
            if not fact_found:
                new_mults.append(p)
                fact_found = True
            quo = n // p
            new_numbs.append(quo)
        else:
            new_numbs.append(n)
    return new_numbs, new_mults

def hcf(numbers):
    """
    Computes the highest common factor
    """
    nmax      = max(numbers)
    plist     = prime_lister(nmax)
    multiples = []
    count = 1
    while sum(numbers) > len(numbers): 
        new_numbs, new_mults = hcf_iterate(numbers, plist[count])
        multiples += new_mults
        count = count + 1 if count < len(plist) - 1 else 0
        numbers = new_numbs
    return multiples, math.prod(multiples)
               
def is_square(n):
    """
    Checks if a natural number is a perfect square or not
    """
    return n == math.isqrt(n)**2

def triangle_numbers(n):
    """
    Lists the sequence of n triangle numbers
    """
    trilist = [0]
    for ii in range(1, n+1):
        trilist.append(trilist[-1] + ii)
    return(trilist[1:])

def collatz_sequence(n):
    """
    Lists the sequence of numbers of the collatz 
    series starting from n
    """
    clist = [n]
    while n > 1:
        n = n // 2 if n % 2 == 0 else 3 * n + 1
        clist.append(n)
    return clist
