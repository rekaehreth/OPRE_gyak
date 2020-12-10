// fork.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //fork, signal, pipe
#include <sys/wait.h> //waitpid
#include <errno.h>
// fcntl.c
#include <sys/types.h> //fork-hoz
#include <sys/stat.h>
#include <string.h> //strlen
#include <fcntl.h>  //lock

// signal.c
#include <signal.h> // signal
#include <sys/types.h> // struct? 


// signal handler
void handler(int signumber)
{
    printf("Signal with number %i has arrived\n", signumber);
}

int main()
{
    // Signal
    signal(SIGTERM, handler); //handler = SIG_IGN - ignore the signal (not SIGKILL,SIGSTOP),
                              //handler = SIG_DFL - back to default behavior
    // Fork
    pid_t child = fork(); //forks make a copy of variables
    if (child < 0)
    {
        perror("The fork calling was not succesful\n");
        exit(1);
    }
    if (child > 0)
    {
        // the parent process, it can see the returning value of fork - the child variable!
        // waitpid(child, &status, 0);
        // waits the end of child process PID number=child, the returning value will be in status
        // 0 means, it really waits for the end of child process - the same as wait(&status)
    }
    else
    {
        //child process
    }
    return 0;
}