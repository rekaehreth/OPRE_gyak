// source code created by me
// to show different steps

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handler(int signumber)
{
	printf("Signal with number %i has arrived\n", signumber);
    // Should use only minél gyorsabban végrehajtható, nem megszakítható functions
}

void termHandler(int signumber)
{
    handler(signumber);
    // Make the program stop after SIGTERM, but with the original handler completed, without multiple SIGTERM call
    signal(SIGTERM, SIG_DFL); // unlinks the handler function
    raise(SIGTERM); // the process emits a signal to itself
}

int main()
{
	signal(SIGTERM, handler);
    // signal(SIGTERM, termHandler);
    // handler = SIG_IGN - ignore the signal (not SIGKILL, SIGSTOP) - the signal won't be delivered to the application
	// handler = SIG_DFL - back to default behavior 
    signal(SIGUSR1, handler);
    // the same handler can be linked to multiple signals

	pid_t child = fork();
	if (child > 0)
	{
		// sleep(3); // when sleep is here instead of in the child, the signal is not received by pause, because it was sent and handled during sleep
        // when there's no sleep, signals can get mixed up
        pause(); 
        // pause waits for a signal, and completes the 
        // a signal can be emitted from a (different) bash with kill {pid number}
        // kill -SIGKILL {pid number} cannot be ignored
        // useful signals: 
            // SIGTERM - the signal that is typically used to administratively terminate a process
            // SIGKILL - cannot be ignored
            // SIGUSR1 - User defined signal 1, os doesn't use it, a handler function can be defined with signal function
            // SIGUSR2 - User defined signal 2, os doesn't use it, a handler function can be defined
        pause();
		printf("Signal arrived\n", SIGTERM);
		int status;
		wait(&status); // waits for the child process to finish (not for a set amount of time)
		printf("Parent process ended\n");
	}
	else
	{
		printf("Waits 3 seconds, then send a SIGTERM %i signal\n", SIGTERM);
		sleep(3); // we can see the flow of the program, but it can also change the result
		kill(getppid(), SIGTERM);
        // send signal 
            // to whom
            // what signal
		printf("Child process ended\n");
	}
	return 0;
}
