#!usr/bin/env bash
# File name: wk3_ar_ex2.sh

arr1=(1 2 3 4 5)
arr2=(1 2 3 4 5 6 7 8)

echo ${#arr2[*]} + ${#arr1[*]}|bc -l
expr $(echo ${#arr2[*]}) + $(echo ${#arr1[*]})
