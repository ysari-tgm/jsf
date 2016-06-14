#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t TYPE;
char *int2bin(TYPE);

int main (int argc, char** argv)
{
  TYPE registerA = 0;

  registerA |= (1<<4);
  registerA |= (0xA<<4);
  registerA |= (1<<0);
  registerA |= 0b00000010;
  //registerA &= (0<<1);
  registerA &= ~(1<<1);

  printf("size of registerA: %ld byte(s)\n",sizeof(registerA));
  printf("registerA: 0x%x\n",registerA);
  printf("registerA: 0b%s\n",int2bin(registerA));

  return EXIT_SUCCESS;
}

char *int2bin(TYPE a)
{
  char *str;
  int i, size=sizeof(TYPE)*8;
  str = (char *) malloc(size+1);

  for(i=0; i<size; i++) str[i]= '0';

  i = size-1;
  while (a > 0)
  {
    if (a%2==1) str[i] = '1';  
    i--;
    a = a/2 ;
  }
  return str;   
} 
