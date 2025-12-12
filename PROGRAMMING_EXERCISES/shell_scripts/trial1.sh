#!/bin/bash

# accepts some command line arguments and echo out some details about them.
echo $0
echo 'There are '$#' command line arguments'
echo $@' are the command line arguments'
echo $2' is the second one'
echo $?
echo $$
echo $USER" is the user"
echo $HOSTNAME
echo $RANDOM
echo $SECONDS
echo $LINENO