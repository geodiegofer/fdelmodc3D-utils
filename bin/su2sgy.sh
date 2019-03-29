#!/bin/bash


if [ "$#" -ne 2 ]; then
		echo "print_my_input: wrong number of input parameters. Exiting."
		echo "Ex: ./su2sgy.sh sufile.su"
		#return #for function
		exit #for script
fi

dum=hdrsu.su

# Create extra header for segywrite
segyhdrs <$1 >$dum

# Create segy file
segywrite tape=$2 endian=0 verbose=1 <$dum 

# Clean up
rm $dum
