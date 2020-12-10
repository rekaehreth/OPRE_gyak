// source code created by me
// to show different steps

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	  //fork
#include <sys/wait.h> //waitpid
#include <errno.h>

int main()
{
	pid_t child = fork(); 
    // A child process is created with fork 
        // fork clones the code of the parent process to the child process
        // we can separate the two process by the child variable 
            // 0 (default) is the child
            // some positive number is the parent
    if (child > 0)
    {
        printf("I'm the parent process, pid: %i", getpid());
        // getpid() returns the pid number of the process
            // the child's pid isn't necessary a neighbour to the parent's
    }
    else
    {
        printf("I'm the child process, pid: %i", getpid());
    }
	printf("Hello, my pid number is: %i\nmy child number is: %i\n", getpid(), child); 
    // everything after fork is cloned
        // so this will be written to the output twice
    printf("Hello, my pid number is: %i\nmy parent number is: %i\n", getpid(), getppid());
    // getppid() returns the pid number of the parent process 
        // the application is also a process so it has to have a parent, wich will be the bash
    // pid numbers can be accessed in bash with: ps aux
    fork();
    fork();
    // Everything written here will be done 8 times (2^(number of forks))
    fork();
    fork();
    // when the parent is 1, the process' parent has already finished, so a new parent has to be choosen (1 - init process)
    // even the prompt can finish before its children finished 
    // as a result, the prompt will come back, but the children will continue writing things to the output
        // parent has to wait for all of its children processes to finish, before it can finish running
        // waitpid(child, status, 0);
	return 0;
}