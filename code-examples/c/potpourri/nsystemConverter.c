#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define ZAHLENSYSTEM 3
#define MAX_EINGABE 128

// Prototypen der verwendeten Funktionen
int hex2int(int);
void chomp(char*);
int auswaehlen(char*);
void eingeben(int, char*);
unsigned long int umrechnen(int, char*);
void umrechnung(int, char*);

// main Funktion
int main(int argc, char** argv)
{
	char * zahlenSystem = malloc(ZAHLENSYSTEM*sizeof(char));
	char * eingabe = malloc(MAX_EINGABE*sizeof(char));
	int basis, stellen;
	unsigned long int ausgabe=0;

	// Uepruefen, ob genuegend Speicherplatz vorhanden
	if( zahlenSystem == NULL || eingabe == NULL )
	{
		printf("Kein Platz im Heap! ;(");
		return EXIT_FAILURE;
	}

	// Information fuer Benutzer
	printf("\nZahlensystemkonverter");
	printf("\n=====================\n");

	// Eingabe des gewuenschten Zahlensystems und Zuordnung der Basis
	basis = auswaehlen(zahlenSystem);

	// Information fuer Benutzer
	printf("Sie haben %c mit der Basis %d gewaehlt.\n", zahlenSystem[0], basis);

	// Eingabe der Zahl und Ueberpruefung auf Grenzen und Gueltigkeit
	eingeben(basis, eingabe);

	// Berechnung der dezimalen Zahl
	ausgabe = umrechnen(basis, eingabe);

	// Ausgabe der berechneten Zahl
	printf("\nDie Dezimalzahl zu %s(%c) lautet: %lu\n\n", strtok(eingabe, "\n"), *zahlenSystem, ausgabe);

	umrechnung(basis, eingabe);

	if(zahlenSystem) free(zahlenSystem);
	if(eingabe) free(eingabe);

	return EXIT_SUCCESS;
}

int hex2int(int c)
{
	char hexalpha[] = "aAbBcCdDeEfF";
	int i;
	int answer = 0;

	for(i = 0; answer == 0 && hexalpha[i] != '\0'; i++)
	{
		if((hexalpha[i] - '0') == c)
		{
			answer = 10 + (i / 2);
		}
	}
	return answer;
}

void chomp(char *str) {
	size_t p=strlen(str);
	// '\n' mit '\0' ueberschreiben
	str[p-1]='\0';
}

int auswaehlen(char* zahlenSystem)
{
	int basis = 0;

	do
	{
		printf("\nWaehlen Sie bitte aus folgenden Zahlensystemen:\n\n");
		printf("Binaer\t\t... b\n");
		printf("Oktal\t\t... o\n");
		printf("Dezimal\t\t... d\n");
		printf("Hexadezimal\t... h\n");

		fgets(zahlenSystem, ZAHLENSYSTEM, stdin);
		chomp(zahlenSystem);

		switch (zahlenSystem[0])
		{
			case 'b': basis = 2; break;
			case 'o': basis = 8; break;
			case 'd': basis = 10; break;
			case 'h': basis = 16; break;
			default: printf("Falsche Eingabe!");
		}
	} while ( zahlenSystem[0] != 'b' && zahlenSystem[0] != 'o' 
			&& zahlenSystem[0] != 'd' && zahlenSystem[0] != 'h' );

	return basis;
}

void eingeben(int basis, char* eingabe)
{
	int digit_error, range_error, i;
	char hex_digits[23] = "0123456789aAbBcCdDeEfF";

	do
	{
		printf("Bitte geben Sie die gewuenschte Zahl ein:\n");
		fgets(eingabe, MAX_EINGABE, stdin);
		chomp(eingabe);

		digit_error=0;
		switch (basis)
		{
			case 2: 
				for ( i=0; eingabe[i] != '\0'; i++ ) 
					if( eingabe[i] != '1' && eingabe[i] != '0' ) 
						digit_error=1; 
				break;
			case 8:
				for ( i=0; eingabe[i] != '\0'; i++ )
					if( !isdigit(eingabe[i]) || eingabe[i] == '8' || eingabe[i] == '9' )
						digit_error=1;
				break;
			case 10:
				for ( i=0; eingabe[i] != '\0'; i++ )
					if( !isdigit(eingabe[i]) )
						digit_error=1;
				break;
			case 16:
				for ( i=0; eingabe[i] != '\0'; i++ )
					if( !isxdigit(eingabe[i]) )
						digit_error=1;
				break;
		}
		if(digit_error) printf("Bitte nur Zahlen der Basis %d eingeben! ",basis);

		range_error=0;
		switch (basis)
		{
			case 2: 
				// anzahl der stellen sind jeweils ein bit, also sizeof(usigned long int)*8 muss kleiner gleich sein
				if ( strlen(eingabe) > sizeof(unsigned long int)*8 ) range_error=1;
				break;
			case 8:
				// maximum ist 1777777777777777777777 (1 mit 21 7er, sprich 22 stellen); 64/3=21
				printf("size: %d\n",(int) sizeof(unsigned long int)*8/3 );
				if ( (strlen(eingabe) > ((int)sizeof(unsigned long int)*8/3)+1) 
						|| (strlen(eingabe) == ((int)sizeof(unsigned long int)*8/3)+1 && eingabe[0] != '1'))  range_error=1;
				break;
			case 10:
				if ( strlen(eingabe) > 20 ) range_error=1;
				printf("Ergebnis koennte verfaelscht sein, da nur ein rudimentaerer Groessentest implementiert ist! ");
				// else if ( eingabe > ULONG_MAX ) range_error=1;
				break;
			case 16: 
				// anzahl der stellen sind jeweils vier bit, also sizeof(usigned long int)*8/4 muss kleiner gleich sein
				if ( strlen(eingabe) > sizeof(unsigned long int)*8/4 ) range_error=1;
				break;
		}
		if(range_error) printf("Eingegebene Zahl der Basis %d ist zu groß! ",basis);

	} while(digit_error || range_error);
}

unsigned long int umrechnen(int basis, char* eingabe)
{
	unsigned long int ausgabe = 0;
	int i, stellen=0;

	for ( i=0; eingabe[i] != '\0'; i++ )
		stellen++;
	printf("Eingabe hat %d Stellen!", stellen);

	for ( i=1; i<= stellen; i++) {
		switch (basis)
		{
			case 16:
				ausgabe += (hex2int((int) eingabe[stellen-i] - '0')) 
					* (unsigned long int) pow(basis,(i-1));
				break;
			default:
				ausgabe += ((int) eingabe[stellen-i] - '0') 
					* (unsigned long int) pow(basis,(i-1));
		}
	}

	return ausgabe;
}

void umrechnung(int basis, char* eingabe)
{
	static unsigned long val;
	char *stop_ptr = NULL;

	val = strtoul(eingabe, &stop_ptr, basis);

	if(errno == ERANGE) {
		printf("Werteueber- bzw. unterlauf!!!\n");
		exit(EXIT_FAILURE);
	}
	if(!val) {
		printf("Wert konnte nicht umgewandelt werden\n");
		exit(EXIT_FAILURE);
	}
	if(*stop_ptr) {
		printf("Kein korrekter long-Wert: %s\n", eingabe);
		printf("Fehler der Umwandlung ab Pos.: %s\n", stop_ptr);
		printf("Umgewandelt ---> %lu\n", val);
	}
	else
		printf("Yeah! Korrekter unsigned long-Wert : %lu\n", val);
}

