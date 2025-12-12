#!/usr/bin/env bash
# File: vars.sh

echo "the no of arguments is $#"
echo "the first argument is $1"
echo "the second argument is $2"
echo "the third argument is $3"
echo "the result is" $(expr $# \* $1)
