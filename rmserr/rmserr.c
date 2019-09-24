#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]){
	// Check IO
	if(argc!=(1+2)){
		printf("fdelmodc3D utils rmserr\nPrints sum of rms err between 2 files\nIncorrect usage of input parameters. Exiting.\n");
		printf("Usage: \n");
		printf("%s file1.bin file2.bin\n", argv[0]);
		exit(0);	
	}

	// Declare
	double rmserr = 0.0;
	int count = 0;
	FILE *fp1, *fp2;
	float fl1, fl2;
	// Get dimensions
	
	// Alloc
	
	// Init
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	
	
	while( fread(&fl1, 1, sizeof(float), fp1) ){
		fread(&fl2, 1, sizeof(float), fp2);
		rmserr += (fl1 - fl2)*(fl1 - fl2);
		count ++;
	}
	rmserr /= count;
	rmserr = sqrt(rmserr);
	
	printf("fdelmodc3D utils's -- rmserr\n");
	printf("rmserr between %s and %s is: %.6e\n", argv[1], argv[2], rmserr);
	// Do stuff
	
	// Free
	fclose(fp1);
	fclose(fp2);
	
	// End
	return 0;	
}

