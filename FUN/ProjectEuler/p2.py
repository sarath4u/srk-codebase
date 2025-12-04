N = 4000000
ilast = 0
inext = 1
summ = 0
while inext < N:
    inext_old = inext
    inext += ilast
    summ += inext if inext%2 == 0 else 0
    ilast = inext_old
print(summ)
