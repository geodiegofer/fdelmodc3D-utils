#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "su.h"
#include "par.h"

// SU header read/write*/
#include "segy.h"
//#define TRCBYTES                240		//SU-header size

/*********************** self documentation **********************/
char *sdoc[] = {
"  ",
" vel2rho - Creates density model from a velocity model",
"  ",
" ./vel2rho.exe nsamp= velfile= rhofile= ",
"  ",
" Required parameters:",
" ",
"   nsamp= ................ total number samples in the model",
"   velfile= .............. file name of input 2d velocity field",
"   rhofile= .............. file name of output 2d density field",
"  ",
" ",
" Creates binary density model from a binary velocity model using Gardner's relation. ",
" Velocity values must be in [m/s] in order for densities to be in [kg/m3]. ",
" ",
"      Author 2018",
"      Institution",
"      E-mail: email@domain.com ",
"  ",
NULL};
/**************** end self doc ***********************************/


int main(int argc, char *argv[]){
	// Init SU selfdoc and IO
	initargs(argc, argv);
	requestdoc(0);

	// Declare variables
	int i, nsamp;
	float *vel, *rho;
	FILE *fpin, *fpout;
	char *velname, *rhoname;


	// Get input/output parameters
	if( !getparint("nsamp", &nsamp) ) err("No nsamp. Exiting.\n");
	if( !getparstring("velfile", &velname) ) err("No velfile provided. Exiting.\n");
	if( !getparstring("rhofile", &rhoname) ) err("No rhofile provided. Exiting.\n");

	// Allocate data
	vel = (float*)malloc(nsamp*sizeof(float));
	rho = (float*)malloc(nsamp*sizeof(float));

	// Read input files
	fpin = fopen(velname, "r");
	fread(vel, nsamp, sizeof(float), fpin);
	fclose(fpin);

	// Process data
	// Uses gardner: https://en.wikipedia.org/wiki/Gardner%27s_relation
	for(i=0; i<nsamp; i++){
		rho[i] = 1000*0.31*pow(vel[i], 0.25);
	}
	printf("Created %s from velfield %s.\n", rhoname, velname);

	// Write output data	
	fpout = fopen(rhoname, "w");
	fwrite(rho, nsamp, sizeof(float), fpout);
	fclose(fpout);

	// Free variables
	free(vel);
	free(rho);

	return 0;
}

