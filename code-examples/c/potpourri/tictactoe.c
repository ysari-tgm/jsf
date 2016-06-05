#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#define clrscr() system("clear")
#elif __BORLANDC__ && __MSDOS__
#include <conio.h>
#elif __WIN32__ || _MSC_VER
#define clrscr() system("cls")
#else
#define clrscr() printf("clrscr() - Fehler!!\n")
#endif

typedef struct
{
	char name[255];
	char zeichen;
} SPIELER;

typedef struct {
	SPIELER s1;
	SPIELER s2;
	SPIELER gewinner;
	char feld[3][3];
	char aktuell;
} SPIEL;

void initFeld(SPIEL*);
void printSpielfeld(SPIEL*);
void neuerZug(SPIEL*);
int hatGewonnen(SPIEL*);

int main(int argc, const char * argv[])
{
	SPIEL spiel;

	printf("Name fuer Spieler 1: ");
	scanf("%s", spiel.s1.name);
	getchar();
	
	printf("Name fuer Spieler 2: ");
	scanf("%s", spiel.s2.name);
	getchar();
	
	printf("Zeichen fuer Spieler 1: ");
	scanf("%c", &spiel.s1.zeichen);
	getchar();
	
	printf("Zeichen fuer Spieler 2: ");
	scanf("%c", &spiel.s2.zeichen);
	getchar();
	
	/* teste ob zeichen gleich sind */
	if(spiel.s1.zeichen == spiel.s2.zeichen)
	{
		if(spiel.s1.zeichen != 'X') spiel.s2.zeichen = 'X';
		else spiel.s2.zeichen = 'O';
	}
	
	initFeld(&spiel);
	clrscr();

	do
	{
		if(spiel.aktuell == spiel.s1.zeichen) spiel.aktuell = spiel.s2.zeichen;
		else spiel.aktuell = spiel.s1.zeichen;
		printSpielfeld(&spiel);
		neuerZug(&spiel);
		
		clrscr();
	}
	while(!hatGewonnen(&spiel));
	
	if(&spiel.gewinner)
		printf("Spieler %s hat gewonnen!!!",spiel.gewinner.name);
	else
		printf("Leider ein Unentschieden!");
	
	return EXIT_SUCCESS;
}

void initFeld(SPIEL* spiel)
{
	int hor, ver;
	
	for(ver=0; ver<3; ver++)
	{
		for(hor=0; hor<3; hor++)
		{
			spiel->feld[ver][hor] = ' ';
		}
	}
}

void printSpielfeld(SPIEL* spiel)
{
	int hor, ver;
	
	for(ver=0; ver<3; ver++)
	{
		printf("+-+-+-+\n");
		
		for(hor=0; hor<3; hor++)
		{
			printf("|%c", spiel->feld[ver][hor]);
		}
		printf("|\n");
	}
	
	printf("+-+-+-+\n");
}

void neuerZug(SPIEL* spiel)
{
	int x, y;
	
	while(1)
	{
		printf("Zug fuer '%c':\n", spiel->aktuell);
		printf("Zeile: ");
		scanf("%i", &x);
		
		printf("Spalte: ");
		scanf("%i", &y);
		
		if((x>0 && x<4) && (y>0 && y<4) && (spiel->feld[x-1][y-1] == ' ')) break;
		
		printf("Koordinaten falsch!\n");
	}
	
	spiel->feld[x-1][y-1] = spiel->aktuell;
}

int hatGewonnen(SPIEL* spiel)
{
	int i, gewonnen = 0;
	char zeichen = spiel->aktuell;

	/* teste horizontal */
	for(i=0; i<3; i++)
	{
		if(spiel->feld[i][0] == zeichen && 
		   spiel->feld[i][1] == zeichen && 
		   spiel->feld[i][2] == zeichen)
		gewonnen = 1;
	}
	
	/* teste vertikal */
	for(i=0; i<3; i++)
	{
		if(spiel->feld[0][i] == zeichen && 
		   spiel->feld[1][i] == zeichen && 
		   spiel->feld[2][i] == zeichen)
		gewonnen = 1;
	}
	
	/* teste schief */
	if(spiel->feld[0][0] == zeichen &&
	   spiel->feld[1][1] == zeichen && 
	   spiel->feld[2][2] == zeichen)
		gewonnen = 1;

	if(spiel->feld[0][2] == zeichen &&
	   spiel->feld[1][1] == zeichen && 
	   spiel->feld[2][0] == zeichen)
		gewonnen = 1;

	if(gewonnen) {
		if(spiel->s1.zeichen == zeichen)
			spiel->gewinner = spiel->s1;
		else
			spiel->gewinner = spiel->s2;
	}
	
	return gewonnen;
}
