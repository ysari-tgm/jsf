#include "stdio.h"
//#include "math.h"
float squrt(float);

int main(void) {
	// Disable stdout buffering
	setvbuf(stdout, NULL, _IONBF, 0);

	/* Deklaration der Variablen der Gleichung */
	int a, b, c;
	/* Deklaration der Variable fuer die Ergebnisse */
	float x1, x2;

	/* Ausgabe "Begrüßung" */
	printf("Berechnung quadratischer Zahlen\n");

	do {
		/* Ausgabe "Bitte a,b,c eingeben" */
		printf("Form der quadratischen Gleichung:\n");
		printf("a*x^2 + b*x + c == 0\n\n");
		printf("Bitte die Parameter a, b, c eingeben.\n");

		/* Eingabe a */
		printf("Parameter a: ");
		scanf("%d", &a);

		// Eingabe b
		printf("Parameter b: ");
		scanf("%d", &b);

		// Eingabe c
		printf("Parameter c: ");
		scanf("%d", &c);

		printf("\nBerechnet wird:\n");
		printf("%d*x^2 + %d*x + %d == 0\n\n", a, b, c);

		// Überprüfung 1. Sonderfall: a==0
		if ( a == 0 ) {
			// Ja -> Berechnung: x = - c / b
			x1 = - (float)c / (float)b;
			printf("Das Ergebnis ist %f.\n\n", x1);
		} else {
			// Nein -> Prüfe 2. Sonderfall:  Wurzel == 0
			float wurzel;
			// Berechnung von "dem was unter der Wurzel steht"
			wurzel = b*b - 4*a*c;

			if ( wurzel == 0 ) {
				// Ja -> Berechnung: x = - b / 2a
				x1 = - (float)b / 2.0*a;
				printf("Das Ergebnis ist %f.\n\n", x1);
			} else {
				// Nein -> Prüfe 3. Sonderfall: Wurzel < 0
				if ( wurzel < 0 ) {
					// Ja -> Berechnung: x1,2 = -b/2a +/- j squrt(4ac-b*b)/2a
				} else {
					// Nein -> Berechnung: x1,2 = ( -b +/- squrt(b*b-4ac) ) / 2a
					x1 = ( - (float)b + squrt(wurzel) ) / ( 2.0 * a );
					x2 = ( - (float)b - squrt(wurzel) ) / ( 2.0 * a );
					// squrt = Square Root = Quadratwurzel, def. in math.h
					printf("Das 1. Ergebnis ist %f.\n", x1);
					printf("Das 2. Ergebnis ist %f.\n", x2);
				}
			}
		}
		/*Eingabe "Wiederholung?"*/

	} while( a==0 /*solange Wiederholung erwünscht*/);

	return 0;
}

/* 
 * Babylonian method for square root
 * Returns the square root of n.
 *
 * Source: http://www.geeksforgeeks.org/square-root-of-a-perfect-square/
 */
float squrt(float n)
{
	/*We are using n itself as initial approximation
	 *    This can definitely be improved */
	float x = n;
	float y = 1;
	float e = 0.000001; /* e decides the accuracy level*/
	while(x - y > e)
	{
		x = (x + y)/2;
		y = n/x;
	}
	return x;
}
