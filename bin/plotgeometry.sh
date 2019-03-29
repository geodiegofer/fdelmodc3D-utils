#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "plotgeometry: wrong number of input parameters. Exiting."
	echo "Correct usage is:"
	echo "plotgeometry SrcRecFile.su velfile.su"
	echo "Plot model+geometry on ximage according to fdelmodc's manual."
	exit # for shellscript
	#return # for shell function
fi

suop2 $1 $2 w1=6000 w2=1 op=sum | suximage bclip=6000 wclip=0 &
