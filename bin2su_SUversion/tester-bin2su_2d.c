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

#include "su.h"
#include "segy.h"
#include "par.h"

#define TRCBYTES                240

#include "bin2su_2d.h"

int main(int argc, char *argv[]){
//CHECK CORRECT USAGE OF INPUT PARAMETERS /////////////////////////////////////

	if(argc!=7){
		printf("Incorrect usage of input parameters. Exiting.\n");
		printf("Correct use is:\n/bin2su_2d.exe nz nx dz dx in.bin out.su\n");
		printf("Ex:\n../bin2su_2d.exe nz nx dz dx vel250x767.bin vel250x767.su\n");
		exit(0);	
	}

	
// DECLARE VARIABLES //////////////////////////////////////////////////////////
	int nz, nx, dz, dx;
	char inName[400], outName[400];

// GET INPUT PARAMETERS ///////////////////////////////////////////////////////
	nz = atoi(argv[1]);
	nx = atoi(argv[2]);
	dz = atof(argv[3]);
	dx = atof(argv[4]);
	strcpy(inName, argv[5]);
	strcpy(outName, argv[6]);

// PROCESS DATA ///////////////////////////////////////////////////////////////
	bin2su_2d(nz, nx, dz, dx, inName, outName);

// FREE VARIABLES /////////////////////////////////////////////////////////////
	
// END MAIN ///////////////////////////////////////////////////////////////////
	return 0;
}











