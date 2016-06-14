/*Autor:        Ingo Joechl
 * Erstellt:06.11.2008
 * Version       0.1
 * Beschreibung: Zahleneingabe vom User werden in ein Array abgelegt. Die Eingabe wird mit mergesort geordnet.
 *               Zum Schuss erfolgt die Ausgabe der Eingabe und des sortierten Arrays.
 *               Demo zu  mergsort mit Arrays die Rekursiv aufgerufen werden. 
 */

#include<stdio.h>
#include<stdlib.h>


// Feldlaenge
#define SIZE 10
// funktionsdekleration
void merge(int array[], int);

int main (int argc, char* argv[]) {

  int z=0,wert=0,ausgabearray [SIZE],array[SIZE];
  // Eingabe
  while(z<SIZE){
    printf("Bitte geben Sie den %d. Wert ein ",z);
    scanf("%d",&wert);
    array[z]=wert;
    ausgabearray[z]=wert;
    z++;
  }
  // Ausgabe
  printf("\n Noch Unsortiert:\n");
  z=0;
  while(z<SIZE){
    printf("Feldnummer: %d Wert: %d\n",z,ausgabearray[z]);
    z++;
  }

  //Funktionsaufruf
  merge(array,SIZE);

  printf("Jetzt Sortiert:\n");
  z=0;
  while(z<SIZE){
    printf("Feldnummer: %d Wert: %d\n",z,array[z]);
    z++;
  }
  return EXIT_SUCCESS;
}

void merge(int array[], int laenge){

  //Abbruchbedingung, Nur ein Element braucht nicht sortiert werden
  if(laenge> 1){
    // Deklaration der Felder
    int links[laenge/2], rechts[(laenge + 1)/2], i;
    // array in 2 Haelften teilen
    for(i = 0; i < laenge/2; ++i)
      links[i] = array[i];
    for(i = laenge/2; i < laenge; ++i)
      rechts[i - laenge/2] = array[i];
    // Rekursiver Funktionsaufruf
    merge(links,laenge/2);
    merge(rechts,(laenge + 1)/2);
    // Zeiger auf den Anfang von den Teilarray legen
    int *zeiger1 = &links[0];
    int *zeiger2 = &rechts[0];

    for(i = 0; i < laenge; ++i){
      // Ist 1.Element von links kleinergleich 1.Element von rechts
      if(*zeiger1 <= *zeiger2){
	// wenn ja schreibe 1.Element in array
	array[i] = *zeiger1;
	// Wenn zeiger am Ende angekommen 
	if(*zeiger1 == links[laenge/2 - 1]){
	  // dann zeiger auf 1.Element von rechts legen
	  zeiger1=&rechts[(laenge + 1)/2 - 1];
	}
	// wenn nicht Zeiger weiterruecken
	else{
	  ++zeiger1;
	}
      }
      else{
	//1.Feld von rechts ins array schreiben
	array[i]=*zeiger2;

	// Wenn rechtes Feld abgearbeitet ist
	if(*zeiger2 == rechts[(laenge + 1)/2 - 1]){
	  // zeiger2 auf erstes element von links legen
	  zeiger2 = &links[(laenge)/2 - 1];
	}
	else{
	  // zeiger2 weiterschieben
	  ++zeiger2;
	}
      }
    }
  }
}
