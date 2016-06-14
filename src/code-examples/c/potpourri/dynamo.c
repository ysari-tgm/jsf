#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void speicher_reservieren(void* speicheraddresse);

int main( int argc, char** argv)
{
  int *pint = malloc(NULL);
  int i;

  for(i=0; i<UINT_MAX; i++)
  {
    speicher_reservieren(pint);
    *pint = i+1;
    printf("\nHier ist die %d. Iteration\n",*pint);
  }
  return EXIT_SUCCESS;
}


void speicher_reservieren(void* speicheradresse) {
    if( !(speicheradresse = malloc(10000*sizeof(int))))
    {
      printf("\nSorry, habe keinen freien Speicherplatz mehr!");
      printf("\nProgramm sollte beendet werden ...\n");
    }
}
