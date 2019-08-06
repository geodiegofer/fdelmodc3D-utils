#!/bin/bash

echo "------------------------------------------------"
echo "sunimagedif.sh - Gets diff of 2 su files and nimage it to user."

if [ "$#" -ne 2 ]; then
	echo "sunimagedif.sh: wrong number of input parameters. Exiting."
	echo "Correct usage is:"
	echo "	sunimagedif.sh sufile1.su sufile2.su"
	echo "Example:"
	echo "	sufarithsub.sh shots1.su shots2.su"
	echo "------------------------------------------------"
	exit # for shellscript
	#return # for shell function
fi
echo "------------------------------------------------"

n1=$(surange <$1 | awk '$1 ~ /ns/ {print $2}')
n2=$(surange <$1 | awk '$1 ~ /trwf/ {print $2}')

sustrip <$1 >f1
sustrip <$2 >f2

farith in=f1 in2=f2 out=f3 op=sub

nimage n1=$n1 n2=$n2 <f1 perc=98 legend=1 lwidth=8 title=$1 & 
nimage n1=$n1 n2=$n2 <f2 perc=98 legend=1 lwidth=8 title=$2 & 
nimage n1=$n1 n2=$n2 <f3 perc=98 legend=1 lwidth=8 title='dif' & 

rm f1 f2 f3
