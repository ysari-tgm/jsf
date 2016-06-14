#include <stdio.h>
#include <stdlib.h>

void callstatic(void);

int main (int argc, char** argv)
{
	int i;

	for(i=0;i<10;i++) callstatic();

	return EXIT_SUCCESS;
}

void callstatic(void)
{
	int static s = 0;
	int i;

	for(i=0; i<2; i++)
	{
		int static t = 0;
		printf("\ns: %d, t: %d",s,t);
		t++;
	}
	s++;
}
