/*
HOW TO COMPILE (need SU installed):
gcc -c twoD_to_twoHalfD.c -I$(CWPROOT)/include
gcc twoD_to_twoHalfD.o -o twoD_to_twoHalfD.exe -L$(CWPROOT)/lib -lsu -lpar -lcwp

Testing:
./twoD_to_twoHalfD.exe nz=125 nx=383 dz=24 dx=24 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "su.h"
#include "par.h"

// SU header read/write*/
#include "segy.h"
#define TRCBYTES                240		//SU-header size, fdelmodc's format


/*********************** self documentation **********************/
char *sdoc[] = {
"  ",
" twoD_to_twoHalfD - Extends a 2D model in the y-direction",
"  ",
" ./twoD_to_twoHalfD nz= nx= ny= input2d= output3d= [optional parameters]",
"  ",
" Required parameters:",
" ",
"   nz= ................ total samples in first dimension (z)",
"   nx= ................ total samples in second dimension (x)",
"   ny= ................ total samples in third dimension (y)",
"   input2d= ........... file name of input 2d velocity field",
"   output3d= .......... file name of output 3d (2.5d) velocity field",
"  ",
" Optional parameters:",
" ",
" ",
" Replicates the provided 2D model ny-times, providing a 3d (2.5d) model ",
" of total size nz*nx*ny. ",
" ",
"      Author 2018",
"      Institution",
"      E-mail: email@domain.com ",
"  ",
NULL};
/**************** end self doc ***********************************/


void twoD_to_twoHalfD(int nz, int nx, int ny, char *inName, char *outName){
	float *vel;
	vel = (float*)malloc(nz*nx*sizeof(float));	
	FILE *fpin, *fpout;

	fpin = fopen(inName, "r");
	fread(vel, nz*nx, sizeof(float), fpin);
	fclose(fpin);

	fpout = fopen(outName, "w");
	int iy;
	for(iy=0; iy<ny; iy++){
		fwrite(vel, nz*nx, sizeof(float), fpout);
	}
	fclose(fpout);

	free(vel);
}


int main(int argc, char *argv[]){
// INIT ARGS, REQUESTDOC //////////////////////////////////////////////////////////
	initargs(argc, argv);
	requestdoc(0);


// DECLARE VARIABLES //////////////////////////////////////////////////////////////
	int nz, nx, ny;
	char *inName, *outName;

// GET INPUT PARAMETERS ///////////////////////////////////////////////////////////
	if( !getparint("nz", &nz) ) err("No nz. Exiting.\n");
	if( !getparint("nx", &nx) ) err("No nx. Exiting.\n");
	if( !getparint("ny", &ny) ) err("No ny. Exiting.\n");
	if( !getparstring("input2d", &inName) ) err("No input2d file provided. Exiting.\n");
	if( !getparstring("output3d", &outName) ) err("No output3d file name provided. Exiting.\n");
	//printf("CHECK: nz=%d \n nx=%d \n ny=%d \n input2d=%s\noutput3d=%s \n", nz, nx, ny, inName, outName);	

// ALLOCATE VARIABLES /////////////////////////////////////////////////////////////


// FILL INITIAL VALUES ///////////////////////////////////////////////////////////


// PROCESS DATA ///////////////////////////////////////////////////////////////
	twoD_to_twoHalfD(nz, nx, ny, inName, outName);
	printf("\n2.5d model saved at %s \nnz=%d\nnx=%d\nny=%d\n\n", outName, nz, nx, ny);	

// FREE VARIABLES /////////////////////////////////////////////////////////////

	
// END MAIN ///////////////////////////////////////////////////////////////////

	return 0;
}



















