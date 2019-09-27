#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double rmserr2filesF(FILE *fp1, FILE *fp2){
	float fl1, fl2;
	int stride = sizeof(float);
	double rmserr;
	int count = 0;

	while( fread(&fl1, 1, stride, fp1) ){
		fread(&fl2, 1, stride, fp2);
		rmserr += (fl1 - fl2)*(fl1 - fl2);
		count ++;
	}
	rmserr /= count;
	rmserr = sqrt(rmserr);

	return rmserr;
}

double rmserr2filesD(FILE *fp1, FILE *fp2){
	double fl1, fl2;
	int stride = sizeof(double);
	double rmserr;
	int count = 0;
	
	while( fread(&fl1, 1, stride, fp1) ){
		fread(&fl2, 1, stride, fp2);
		rmserr += (fl1 - fl2)*(fl1 - fl2);
		count ++;
	}
	rmserr /= count;
	rmserr = sqrt(rmserr);

	return rmserr;
}

double rmserr2filesI(FILE *fp1, FILE *fp2){
	int fl1, fl2;
	int stride = sizeof(int);
	double rmserr;
	int count = 0;
	
	while( fread(&fl1, 1, stride, fp1) ){
		fread(&fl2, 1, stride, fp2);
		rmserr += (fl1 - fl2)*(fl1 - fl2);
		count ++;
	}
	rmserr /= count;
	rmserr = sqrt(rmserr);

	return rmserr;
}

int main(int argc, char *argv[]){
	// Check IO
	if(argc!=(1+3)){
		printf("fdelmodc3D utils rmserr\nPrints sum of rms err between 2 files\nIncorrect usage of input parameters. Exiting.\n");
		printf("Usage: \n");
		printf("%s file1.bin file2.bin precision\n", argv[0]);
		printf("Example: \n");
		printf("%s file1.bin file2.bin double\n", argv[0]);

		exit(0);	
	}

	// Declare
	double rmserr = 0.0;
	int count = 0;
	FILE *fp1, *fp2;
	double fl1, fl2;
	int stride;
	
	// Get dimensions
	
	// Alloc
	
	// Init
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");

	if(strstr(argv[3],"int")){
		rmserr = rmserr2filesI(fp1, fp2);
	}else if(strstr(argv[3],"float")){
		rmserr = rmserr2filesF(fp1, fp2);
	}else if(strstr(argv[3],"double")){
		rmserr = rmserr2filesD(fp1, fp2);
	}
	
	printf("fdelmodc3D utils's -- rmserr\n");
	printf("rmserr between %s and %s is: %.6e\n", argv[1], argv[2], rmserr);
	// Do stuff
	
	// Free
	fclose(fp1);
	fclose(fp2);
	
	// End
	return 0;	
}

