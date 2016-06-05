#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XVSM_MAX_CSL 10

typedef struct {
	char ID[20];
	ulong cslstatus;
} struct_XVSMcsl;

void init(void);
struct_XVSMcsl xvsm_csl[XVSM_MAX_CSL];

int main(int argc, char** argv)
{
	FILE *fp;
	char *fname = "CONF.SYS";

	auto char loc[255];
	auto long fpos = 0;
	auto int i;
	auto char* pp;

	init();

	if(argc == 2) fname = argv[1];
	fp = fopen( fname, "r" );
	if( fp == NULL ){
		printf( "\n%s not available!\n", fname );
		return EXIT_FAILURE;
	}

	i=0;
	while( fscanf( fp, "%s\n", loc ) != EOF && i < XVSM_MAX_CSL ) {
		//fprintf( stdout, "%s\n", str1);
		fpos += (long) strlen(loc) + 2; // update seekpos for next read
		printf("%s\n",loc);

		if ((strstr(loc, "CN=")) != NULL) {
			pp = strtok(loc, ";");
			strncpy( (xvsm_csl+i)->ID, pp+strlen("CN="),sizeof(xvsm_csl->ID)-1);
			//printf("%d.ContainerName: %s\n",i+1,pp+strlen("CN="));
			printf("%d.ContainerName: %s\n",i+1,(xvsm_csl+i)->ID);
			pp = strtok(NULL, ";");
			(xvsm_csl+i)->cslstatus = (ulong) atol(pp);
			//printf("%d.ContainerStatus: %d\n",i+1,atoi(pp));
			printf("%d.ContainerStatus: %lu\n",i+1,(xvsm_csl+i)->cslstatus);
			i++;
		}
	}

	fclose( fp );

	return EXIT_SUCCESS;
}

void init() {
	auto int i;
	auto struct_XVSMcsl* csl;
	for (i = 0; i < XVSM_MAX_CSL; i++) {
		csl = &xvsm_csl[i];
		memset(csl, 0, sizeof(struct_XVSMcsl)); // clear all to 0
	}
}
