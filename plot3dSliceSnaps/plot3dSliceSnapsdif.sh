#!/bin/bash

if [ "$#" -ne 7 ]; then
	echo ""
	echo "----- fdelmodc3D-utils repo's plot3dSliceSnapsdif.sh -----"
	echo "Usage: ./plot3dSliceSnaps.exe nz nx ny slicedim fac snaps.bin slices.bin"
	echo ""
	exit
fi 

nz=$1
nx=$2
ny=$3 
slicedim=$4
fac=$5
file1=$6
file2=$7

title1="$file1 $slicedim slice,fac=$fac"
title2="$file2 $slicedim slice,fac=$fac"
title3="dif $slicedim slice,fac=$fac "


echo "slicing $file1..."
plot3dSliceSnaps.exe $nz $nx $ny $slicedim $fac $file1 tmp1.bin
echo "done."
echo "slicing $file2..."
plot3dSliceSnaps.exe $nz $nx $ny $slicedim $fac $file2 tmp2.bin
echo "done."

farith <tmp1.bin in2=tmp2.bin op=sub >tmp3.bin 

n1=0
n2=0
if [ $slicedim == 'y' ]; then
	n1=$nz
	n2=$nx
elif [ $slicedim == 'x' ]; then	
	n1=$nz
	n2=$ny
elif [ $slicedim == 'z' ]; then	
	n1=$nz
	n2=$ny
fi

echo ""
echo "n1=$n1 n2=$n2"
nimage n1=$n1 n2=$n2 <tmp1.bin perc=98 title=$title1 legend=1 &
nimage n1=$n1 n2=$n2 <tmp2.bin perc=98 title=$title2 legend=1 &
nimage n1=$n1 n2=$n2 <tmp3.bin perc=98 title=$title3 legend=1 &

wait
rm tmp1.bin tmp2.bin tmp3.bin


