#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for pipe()
#include <string.h>
#include <sys/wait.h>
//
// unnamed pipe example
//
int main(int argc, char *argv[])
{
    int pipefd[2]; // unnamed pipe file descriptor array | egy cso ket fajlkent fog latszani (0 - read , 1 - write)
    pid_t pid;
    char sz[100]; // char array for reading from pipe

    if (pipe(pipefd) == -1)
    {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    pid = fork(); // creating parent-child processes
    if (pid == -1)
    {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {                     // child process
        sleep(3);         // sleeping a few seconds, not necessary | csovek szinkronizalnak az olvasasi parancsnal
        close(pipefd[1]); // Usually we close the unused write end | a gyerekben csak olvasni szeretnenk, ne legyen felesleges eroforras
        printf("Gyerek elkezdi olvasni a csobol az adatokat!\n");
        read(pipefd[0], sz, sizeof(sz)); // reading max 100 chars | file-kezeles read-je (binaris file)
        printf("Gyerek olvasta uzenet: %s", sz);
        printf("\n");
        close(pipefd[0]); // finally we close the used read end |ha nem zarjuk be, lesz egy felesleges eroforras, amit nem hasznalunk. 
    }
    else // pid > 0
    { // szulo process
        printf("Szulo indul!\n");
        close(pipefd[0]); // Usually we close unused read end
        write(pipefd[1], "Hajra Fradi!", 13); // 13 karaktert kuldunk, a 13. a terminal null, eddig olvas a read
        close(pipefd[1]); // Closing write descriptor
        printf("Szulo beirta az adatokat a csobe!\n");
        fflush(NULL); // flushes all write buffers (not necessary) | ha nem zarjuk le a pipe-ot, akkor nem biztos, hogy fogja flush-olni
        wait(NULL);   // waiting for child process (not necessary)
                      // try it without wait()
        printf("Szulo befejezte!");
    }
    exit(EXIT_SUCCESS); // force exit, not necessary
}
