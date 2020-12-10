#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	  // fork
#include <sys/wait.h> // waitpid
#include <errno.h>

int main()
{
	int status;

	pid_t child = fork(); // forks make a copy of variables
	if (child < 0)
	{
		perror("The fork calling was not succesful\n");
		exit(1);
	}
	if (child > 0) // the parent process, it can see the returning value of fork - the child variable!
	{
		// if a fork is created here, the parent process will have a second child process 
		pid_t child2 = fork();
		if (child2 > 0) // parent
		{
			waitpid(child, &status, 0);
			waitpid(child2, &status, 0);
			printf("The end of parent process\n");
			// every child process has to be awaited in the true parent process
		}
		else // child2
		{
			
		}
	}
	else // child process
	{
		// to start a program, like printing out a string (in parameter) 5 times (parameter)
		char *cmd = "./write";
		char *arg[] = {"./write", "Operating Systems", "5", NULL};
		// Null is needed so we know where the end is 
		printf("./write program will be called by execv function\n");
		execv(cmd, arg);
		// Nothing after execv will be executed
		// **TODO** Készítsenek egy mini shell-t (fogadjunk egy parancsot a billentyűzetről, hajtsuk végre, majd ha megvan, fogadjunk még egyet, stb. )
			// egy ciklus nem menne végig csak egyszer
			// minden beolvasás után gyártani kell egy új ciklust, és abban meghívni az exec-et  
		printf("It never returns to child process (except on error)- the content of the whole child process will be changed to the new one\n");
	}
	return 0;
}

// Output - no write program in directory
	// ./write program will be called by execv function
	// It never returns to child process (except on error) - the content of the whole child process will be changed to the new one
	// The end of parent process

// Output - with write program in directory 
	// // ./write program will be called by execv function
	// Operating Systems
	// Operating Systems
	// Operating Systems
	// Operating Systems
	// Operating Systems
	// The end of parent process