#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main()
{
	// srand(time(NULL));	  // the starting value of random number generation
	fork();
	// the same number will be generated, when generating the seed before the fork
	// but swapping the two lines won't help, because the current time in secs is used as seed 
		// you have to be really unlucky to have differenc seeds for the parent and child this way
	// pid number is guaranteed to be different
	srand(getpid());
	int r = rand() % 100; // number between 0-99
	printf("Random number %i\n", r);
	return 0;
}
// **TODO** legyen benne egy szulo es egy gyerek feladat, 