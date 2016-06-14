#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  long unsigned int ausgabe=0, i=0, random=0;

  //char spComp[2][3]= {{'a','b','c'}, {'d','e','f'}};

  // Initialisiere die Randomizefunktion mit
  // dem jetzigen time-Wert
  srand( (unsigned) time(NULL) );

  do {
    ausgabe = rand()%2212124123121412+1;
    printf("Ausgabe: %lu\n",ausgabe);
    random += ausgabe;
    i++;
  } while (1);

  //printf("Hier ist die ... %c\n",spComp[1][2]);
  printf("Hier ist die Zahl ... %lu\n",random%ausgabe+1);

  return EXIT_SUCCESS;
}
