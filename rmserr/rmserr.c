#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Taken from ZFP library
https://github.com/LLNL/zfp
*/
/* compute and print reconstruction error */
static void
test_error(const void* fin, const void* fout, char *vartype)
{
	const float* f32i;
	const double* f64i;
	const float* f32o;
	const double* f64o;
	double fmin = +DBL_MAX;
	double fmax = -DBL_MAX;
	double erms = 0;
	double ermsn = 0;
	double emax = 0;
	double psnr = 0;
	size_t i;

	int stride;

	if( strstr(vartype,"float") ){
		stride = sizeof(float);
	}else if ( strstr(vartype,"double") ){
		stride = sizeof(double);
	}else{
		printf("rmserr's print_error Invalid vartype. Exiting.\n");
		exit(0);
	}


	while( fread(&fl1, 1, stride, fp1) ){
		fread(&fl2, 1, stride, fp2);
		erms += (double)(fl1 - fl2)*(fl1 - fl2);
		count ++;
		
		emax = MAX(emax, d);
		erms += d * d;
		fmin = MIN(fmin, val);
		fmax = MAX(fmax, val);
	}

	erms = sqrt(erms / n);
	ermsn = erms / (fmax - fmin);
	psnr = 20 * log10((fmax - fmin) / (2 * erms));
	fprintf(stderr, " rmse=%.4g nrmse=%.4g maxe=%.4g psnr=%.2f", erms, ermsn, emax, psnr);
}


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
	
	printf("Testing ZFP's print_error.\n");
	test_error(fp1, fp2, argv[3]);
	
	// Do stuff
	
	// Free
	fclose(fp1);
	fclose(fp2);
	
	// End
	return 0;	
}

