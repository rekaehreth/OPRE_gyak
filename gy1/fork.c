#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	  //fork
#include <sys/wait.h> //waitpid
#include <errno.h>

int main()
{
	int status;
	int notacommonvalue = 1;
	printf("The value is %i before forking \n", notacommonvalue);

	pid_t child = fork(); 
	//fork makes a copy of variables
	if (child < 0) // error
	{
		perror("The fork calling was not succesful\n");
		exit(1);
	}
	if (child > 0) // the parent process, it can see the returning value of fork - the child variable!
	{
		waitpid(child, &status, 0);
		// waits the end of child process PID number=child, the returning value will be in status
		// 0 means, it really waits for the end of child process - the same as wait(&status)
		// waitpid breaks the program flow, and only continues after the child (or children) had finished
		// parameters 
			// 1st - pid number of child process 
			// 2nd - integer, contains the error number (e.g. the process was terminated manually) 
			// 3rd - modifies the function so it won't wait for the child process, just gets information about it
				// we won't use this 
		printf("The value is %i in parent process (remain the original) \n", notacommonvalue);
		
	}
	else // child process
	{
		notacommonvalue = 5; // it changes the value of the copy of the variable
		printf("The value is %i in child process \n", notacommonvalue);
	}
	return 0;
	// The processes can't communicate with each other via the copy of one variable
}
// Output:
	// The value is 1 before forking
	// The value is 5 in child process
	//N// The value is 1 in parent process (remain the original)