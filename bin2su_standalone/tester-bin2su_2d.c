/*
HOW TO COMPILE (need SU installed):
gcc -c bin2su_2d.c -I$CWPROOT/include
gcc bin2su_2d.o -o bin2su_2d.exe -L$CWPROOT/lib -lsu -lpar -lcwp

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

#define TRCBYTES                240

#include "bin2su_2d.h"


/*********************** self documentation **********************/
char *sdoc[] = {
"  ",
" MODULE - Quick description of the module",
"  ",
" ./module required_par1= required_par2= [optional parameters]",
"  ",
" Required parameters:",
" ",
"   required_par1= ................ quick description",
"   required_par2= ................ quick description",
"  ",
" Optional parameters:",
" ",
"   opt_par1=defaultVal1 ................. quick description",
"   opt_par2=defaultVal2 ................. quick description",
" ",
"      Author 2018",
"      Institution",
"      E-mail: email@domain.com ",
"  ",
NULL};
/**************** end self doc ***********************************/


int main(int argc, char *argv[]){
//CHECK CORRECT USAGE OF INPUT PARAMETERS /////////////////////////////////////

	initargs(argc, argv);
	requestdoc(0);

	if(argc!=7){
		printf("Incorrect usage of input parameters. Exiting.\n");
		printf("Correct use is:\n/bin2su_2d.exe nz nx dz dx in.bin out.su\n");
		printf("Ex:\n../tester-bin2su_2d.exe nz nx dz dx vel250x767.bin vel250x767.su\n");
		exit(0);	
	}

	
// DECLARE VARIABLES //////////////////////////////////////////////////////////
	int nz, nx;
	float dz, dx;
	//char inName[400], outName[400];
	char *inName, *outName;

// GET INPUT PARAMETERS ///////////////////////////////////////////////////////
/*	nz = atoi(argv[1]);*/
/*	nx = atoi(argv[2]);*/
/*	dz = atof(argv[3]);*/
/*	dx = atof(argv[4]);*/
/*	strcpy(inName, argv[5]);*/
/*	strcpy(outName, argv[6]);*/
	if( !getparint("nz", &nz) ) err("No nz provided. Exiting.");
	if( !getparint("nx", &nx) ) err("No nx provided. Exiting.");
	if( !getparfloat("dz", &dz) ) err("No dz provided. Exiting.");
	if( !getparfloat("dx", &dx) ) err("No dx provided. Exiting.");
	if( !getparstring("binfield", &inName) ) err("No binfield provided. Exiting.");
	if( !getparstring("sufield", &outName) ) err("No sufield name provided. Exiting.");
	
	printf("CHECK: nz=%d \n nx=%d \n dz=%f \n dx=%f \n binfield=%s \n sufield=%s \n", nz, nx, dz, dx, inName, outName);

// PROCESS DATA ///////////////////////////////////////////////////////////////
	bin2su_2d(nz, nx, dz, dx, inName, outName);

// FREE VARIABLES /////////////////////////////////////////////////////////////
	
// END MAIN ///////////////////////////////////////////////////////////////////
	return 0;
}











