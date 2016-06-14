# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <limits.h>

# define MAX 45
# define MIN 1

int doppelt(unsigned int array[], int pos){

    int i;

    for(i=0; i<pos; i++)
        if(array[pos]==array[i])
            return 1;

    return 0;

}

int zufall_ohne_zuruecklegen(unsigned int array[], int groesse, int min, int max){

    int i;

    for(i=0; i<groesse; i++){

        do{

            array[i]=min+rand()%(max-min+1);

        }while(doppelt(array, i));

    }

}

int pruefe(unsigned int array_1[], unsigned int array_2[], int groesse){

    int i, n;
    int treffer;

    for(i=0, treffer=0; i<groesse; i++)
        for(n=0; n<groesse; n++)
            if(array_1[i]==array_2[n])
                treffer++;

    return treffer;

}

int main(){

    int i;
    unsigned long zaehler;
    unsigned int tipp[6], zufall[6];

    for(i=0; i<6; i++){

        printf("%d. Zahl: ", i+1);
        scanf("%d", &tipp[i]);

        if(doppelt(tipp, i) || tipp[i]>MAX || tipp[i]<MIN){

            printf("Zahl ungueltig\n");
            i--;

        }

    }

    srand(time(NULL));
    for(zaehler=0; zaehler<=ULONG_MAX; zaehler++){

        zufall_ohne_zuruecklegen(zufall, 6, MIN, MAX);

        if(pruefe(tipp, zufall, 6)==6){

            printf("6 Treffer nach %lu Versuchen, die Wahrscheinnlichkeit liegt bei %.9f%%.\n", zaehler, (double)1/zaehler);
            return 0;

        }

    }

}
