#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE *fp;
	char *fname = "comma.csv";
	//char str1[10];
	//char str2[10];
	char* str1 = malloc(10 * sizeof(char));
	char* str2 = malloc(100 * sizeof(char));
	int ret, n1, n2;
	float f1, f2;

	if(argc == 2) fname = argv[1];
	fp = fopen( fname, "r" );
	if( fp == NULL ){
		printf( "\n%s not available!\n", fname );
		return EXIT_FAILURE;
	}

	while( fscanf( fp, "%[^','],%[^','],%d,%d,%f,%f\n", str1, str2, &n1, &n2, &f1, &f2 ) != EOF ) {
		fprintf( stdout, "%s %s %d %d %.2f %.2f\n", str1, str2, n1, n2, f1, f2 );
	}

	fclose( fp );

	return EXIT_SUCCESS;
}
