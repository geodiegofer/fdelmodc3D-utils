#!/bin/bash

function sunimage(){
	if [ "$#" -ne 4 ]; then
		echo "sunimage: wrong number of input parameters. Exiting."
		echo "Correct usage is:"
		echo "sunimage 121 121 file.su perclvl"
		#exit # for shellscript
		return # for shell function
	fi

	n1=$1
	n2=$2
	name=$3

	sustrip <$3 >test.bin
	nimage n1=$n1 n2=$n2 <test.bin perc=$4 &

	rm test.bin 
}

function plotgeometry() { 
	if [ "$#" -ne 2 ]; then
		echo "plotgeometry: wrong number of input parameters. Exiting."
		echo "Correct usage is:"
		echo "plotgeometry SrcRecFile.su velfile.su"
		#exit # for shellscript
		return # for shell function
	fi

	suop2 $1 $2 w1=6000 w2=1 op=sum | suximage bclip=6000 wclip=0 &
}


