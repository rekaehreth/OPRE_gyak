#include <stdio.h>
#include <stdlib.h>
//call it with some parameters from the command line

int main(int argc, char **argv)
// argc - number of arguments found in command prompt
//char** - parameters (char** means an array of character arrays = array of strings)
{
    int i; 
    printf("Number of command line arguments are: %i\n", argc); // %i - argc is an integer type
    for (i = 0; i < argc; i++) // i has to be declared before for (in classic c)
    {
        // first (0.) argument is the name of the called app 
        // módosítsuk a kódot úgy, hogy ha számot kapunk paraméterként, ne a számot, hanem a kétszeresét írjuk ki a képernyőre
        int param = atoi(argv[i]);
        if ( param != 0) 
        {
            printf("%i. argument is %d\n", i, param * 2;
        }
        printf("%i. argument is %s\n", i, argv[i]);
    }
    return 0;
}
// compile from command propt: gcc arg.c -out arg.out | arg.exe
