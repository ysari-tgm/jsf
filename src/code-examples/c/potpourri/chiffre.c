/*
 *  Projekt: Programm zum (de)chiffrieren von Textdateien
 *    Autor: Thomas Krug
 *    */

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


FILE *lesen, *schreiben;
char dateiname_eingabe[256], dateiname_ausgabe[256];
char zeichen;
int schluessel;

int main()
{
  int lauf=0;

  printf("\n\tProgramm zum (de)chiffrieren von Textdateien");
  printf("\n\t____________________________________________\n\n");

  while(lauf==0)
  {
    printf("\nInputdatei: ");
    scanf("%s",&dateiname_eingabe);

    lesen=fopen(dateiname_eingabe,"r");

    if(lesen==NULL)
      printf("\nFehler beim Oeffnen der Datei!");


    else
      lauf=1;
  }
  lauf=0;

  while(lauf==0)
  {
    printf("\nOutputdatei: ");
    scanf("%s",&dateiname_ausgabe);

    schreiben=fopen(dateiname_ausgabe,"w");

    if(schreiben==NULL)
      printf("\nFehler beim Erstellen der Datei!");

    else
      lauf=1;
  }
  lauf=0;

  while(lauf==0)
  {
    printf("\nSchluessel (zum dechiffrieren negativen Schluessel angeben): ");
    scanf("%i",&schluessel);

    if((schluessel<-25)||(schluessel>25))
      printf("\nBitte geben Sie einen Schluessel im Bereich von -25 bis 25 an!");

    else
      lauf=1;
  }
  lauf=0;

  while(zeichen!=EOF)
  {
    zeichen=fgetc(lesen);

    //Zahlen
    if((zeichen>47)&&(zeichen<58)&&((zeichen+schluessel)<58)&&((zeichen+schluessel)>47))
      fputc(zeichen+schluessel, schreiben);

    else if((zeichen>47)&&(zeichen<58)&&((zeichen+schluessel)>57))
      fputc(zeichen+schluessel+47-57, schreiben);

    else if((zeichen>47)&&(zeichen<58)&&((zeichen+schluessel)<48))
      fputc(zeichen+schluessel-47+57, schreiben);

    //Grossbuchstaben
    else if((zeichen>64)&&(zeichen<91)&&((zeichen+schluessel)<91)&&((zeichen+schluessel)>64))
      fputc(zeichen+schluessel, schreiben);

    else if((zeichen>64)&&(zeichen<91)&&((zeichen+schluessel)>90))
      fputc(zeichen+schluessel+64-90, schreiben);

    else if((zeichen>64)&&(zeichen<91)&&((zeichen+schluessel)<65))
      fputc(zeichen+schluessel-64+90, schreiben);

    //Kleinbuchstaben
    else if((zeichen>96)&&(zeichen<123)&&((zeichen+schluessel)<123)&&((zeichen+schluessel)>96))
      fputc(zeichen+schluessel, schreiben);

    else if((zeichen>96)&&(zeichen<123)&&((zeichen+schluessel)>122))
      fputc(zeichen+schluessel+96-122, schreiben);

    else if((zeichen>96)&&(zeichen<123)&&((zeichen+schluessel)<97))
      fputc(zeichen+schluessel-96+122, schreiben);

    //sonstige Zeichen
    else
      fputc(zeichen, schreiben);
  }

  fclose(lesen);
  fclose(schreiben);
}

