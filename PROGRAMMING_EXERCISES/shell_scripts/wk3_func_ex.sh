#!usr/bin/env bash	
# File name: wk3_func_ex.sh

function plier {
	
	local mult=1
	for evry in $@
	do
		let mult*=evry
	done
	echo $mult
}

function isiteven {
	if [[ $1%2 -eq 0 ]]
	then
		echo 1
	else
		echo 0
	fi
}

function nevens {
	local count=0
	for i in $@
	do 
		if [[ $(isiteven i) -eq 1 ]]
		then
			let count+=1
		fi
	done
	echo $count	
}

function howodd {
	local per=$(echo 1-$(nevens $@)/$# |bc -l)
	echo $per*100 |bc -l
}
 
function fib {
	if [[ $1 -eq 1 ]]
	then
		echo 0
	elif [[ $1 -eq 2 ]]
	then	
		echo -n 0" "
		echo 1
	else
		local count=$1
		local first=0
		echo -n $first" "
		local second=1
		echo -n $second" "
		while [[ count -gt 2 ]]
		do
			let third=second+first	
			echo -n $third" "
			let first=second 
			let second=third
			let count-=1
		done
	echo $'\n'
	fi
}
