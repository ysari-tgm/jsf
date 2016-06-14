#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int i=0;
	// Initialisiere die Randomizefunktion mit
	// dem jetzigen time-Wert
	time_t now = time(NULL);
	if ( argc == 2 ) {
		srand( (unsigned) now * atoi(argv[1]) );
		printf("Init mit Zeit %d multipliziert mit %d\n",(int)now,atoi(argv[1]));
	}

	do {
		printf("Zufallszahl: %d\n",rand());
		i++;
	} while (1);

	return EXIT_SUCCESS;
}
