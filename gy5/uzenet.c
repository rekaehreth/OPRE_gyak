#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

struct uzenet 
{
     // az elsonek mindenkepp long-nak kell lennie, ez a szam az uzenet osztalya / kategoriaja / prioritasa
     // ezzel tudom pl. biztositani, hogy ne olvassa ki a sajat uzenetet a process
     long mtype; //ez egy szabadon hasznalhato ertek, pl uzenetek osztalyozasara
     char mtext[1024]; // kuldendo szoveg
};

// sendig a message
int kuld(int uzenetsor)
{
     const struct uzenet uz = {5, "Hajra Fradi!"}; // 5-os kategoriaba kuldjuk a kovetkezo uzenetet
     int status;

     status = msgsnd(uzenetsor, &uz, strlen(uz.mtext) + 1, 0); 
     // hova, mesage send (memoriateruletrol), hany byte-ot szeretnek kuldeni (nem szamoljuk bele a long-ot), 
     // a 3. param ilyen is lehet: sizeof(uz.mtext)
     // a 4. parameter gyakran IPC_NOWAIT, ez a 0-val azonos | ha tele van a sor, nem varakozik (deadlock), hanem hibaval visszater
     if (status < 0)
          perror("1 msgsnd");
     return 0;

     struct uzenet uz2; // ebbe fogunk fogadni
     int status2;
     status2 = msgrcv(uzenetsor, &uz2, 1024, 3, 0); 

     if (status2 < 0)
          perror("2 msgsnd");
     else
          printf("A 2 kapott uzenet kodja: %ld, szovege:  %s\n", uz2.mtype, uz2.mtext);
     return 0;
}

// receiving a message.
int fogad(int uzenetsor)
{
     const struct uzenet uz2 = {3, "Zoldeteg"};
     int status2;
     status2 = msgsnd(uzenetsor, &uz2, strlen(uz2.mtext) + 1, 0);
     // nyugodtan kezdhet mindenki a kuldessel

     struct uzenet uz; // ebbe fogunk fogadni
     int status;
     // az utolso parameter(0) az uzenet azonositoszama
     // ha az 0, akkor a sor elso uzenetet vesszuk ki
     // ha >0 (5), akkor az 5-os uzenetekbol a kovetkezot
     // vesszuk ki a sorbol
     status = msgrcv(uzenetsor, &uz, 1024, 5, 0); 
     // mesage receive (az uzenet max hossza 1024, rovidebbet is ert)
     // honnan, hova, uzenet max hossza, melyik kategoriabol, flag-ek (most ures sorbol nem varakozik, hanem visszater hibaval)

     if (status2 < 0)
          perror("2 msgsnd");

     if (status < 0)
          perror("1 msgsnd");
     else
          printf("Az 1 kapott uzenet kodja: %ld, szovege:  %s\n", uz.mtype, uz.mtext);
     return 0;
}

int main(int argc, char *argv[])
{
     pid_t child;
     int uzenetsor, status;
     key_t kulcs;

     // msgget needs a key, amelyet az ftok generál
     //.
     // több processz között és akár több irányba is mehet kommunikáció
     // nem konkrét fájlként jön létre, hanem a rendszer egy id mögé tárolja, alkalmazáshoz egyedi kell
     // ftok hashelő függvény - szöveg + egy szám (itt: futtatott fájl neve + ennyivel hashelj)
     // ha ugyan azt az elérési utat adjuk meg ugyan azzal a számmal, ugyan azt a kukcsot kapjuk mindig
     kulcs = ftok(argv[0], 1); // ftok - egyedi azonosítóra van szükségünk a msgqueue erőforrás beazonosításához
     printf("A kulcs: %d\n", kulcs);
     uzenetsor = msgget(kulcs, 0600 | IPC_CREAT); // msgget-tel hozzuk létre, ha már van ilyen a rendszerben, akkor megnyitjuk | IPC_CREAT ha nincs ilyen, csinálj
     // az uzenetsor integerrel azonosítom, itt már file-ként tudom használni (filediscriptor)
     if (uzenetsor < 0)
     {
          perror("msgget");
          return 1;
     }

     child = fork();
     if (child > 0)
     {
          kuld(uzenetsor); // Parent sends a message.
          wait(NULL); // megvárjuk, hogy mindenki, aki használja, befejezze
          // After terminating child process, the message queue is deleted.
          status = msgctl(uzenetsor, IPC_RMID, NULL); // ~ unlink | message control remove id
          if (status < 0)
               perror("msgctl");
          return 0;
     }
     else if (child == 0)
     {
          return fogad(uzenetsor);
          // The child process receives a message.
     }
     else
     {
          perror("fork");
          return 1;
     }

     return 0;
}
