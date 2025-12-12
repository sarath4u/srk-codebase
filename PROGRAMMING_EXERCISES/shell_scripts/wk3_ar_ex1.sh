≈#!usr/bin/env hash
# File name: wk3_ar_ex1.sh

array=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
echo ${array[$(expr $1 - 1)]}
