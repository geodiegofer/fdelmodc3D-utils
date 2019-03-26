/*
HOW TO COMPILE (need SU installed):
gcc -c bin2su_2d.c -I$(CWPROOT)/include
gcc bin2su_2d.o -o bin2su_2d.exe -L$(CWPROOT)/lib -lsu -lpar -lcwp

Or Thorbecke's fix:
	copy par.h(erase unused header values) and segy.h to this folder
	gcc -c bin2su_2d.c
	gcc bin2su_2d.o -o bin2su_2d.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "par.h"
#include "segy.h"

#define TRCBYTES                240

void bin2su_2d(int nz, int nx, float dz, float dx, char *inName, char *outName){
/*
	FIrst version, improve later.
	Substitute for(ix..) with while loop
	Check bounds
*/	
	segy hdr;
	float *binTrace;
	FILE *fpin, *fpout;

	binTrace = (float*)malloc(nz*sizeof(float));	

	hdr.d1 = dz;
	hdr.d2 = dx;
	hdr.ns = nz;
	
	fpin = fopen(inName, "r");
	fpout = fopen(outName, "w");
	int iz, ix;
	for(ix = 0; ix<nx; ix++){
		// Read one raw trace
		fread(binTrace, nz, sizeof(float), fpin);
	
		// Write header
		fwrite(&hdr, TRCBYTES, 1, fpout); //& is necessary because structure doesn't decay automatically

		// Write raw trace
		fwrite(binTrace, nz, sizeof(float), fpout);		
	}

	fclose(fpin);
	fclose(fpout);
	printf("Wrote data to %s\n", outName);	

	free(binTrace);
}









