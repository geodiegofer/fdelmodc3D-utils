/*
HOW TO COMPILE (need SU installed):
gcc -c bin2su.c -I$(CWPROOT)/include
gcc bin2su.o -o bin2su.exe -L$(CWPROOT)/lib -lsu -lpar -lcwp

Or Thorbecke's fix:
	copy par.h(erase unused header values) and segy.h to this folder
	gcc -c bin2su.c
	gcc bin2su.o -o bin2su.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "su.h"
#include "segy.h"
#include "par.h"

#define TRCBYTES                240 //as in fdelmodc 

/*********************** self documentation **********************/
char *sdoc[] = {
"  ",
" bin2su - puts a SU header on binmodel, save it on sumodel", 
"  ",
" ./bin2su binmodel= sumodel= nz= nx= ny= dz= dx= dy=  [optional parameters]",
"  ",
" Required parameters:",
" ",
"   binmodel= .......... file name to read binary 2D or 3D model",
"   sumodel= ........... file name to save SU 2D or 3D model",
"   nz= ................ number of samples in 1st dimension (z)",
"   nx= ................ number of samples in 2nd dimension (x)",
"   ny= ................ number of samples in 3rd dimension (y)",
"   dz= ................ spacing (m) of 1st dimension (z)",
"   dx= ................ spacing (m) of 2nd dimension (x)",
"   dy= ................ spacing (m) of 3rd dimension (y)",
"  ",
" Optional parameters:",
" ",
"   opend=0 ................ OpendTect flag, =1 fill extra header values, = 0 (default) fills only the minimum for fdelmodc",
"  ",
" If no ny is provided, a it assumes a 2D model input.",
" Filled header parameters (for a complete list, please check segy.h):",
" hdr.ns	-> nz",
" hdr.d1	-> dz",
" hdr.n2	-> nx",
" hdr.d2	-> dx",
" hdr.gx	-> (int) ix*dx*1000 . x distance from origin in meters*1000",
" hdr.gy	-> (int) iy*dy*1000 . y distance from origin in meters*1000",
" hdr.scalco	-> -1000. Factor to correct gx, gy", 
" hdr.trid	-> TRID_DEPTH (=130). Standard to read vertical data",
" hdr.ntr	-> nx*ny",
" ",
" OpendTect extra header variables (needs 1-based indexing):",
" hdr.cdp	-> x-index in samples (1 to nx)",
" hdr.fldr	-> y-index in samples (1 to ny)",
" hdr.sx	-> x-index in meters (ix+1)*dx",
" hdr.sy	-> y-index in meters (iy+1)*dy",
" ",
" ",
" Due to compatibility reasons gx and gy are integers. They are multiplied by 1000 to preserve decimal places.",
" hdr.scalco = 1000 can be used to convert gx and gy back to meters.",
" ",
"      Author 2018",
"      Institution",
"      E-mail: email@domain.com ",
"  ",
NULL};
/**************** end self doc ***********************************/



void bin2su(int nz, int nx, int ny, float dz, float dx, float dy, char *inName, char *outName, int odtkey){
/*
	First version, improve later.
	Substitute for(ix..) with while loop
	Check bounds, use assert
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
	hdr.scalco = -1000;
	
	fpin = fopen(inName, "r");
	fpout = fopen(outName, "w");

	for(iy=0; iy<ny; iy++){
		for(ix=0; ix<nx; ix++){
			// Set header for current "trace"
			hdr.gx = (int) ix*dx*1000;
			hdr.gy = (int) iy*dy*1000;
	
			if(odtkey){
				//hdr.dt = dz*1000000;
				/*hdr.dt = 4000;
				hdr.tracl = ix+1;
				hdr.tracr = iy*nx+ix+1;
				
				hdr.trid=1;
				hdr.counit=1;*/

				hdr.cdp = ix+1;			
				hdr.fldr = iy+1;
				hdr.sx = (int) (ix+1)*dx*1000;
				hdr.sy = (int) (iy+1)*dy*1000;	
			} 			 			
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
	int key3D=1, odtkey;

// GET INPUT PARAMETERS ///////////////////////////////////////////////////////
	if( !getparint("nz", &nz) ) err("No nz. Exiting.\n");
	if( !getparint("nx", &nx) ) err("No nx. Exiting.\n");
	if( !getparint("ny", &ny) ) { ny = 1; key3D=0; };
	if( !getparint("opendt", &odtkey) ) odtkey = 0;
	if( !getparfloat("dz", &dz) ) err("No dz. Exiting.\n");
	if( !getparfloat("dx", &dx) ) err("No dx. Exiting.\n");
	if( !getparfloat("dy", &dy) ) dy = 0.0;
	if( !getparstring("binmodel", &inName) ) err("No binmodel file name provided. Exiting.");
	if( !getparstring("sumodel", &outName) ) err("No sumodel file name provided. Exiting.");
	

	//printf("CHECK: nz=%d \n nx=%d \n ny=%d dz=%f \n dx=%f \n dy=%f \n binmodel=%s \n sumodel=%s \n", nz, nx, ny, dz, dx, dy, inName, outName);	

	if(key3D){
		printf("3D binary model provided.\n");
		printf("Putting headers on %s, saving result on %s.\n", inName, outName);
		printf(" nz=%d \n nx=%d \n ny=%d \n dz=%f \n dx=%f \n dy=%f\n ", nz, nx, ny, dz, dx, dy);	
	}else{
		printf("2D binary model provided.\n");
		printf("Putting headers on %s, saving result on %s.\n", inName, outName);
		printf(" nz=%d \n nx=%d \n ny=%d \n dz=%f \n dx=%f \n dy=%f\n", nz, nx, ny, dz, dx, dy);	
	}

// PROCESS DATA ///////////////////////////////////////////////////////////////
	bin2su(nz, nx, ny, dz, dx, dy, inName, outName, odtkey);

// FREE VARIABLES /////////////////////////////////////////////////////////////
	
// END MAIN ///////////////////////////////////////////////////////////////////
	return 0;
}








