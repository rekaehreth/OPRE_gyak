#define Alarcot_FEL SIGUSR1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <sys/wait.h>

char* potentialNames[] = {"Malac", "Majom", "Zebra"};
int arrSize = 3;

char* chooseRandomName()
{
    srand(getpid());
    int name = rand() % arrSize;
    printf("%i", name);
    char* result = potentialNames[name];
    if ( name == (arrSize-1) )
    {
        potentialNames[name] = NULL;
    }
    else
    {
        potentialNames[name] = potentialNames[name + 1];
    }
    arrSize = arrSize - 1;
    return result;
}

void handler(int signumber)
{
	printf("%i szamu jatekos felkeszult\n", signumber);
}

int main(int argc, char *argv[])
{
    signal(Alarcot_FEL, handler);
    
    int pipec1[2]; // unnamed pipe for child1 (0 - read , 1 - write)
    int pipec2[2]; // unnamed pipe for child2 (0 - read , 1 - write)
    pid_t child1, child2;
    char sz1[100]; // char array for reading from pipec1
    char sz2[100]; // char array for reading from pipec2
    if (pipe(pipec1) == -1)
    {
        perror("Hiba a pipe1 nyitaskor!");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipec2) == -1)
    {
        perror("Hiba a pipe2 nyitaskor!");
        exit(EXIT_FAILURE);
    }
    child1 = fork(); // creating parent-child processes
    if (child1 == -1)
    {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }
    if (child1 > 0) 
    {
        child2 = fork();
        if ( child2 > 0) // // szulo, jatekvezeto
        {
            printf("Szulo indul!\n");

            close(pipec1[1]); // Close unused write end for child1
            close(pipec2[1]); // Close unused write end for child2
            
            pause();
            printf("Teszt\n");
            pause();

            printf("A jatekosok keszen allnak!\n");
            
            read(pipec1[0], sz1, sizeof(sz1)); 
            printf("Az elso jatekos neve: %s\n", sz1);
            
            read(pipec1[0], sz2, sizeof(sz2));
            printf("A masodik jatekos neve: %s\n", sz2);

            close(pipec1[0]);
            close(pipec2[0]);

            int status1, status2;
            waitpid(child1, &status1, 0);
            waitpid(child2, &status2, 0);

            printf("Szulo befejezte!");
        }
        else // child2
        {
            sleep(2);
            kill(getppid(), Alarcot_FEL);
            close(pipec2[0]); 
            char* name = chooseRandomName();
            write(pipec2[1], name, sizeof(name)); 
            fflush(NULL);   
            close(pipec2[1]);
            sleep(3);
        }
    }
    else //child1 == 0 // gyerek1
    {
        sleep(4);
        kill(getppid(), Alarcot_FEL);
        close(pipec1[0]); 
        char* name = chooseRandomName();
        write(pipec1[1], name, sizeof(name)); 
        fflush(NULL);   
        close(pipec1[1]);  
        sleep(3);
    }
    exit(EXIT_SUCCESS); // force exit, not necessary
}
