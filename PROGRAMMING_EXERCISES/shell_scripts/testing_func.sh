#!usr/bin/env bash
# File name : testing_func.sh

function summing {
	sum=0
	for each in $@
	do
		let sum+=each
	done
	echo $sum
}
