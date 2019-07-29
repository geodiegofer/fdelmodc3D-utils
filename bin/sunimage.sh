#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "sunimage: wrong number of input parameters. Exiting."
	echo "Correct usage is:"
	#echo "sunimage 121 121 file.su perclvl"
	echo "sunimage file.su perclvl"
	exit # for shellscript
	#return # for shell function
fi

#n1=$1
n1=$(surange <$1 | awk '$1 ~ /ns/ {print $2}') 
#n2=$2
n2=$(surange <$1 | awk '$1 ~ /tracf/ {print $3}') 

sustrip <$1 >test.bin
#nimage n1=$n1 n2=$n2 <test.bin perc=$4 &
nimage n1=$n1 n2=$n2 <test.bin perc=$2 &

rm test.bin 
