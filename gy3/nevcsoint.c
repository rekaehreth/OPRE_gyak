#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> 

int main(int argc, char *argv[])
{
    int pid, fd;
    printf("Fifo start!\n");
    char pipename[20];
    sprintf(pipename, "/tmp/%d", getpid()); 
    int fid = mkfifo(pipename, S_IRUSR | S_IWUSR); 

    char pipename2[20];
    sprintf(pipename2, "/tmp/%d-2", getpid()); 
    int fid2 = mkfifo(pipename2, S_IRUSR | S_IWUSR); 

    if (fid == -1)
    {
        printf("Error number: %i", errno);
        perror("Gaz van:");
        exit(EXIT_FAILURE);
    }
    printf("Mkfifo vege, fork indul!\n");
    pid = fork();

    if (pid > 0) //parent
    {
        printf("Szulo! \n");
        fd = open(pipename, O_RDONLY); 
        int sum = 0;
        int count = 0;
        int number = 1;

        while (number != 0)
        {
            read(fd, &number, sizeof(int));
            printf("Szulo - Olvas: %d\n", number);
            sum += number;
            ++count; // emiatt az átlagszámolás nem jó
        }
        if (count > 0)
        {
            float avg = (sum / (float)count);
            printf("Szulo - Sum : %d - Avg: %f\n", sum, avg);
        }

        // új cső nyitása, majd eredmény küldése 
        fd2 = open(pipename2, O_RDONLY);


        close(fd);
        unlink(pipename); 
    }
    else // child
    {
        printf("Gyerek!\n");
        fd = open(pipename, O_WRONLY);
        int number = 1;

        while (number != 0)
        {
            printf("\nGyerek - Kovetkezo szam: \n");

            int result = scanf("%d", &number);
            if (result == 0)
            {
                printf("Gyerek - Helytelen bemenet\n");
                while (fgetc(stdin) != '\n') 
                    ;
            }
            if (result == 1)
            {
                printf("Gyerek - Kuldi: %d\n", number);
                write(fd, &number, sizeof(int)); 
            }
        }
        
        close(fd)
        printf("Gyerek vege!\n");

        // pipename2 unlink ide kell kerüljön
    }

    return 0;
}
