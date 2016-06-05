#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv)
{
	int zahl = 1234;
	printf("\nWert von Zahl: %d\n", zahl);

	int* pointer;
	pointer = &zahl;
	*pointer = 42;


	printf("\nAdresse von Zahl: %p\n", &zahl);
	printf("\nWert von Zahl: %d\n", zahl);
	printf("\nAdresse von Pointer: %p\n", &pointer);
	printf("\nWert von Pointer: %p\n", pointer);

	return EXIT_SUCCESS;
}
