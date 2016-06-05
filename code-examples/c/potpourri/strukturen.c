#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXMITARBEITER 5

typedef struct
{
	char vorname[128];
	char nachname[128];
	char position[64];
	double einkommen;
} MITARBEITER;

void mitarbeiter_print(MITARBEITER*);

int main(int argc, char** argv)
{
	MITARBEITER mfeld[MAXMITARBEITER];
	int i;

	for(i=0; i<MAXMITARBEITER; i++)
	{
		strcpy(mfeld[i].vorname,"vorname");
		strcpy(mfeld[i].nachname,"nachname");
		strcpy(mfeld[i].position,"position");
		mfeld[i].einkommen = 1200.;
	}

	strcpy(mfeld[MAXMITARBEITER-1].position,"chef");
	mfeld[MAXMITARBEITER-1].einkommen = 4800.;

	strcpy(mfeld->vorname,"Herbert");

	// Uebergabe von Vektor mit Mitarbeitern
	// mfeld == &mfeld[0]
	mitarbeiter_print(mfeld);

	return EXIT_SUCCESS;
}

void mitarbeiter_print(MITARBEITER* mpointer)
{
	int i;

	printf("\nAusgabe von %d Mitarbeitern folgt ...",MAXMITARBEITER);

	for(i=0; i<MAXMITARBEITER; i++)
	{
		printf("\n\n%d. Mitarbeiter:", i+1);
		printf("\nVorname: %s", (mpointer+i)->vorname);
		printf("\nNachname: %s", mpointer[i].nachname);
		printf("\nPosition: %s", mpointer[i].position);
		printf("\nEinkommen: %lf", (*(mpointer+i)).einkommen);
	}

	printf("\nAUSGABE_ENDE\n");
}
