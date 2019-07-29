#!/bin/bash

echo "------------------------------------------------"
echo "sufarithsub.sh - Gets diff of 2 su files and ximage it to user."

if [ "$#" -ne 2 ]; then
	echo "sufarithsub.sh: wrong number of input parameters. Exiting."
	echo "Correct usage is:"
	echo "	sufarithsub.sh sufile1.su sufile2.su"
	echo "Example:"
	echo "	sufarithsub.sh shots1.su shots2.su"
	echo "------------------------------------------------"
	exit # for shellscript
	#return # for shell function
fi
echo "------------------------------------------------"

n1=$(surange <$1 | awk '$1 ~ /ns/ {print $2}')

sustrip <$1 >f1
sustrip <$2 >f2

farith in=f1 in2=f2 out=f3 op=sub

ximage n1=$n1 <f3 perc=98 legend=1 lwidth=8 & 

rm f1 f2 f3
