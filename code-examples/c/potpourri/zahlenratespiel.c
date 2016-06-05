#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	// Initialisiere die Randomizefunktion mit
	// dem jetzigen time-Wert
	srand( (unsigned) time(NULL) );

	int ratezahl, count=0, erraten=0;
	
	// Zufallszahl zwischen 1 und 10
	int zufall = rand() % 10 + 1;

	do {
		printf("Zahleingabe bitte (1-10): ");
		scanf("%d", &ratezahl);
		if(ratezahl==zufall) {  
			erraten=1;
			count++;
		}
		else {
			(ratezahl > zufall) ?
				printf("kleiner\n") : printf("groesser\n");
			count++;
		}
	} while( (erraten != 1) && (count != 3) );

	if(erraten == 0) {
		printf("Sie haben 3 Chancen vertan ;) \n");
		printf("Die Zahl waere %d gewesen: \n", zufall);
	}
	else
		printf("Mit %d Versuchen erraten!\n",count);


	return EXIT_SUCCESS;
}
