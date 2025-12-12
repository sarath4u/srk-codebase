#!/usr/bin/env bash
# File name: range.sh

function range {
	local count=$1
	while [[ count -gt 1 ]]
	do	
		let count-=1
		echo -n $count" "
	done
	echo $'\n'
}
