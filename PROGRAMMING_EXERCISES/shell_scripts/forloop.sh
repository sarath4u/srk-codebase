#!/usr/bin/env bash
# File: forloop.sh

for i in {1..3}
do
    echo "i is equal to $i"
done

for i in ding dong bell
do
	echo $i
done

arr=(1 3 5 7 9)
for i in ${arr[*]}
do
	echo $i
done

for i in $(ls)
do
	echo $i
done
