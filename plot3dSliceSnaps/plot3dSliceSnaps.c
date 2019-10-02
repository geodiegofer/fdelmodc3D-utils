#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	printf("------- fdelmodc3D-utils repo's plot3dSliceSnaps --------\n");
	printf("Slices a 3D snapscube binary in one of 3 dimensions (z,x,y) producing a 2D snapcube in the selected slice. ");
	printf("Slicing is done by specifying a dimension and a factor 'fac'. The maximum of selected dim is multiplied by fac,");
	printf("therefore fac must be <1.\n\n");
	printf("Usage: ./plot3dSliceSnaps.exe nz nx ny slicedim fac snaps.bin\n\n");
	// Check IO
	if(argc!=1+6){
		printf("Incorrect usage of input parameters. Exiting.\n");
		exit(0);	
	}

	// Declare
	int nz, nx, ny, nt, ntotal, n1, n2, n3;
	int iz, ix, iy, it;
	float *slice;
	float fac;
	int pos, islice;
	char title[300];
	FILE *fpin, *fpout;
	
	// Get dimensions
	nz = atoi(argv[1]);
	nx = atoi(argv[2]);
	ny = atoi(argv[3]);
	fac = atof(argv[5]);

	fpin = fopen(argv[6], "r");

	fseek(fpin, 0, SEEK_END);
	ntotal = ftell(fpin);
	rewind(fpin);
	printf("nz=%d nx=%d ny=%d \n", nz, nx, ny);
	nt = ntotal/(nz*nx*ny*sizeof(float));
	printf("ntotal = %d ntotal/(nz*nx*ny)=%d\n", ntotal, nt);

	fpout = fopen("tmp.bin", "w");
	if(strstr(argv[4],"y")){
		n1 = nz;
		n2 = nx;
		n3 = ny;
		
		printf("y slice\n");
		slice = (float*)malloc(nz*nx*sizeof(float));
		pos = ny*fac;
		assert(ftell(fpin)==0);
		
		// Pad beginning of snapscube with 0's, nimage bug
		memset(slice, 0, nz*nx*sizeof(float));
		fwrite(slice, nz*nx, sizeof(float), fpout);
		
		// Offset to 1st slice position
		fseek(fpin, nz*nx*pos*sizeof(float), SEEK_CUR);		
		
		// Now we only have to take nz*nx*islice steps, then save a zx-slice
		islice=0;
		while(islice != nt){			
			fread(slice, nz*nx, sizeof(float), fpin);
			fwrite(slice, nz*nx, sizeof(float), fpout);
			fseek(fpin, nz*nx*(ny-1)*sizeof(float), SEEK_CUR); //-1 to account fread's mispositioning of nz*nx samples
			
			islice++;
		}
		// Pad last snap with zeros	
		memset(slice,0,n1*n2*sizeof(float));
		fwrite(slice, n1*n2, sizeof(float), fpout);

	}else if(strstr(argv[4],"x")){
		n1 = nz;
		n2 = ny;
		n3 = nx;
		
		printf("x slice\n");
		slice = (float*)malloc(nz*ny*sizeof(float));	
		pos = nx*fac;
		assert(ftell(fpin)==0);

		memset(slice,0,n1*n2*sizeof(float));
		fwrite(slice, n1*n2, sizeof(float), fpout);
		
		// Offset fpin to pos*nz
		fseek(fpin, pos*nz*sizeof(float), SEEK_CUR);
		
		islice=0;
		while(islice != ny*nt){
			fread(slice, nz, sizeof(float), fpin);
			fwrite(slice, nz, sizeof(float), fpout);
			fseek(fpin, nz*(nx-1)*sizeof(float), SEEK_CUR); //-1 to account fread's mispositioning of nz samples
						
			islice++;
		}
		memset(slice,0,n1*n2*sizeof(float));
		fwrite(slice, n1*n2, sizeof(float), fpout);
		
	}else if(strstr(argv[4],"z")){
		n1 = nx;
		n2 = ny;
		n3 = nz;
		printf("z slice\n");
		slice = (float*)malloc(nx*ny*sizeof(float));	
		pos = nz*fac;
		assert(ftell(fpin)==0);

		// 0-pad first slice to account for nimage's bug
		memset(slice,0,n1*n2*sizeof(float));
		fwrite(slice, n1*n2, sizeof(float), fpout);
		
		// Set z-slice position on first xz-slice
		fseek(fpin, pos*sizeof(float), SEEK_CUR);

		// No contiguity, must do point by point		
		for(iy=0; iy<ny*nt; iy++){
			
			for(ix=0; ix<nx; ix++){
				fread(slice, 1, sizeof(float), fpin);
				fwrite(slice, 1, sizeof(float), fpout);
				fseek(fpin, (nz-1)*sizeof(float), SEEK_CUR); //-1 to account fread's mispositioning of 1 sample
			}
			
		}
		// 0-pad last slice to account for nimage's bug
		memset(slice,0,n1*n2*sizeof(float));
		fwrite(slice, n1*n2, sizeof(float), fpout);
	}else{
		printf("Invalid slice option, exiting. Valid options: 'z' 'x' 'y'\n");
	}
	// Alloc
	
	// Init
	
	// Do stuff
	sprintf(title, "%s %d-th slice (1st and last snaps zero-padded)", argv[4], pos);
	char nimagecall[400];
	sprintf(nimagecall, "nimage n1=%d n2=%d <tmp.bin title='%s' perc=99 &", n1, n2, title);
	
	system(nimagecall);
	system("rm tmp.bin");
	
/*	system("/bin/pwd");*/
/*	system("ximage n1=64 <test.bin &");*/
	
	// Free
	fclose(fpin);
	fclose(fpout);
	free(slice);

	printf("WARNING!!! Padded snapcube with 0-slice on the beginning and end due to nimage bugging on these slices.\n");
	
	// End
	return 0;	
}

