#!/bin/bash

# Check input parameters
if [ "$#" -ne 2 ]; then
	echo "suximageall: wrong number of input parameters. Exiting."
	echo "Ex: suximageall file.su perclvl"
	return
fi

surange <$1 | awk '$1 ~ /tracl/ {print $3}' | suximage n2=$(cat) <$1 perc=$2 legend=1 &
