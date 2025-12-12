#!/usr/bin/env bash
# File: sum.sh

variable_one=3.14
variable_two=6.28

echo "The sum is "$(echo $variable_one + $variable_two| bc -l)
