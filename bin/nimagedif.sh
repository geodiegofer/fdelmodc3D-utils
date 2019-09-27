#!/bin/bash

echo "------------------------------------------------"
echo "nimagedif.sh - Gets diff of 2 bin files and nimages them to user."

if [ "$#" -ne 4 ]; then
	echo "nimagedif.sh: wrong number of input parameters. Exiting."
	echo "Correct usage is:"
	echo "	nimagedif.sh nz nx file1.bin file2.bin"
	echo "Example:"
	echo "	nimagedif.sh 1024 101 shots1.bin shots2.bin"
	echo "------------------------------------------------"
	exit # for shellscript
	#return # for shell function
fi
echo "------------------------------------------------"

n1=$1
n2=$2

farith in=$3 in2=$4 out=tmp.bin op=sub

nimage n1=$n1 n2=$n2 <$3 perc=98 legend=1 lwidth=8 title="$3" & 
nimage n1=$n1 n2=$n2 <$4 perc=98 legend=1 lwidth=8 title="$4" & 
nimage n1=$n1 n2=$n2 <tmp.bin perc=98 legend=1 lwidth=8 title="dif" & 
wait

rm tmp.bin
