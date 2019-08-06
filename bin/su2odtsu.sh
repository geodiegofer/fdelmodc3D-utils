#!/bin/bash

if [ "$#" -ne 4 ]; then
	echo "su2odtsu: wrong number of input parameters. Exiting."
	echo "Creates OpendTect-like SU file from another SU file"
	echo "Usage: "
	echo "./su2odtsu.sh infile.su d2 d3 outfile.su"
	echo "Ex: "
	echo "./su2odtsu.sh infile.su 25.0 25.0 outfile.su"
	#return #for function
	exit #for script
fi

#infile=farr.su
#d2=25.0
#d3=25.0
#outfile=farr-odt.su
infile=$1
d2=$2 
d3=$3
outfile=$4

surange <$infile >hdr.txt

# Set sx as a gx without negative values
echo "Setting sx as x-coord in meters"
firstgx=$(cat hdr.txt | awk '$1 ~ /gx/ {print $2}')
gxfac=$((0-$firstgx ))
suchw key1=sx key2=gx a=$gxfac <$infile >tmp.su #  
suchw key1=sx key2=sx a=$(($d2*1000)) <tmp.su >tmp2.su # add dx, ODT does not like 0-values
mv tmp2.su $outfile

# Same for sy
echo "Setting sy as y-coord in meters"
firstgy=$(cat hdr.txt | awk '$1 ~ /gy/ {print $2}')
gyfac=$((0-$firstgy ))
suchw key1=sy key2=gy a=$gyfac <$outfile >tmp.su #  
suchw key1=sy key2=sy a=$(($d3*1000)) <tmp.su >tmp2.su # add dx, ODT does not like 0-values
mv tmp2.su $outfile

# Set cdp as ix (crossline?)
echo "Setting cdp as x-coord in samples"
suchw key1=cdp key2=sx d=$(($d2*1000)) <$outfile >tmp.su
mv tmp.su $outfile

# Set fldr as iy (inline?)
echo "Setting fldr as y-coord in samples"
suchw key1=fldr key2=sy d=$(($d3*1000)) <$outfile >tmp.su
mv tmp.su $outfile

# Clean
rm hdr.txt



