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

#include "su.h"
#include "segy.h"
#include "par.h"

#define TRCBYTES                240

/*********************** self documentation **********************/
char *sdoc[] = {
"  ",
" bin2su - puts a SU header on binfield, save it on sufield",
"  ",
" ./bin2su binfield= sufield= nz= nx= ny= dz= dx= dy=[optional parameters]",
"  ",
" Required parameters:",
" ",
"   binfield= .......... file name to read binary 3d field",
"   sufield= ........... file name to save SU 3d field",
"   nz= ................ number of samples in 1st dimension (z)",
"   nx= ................ number of samples in 2nd dimension (x)",
"   ny= ................ number of samples in 3rd dimension (y)",
"   dz= ................ spacing (m) of 1st dimension (z)",
"   dx= ................ spacing (m) of 2nd dimension (x)",
"   dy= ................ spacing (m) of 3rd dimension (y)",
"  ",
" Optional parameters:",
" ",
"   no optional parameters (yet)",
" ",
" If no ny is provided, a it assumes a 2D model input.",
" Filled header parameters (for a complete list, please check segy.h):",
" nz	->	hdr.ns",
" dz	->	hdr.d1",
" nx	->	hdr.n2 (maybe remove, since n2 is type short)",
" dx	->	hdr.d2",
" ix*dx	->	hdr.gx",
" ny	->	----",
" dy	->	----",
" iy*dy	->	hdr.gy",
" nx*ny	->	hdr.ntr",
" ",
"      Author 2018",
"      Institution",
"      E-mail: email@domain.com ",
"  ",
NULL};
/**************** end self doc ***********************************/



void bin2su(int nz, int nx, int ny, float dz, float dx, float dy, char *inName, char *outName){
/*
	FIrst version, improve later.
	Substitute for(ix..) with while loop
	Check bounds
*/	
	segy hdr;
	FILE *fpin, *fpout;
	int ix, iy, trc=0;
	int nread;
	float *binTrace;

	binTrace = (float*)malloc(nz*sizeof(float));	

	hdr.ns = nz;
	hdr.d1 = dz;
	hdr.d2 = dx;
	hdr.ntr = nx*ny;
	hdr.trid = TRID_DEPTH; //standard to read vertical data
	
	fpin = fopen(inName, "r");
	fpout = fopen(outName, "w");
/*	int iz, ix;*/
/*	for(ix = 0; ix<nx; ix++){*/
/*		// Read one raw trace*/
/*		fread(binTrace, nz, sizeof(float), fpin);*/
/*	*/
/*		// Write header*/
/*		fwrite(&hdr, TRCBYTES, 1, fpout); //& is necessary because structure doesn't decay automatically*/

/*		// Write raw trace*/
/*		fwrite(binTrace, nz, sizeof(float), fpout);		*/
/*	}*/

	for(iy=0; iy<ny; iy++){
		for(ix=0; ix<nx; ix++){
			// Set header for current "trace"
			hdr.gx = (int) ix*dx*1000;
			//hdr.gx = (int) (ix+1)*dx*1000; //apparently, it is 1-indexed 
			hdr.gy = (int) iy*dy*1000; 			
			//hdr.gy = (int) (iy+1)*dy*1000; //apparently, it is 1-indexed 
 			
			//printf("(ix, iy)=(%d, %d) hdr.gx=%d hdr.gy=%d\n", ix, iy, hdr.gx, hdr.gy);

			// Read one raw trace from input file
			nread = fread(binTrace, 1, nz*sizeof(float), fpin);
			if( nread != (nz*sizeof(float)) ){ 
				printf("\nData reading failed at trace (ix,iy)=(%d,%d), trace %d. Exiting.\n", ix, iy, trc);
				printf("Please check provided dimensions nz, nx and ny.\n");
				exit(0);
			}

			// Write header to ouput file
			fwrite(&hdr, TRCBYTES, 1, fpout); //& is necessary because structure doesn't decay automatically
			
			// Write raw trace to output file
			fwrite(binTrace, nz, sizeof(float), fpout);
			
			trc++;
		}
	}

	fclose(fpin);
	fclose(fpout);
	printf("Wrote data to %s\n", outName);	

	free(binTrace);
}

int main(int argc, char *argv[]){
//INIT SU SELFDOC AND IO HANDLING FUNCTIONS /////////////////////////////////////
  initargs(argc, argv);
  requestdoc(1);

// DECLARE VARIABLES //////////////////////////////////////////////////////////
	int nz, nx, ny; 
	float dz, dx, dy;
	char *inName, *outName;
	int key3d=1;

// GET INPUT PARAMETERS ///////////////////////////////////////////////////////
/*	nz = atoi(argv[1]);*/
/*	nx = atoi(argv[2]);*/
/*	dz = atof(argv[3]);*/
/*	dx = atof(argv[4]);*/
/*	strcpy(inName, argv[5]);*/
/*	strcpy(outName, argv[6]);*/
	if( !getparint("nz", &nz) ) err("No nz. Exiting.\n");
	if( !getparint("nx", &nx) ) err("No nx. Exiting.\n");
	if( !getparint("ny", &ny) ) { ny = 1; key3d=0; };
	if( !getparfloat("dz", &dz) ) err("No dz. Exiting.\n");
	if( !getparfloat("dx", &dx) ) err("No dx. Exiting.\n");
	if( !getparfloat("dy", &dy) ) dy = 0.0;
	if( !getparstring("binfield", &inName) ) err("No binfield file name provided. Exiting.");
	if( !getparstring("sufield", &outName) ) err("No sufield file name provided. Exiting.");

	//printf("CHECK: nz=%d \n nx=%d \n ny=%d dz=%f \n dx=%f \n dy=%f \n binfield=%s \n sufield=%s \n", nz, nx, ny, dz, dx, dy, inName, outName);	

	if(key3d){
		printf("3D binary field provided.\n");
		printf("Putting headers on %s, saving result on %s.\n", inName, outName);
		printf(" nz=%d \n nx=%d \n ny=%d \n dz=%f \n dx=%f \n dy=%f\n ", nz, nx, ny, dz, dx, dy);	
	}else{
		printf("2D binary field provided.\n");
		printf("Putting headers on %s, saving result on %s.\n", inName, outName);
		printf(" nz=%d \n nx=%d \n ny=%d \n dz=%f \n dx=%f \n dy=%f\n", nz, nx, ny, dz, dx, dy);	
	}

// PROCESS DATA ///////////////////////////////////////////////////////////////
	bin2su(nz, nx, ny, dz, dx, dy, inName, outName);

// FREE VARIABLES /////////////////////////////////////////////////////////////
	
// END MAIN ///////////////////////////////////////////////////////////////////
	return 0;
}








