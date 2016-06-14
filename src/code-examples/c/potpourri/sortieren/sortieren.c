/* Autor: Philipp Lasser
 * Datum: 21.01.2009
 * Version: 1.1
 * Programmbeschreibung: Dies ist ein Programm das 10 eingegebenen 
 * Zahlen, aufsteigend sortiert wieder ausgiebt. 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int main(int argc, char *argv[])
{
  int array[size],i;
  for(i = 0; i < size; i++) {
    printf("Eingabe der %d Zahl > ",i+1);
    scanf("%d",&array[i]);
  }

  printf("\nSie haben die Zahlen eingeben :");
  for(i = 0; i < size; i++)
    printf(" %d", array[i]);

  printf("\n");

  mergesort(array,0, size-1); //Aufruf der Funktion mit übergabe des Arrays, der Startposition und der Anzahl der Zahlen

  printf("Die Zahlen in sortierter Reihenfolge :");
  for(i = 0; i < size; i++)
    printf(" %d", array[i]);

  printf("\n");

  return EXIT_SUCCESS;
}
