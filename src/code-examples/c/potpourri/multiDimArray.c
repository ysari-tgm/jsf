#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int i, j;
	char text[3][3] = {
		'1', '2', '3',
		'4', '5', '6',
		'7', '8', '9'
	};

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++)
			printf("%c ", text[ i ][ j ]);
		printf("\n");
	}

	char ware[3][2][50] = {
		{"ID1", "Hallo Welt Angabe"},
		{"ID2", "Noch eine Eingabe"},
		{"ID3", "Und die letzte Zeile"}
	};

	for (i=0; i<3; i++)
		printf("%s :: %s\n", ware[i][0], ware[i][1]);

	char** dyn;
	dyn = malloc(5*sizeof(char*));
	for (i=0; i<5; i++)
		*(dyn+i) = malloc(1000*sizeof(char));

	for (i=0; i<5; i++)
		strcpy( *(dyn+i), "Zeile mit einem Inhalt von genau 42 Zeichen! Also darf es auf jeden Fall noch einwenig mehr sein! Wir m\u00FCssen auf jeden Fall die Grenze sprengen ... Also zum Tagesthema: Der erste Towel-Day wurde am 25. Mai 2001 gefeiert, genau 14 Tage nach dem unerwarteten Tod von Douglas Adams. Die treuen Fans haben den Gedanken weiterhin in die Welt getragen und somit ist auch 10 Jahre danach ein Handtuch das Zeichen der Solidarit\u00E4t und des tiefen Mitgef\u00FChls!");
	for (i=0; i<5; i++)
		printf("%d. %s\n\n", i+1, *(dyn+i));

	return EXIT_SUCCESS;
}
