#!/usr/bin/env bash
# File name: extremes.sh

function extremes {
	local count=$#
	local max=0
	local min=0
	for i in $@
	do
		if [[ i -gt max ]]
		then
			let max=i
		fi
		if [[ i -lt min ]]
		then
			let min=i
		fi 
	done
	echo $max $min
}
