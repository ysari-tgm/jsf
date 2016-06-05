#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {

	int i = 0;

	srand((unsigned int)time(NULL));

	for(i=0; i<100; i++) {
		printf("Zufallszahl: %d\n", rand()%10000);
	}

	return EXIT_SUCCESS;
}
