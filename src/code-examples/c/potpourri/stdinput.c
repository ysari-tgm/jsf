#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv)
{
}


void clean_stdin(void)
{
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}

