#!/bin/bash

array=( SIGHUP SIGINT SIGQUIT SIGILL )
for i in "${array[@]}"
do
	python -c 'import os, signal;os.kill(os.getpid(), signal.'$i')'
done
