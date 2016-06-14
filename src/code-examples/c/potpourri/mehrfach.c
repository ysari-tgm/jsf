#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPIELER 2

typedef struct {
  char** eigenes;
  char** fremdes;
  int kantenlaenge;
  int schuesse;
  int treffer;
  int runden;
} SPIELFELD;

void spielfeld_print(SPIELFELD*);
void spielfeld_fill(SPIELFELD*);

int main(int argc, char** argv)
{
  int i,j, groesse;

  SPIELFELD spieler[SPIELER];

  fprintf(stdout,"\nBitte geben Sie die Spielgroesse ein: ");
  fscanf(stdin,"%d",&groesse);

  for(i=0;i<SPIELER;i++)
  {
    spieler[i].kantenlaenge = groesse;
    spieler[i].eigenes = malloc(sizeof(char)*(spieler[i].kantenlaenge+1));

    for(j=0; j<spieler[i].kantenlaenge; j++)
    {
      if(spieler[i].eigenes != NULL)
      {
	spieler[i].eigenes[j] = malloc(sizeof(char)*(spieler[i].kantenlaenge+1));
      }
      else
      {
	fprintf(stderr,"Es gibt leider nicht genuegend Speicherplatz!");
      }
    }
    //strcpy(&spieler[i].eigenes[0][0], 'X');
    //fprintf(stdout,"Zeichen im ersten Element: %c", spieler[i].eigenes[0][0]);
    //fprintf(stdout,"\nFuelle das %d. Spielerfeld", i);
    
    spielfeld_fill(&spieler[i]);
    spielfeld_print(&spieler[i]);

    fprintf(stdout,"\n");
  }
  return EXIT_SUCCESS;
}

void spielfeld_print(SPIELFELD* feld)
{
  int i,j;
  char* zeile;

  fprintf(stdout,"\n\nSpielfeld wird angezeigt ...\n\n");

  for(i=0;i<feld->kantenlaenge;i++) {
    zeile = (char*) &feld->eigenes[i];
    fprintf(stdout,"\n");

    for(j=0;j<feld->kantenlaenge;j++)
      fprintf(stdout," %c ",*(zeile+j));
  }

}

void spielfeld_fill(SPIELFELD* feld)
{
  int i,j;
  char* zeile;

  for(i=0;i<feld->kantenlaenge;i++) {
    zeile = (char*) &feld->eigenes[i];
    for(j=0;j<feld->kantenlaenge;j++)
      strcpy(zeile+j,"x");
  }

}
