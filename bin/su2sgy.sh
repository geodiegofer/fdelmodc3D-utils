#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "su2sgy: wrong number of input parameters. Exiting."
	echo "Creates sgy file from su file."
	echo "Ex: ./su2sgy.sh file.su"
	echo "(outputs file.sgy)"
	#return #for function
	exit #for script
fi

strname="${1%%.*}" #strips extension from input
dum=hdrsu.su

# Create extra header for segywrite
segyhdrs <$1 >$dum

# Create segy file
#segywrite tape=$2 endian=0 verbose=1 <$dum 
segywrite tape=$strname.sgy endian=0 verbose=1 <$dum 

# Clean up
rm $dum
rm binary
rm header
