#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#define SHM_SIZE 100

int main()
{
    int shmid, semid;
    key_t shkey, semkey;
    int size = SHM_SIZE;
    
    char *shptr = NULL;

    //Create files
    // fopen("mshmem.txt", "m");
    // fopen("msemmem.txt", "m");
    struct sembuf lock[2] = {{0,0,0},{0,1,0}};
    struct sembuf unlock= {0,-1,0};

    //===============================
    
    //Shared memory

    //Create key for shmem
    shkey = ftok("mshmem.txt",'m');
    if(shkey == (key_t)-1)
    {
        perror("Ftok shered mem");
        return -1;
    }

    //Create piece of shared memory 
    shmid = shmget(shkey, size, 0666 | IPC_CREAT | IPC_EXCL);
    if(shmid == -1){
        perror("Shmget");
        return 1;
    }


    //===============================

    //Semafor

    //Create key for sem
    semkey = ftok("msemmem.txt",'m');
    if(semkey == (key_t)-1)
    {
        perror("Ftok semafor");
        return -1;
    }

    semid = semget(semkey, 2, 0666 | IPC_CREAT);
    if(semid == -1){
        perror("Semget");
        return -1;
    }

    //Create 2 semafors

    if(semctl(semid, 0, SETVAL, 0) == -1)
    {
        perror("Semctl");
        return -1;
    }

    if(semctl(semid, 1, SETVAL, 0) == -1)
    {
        perror("Semctl");
        return -1;
    }


    shptr = shmat(shmid,NULL,0);// Create piece of shared memory

    if(shptr == (void *)-1) // Return void
    {
        perror("Shmat");
        return 1;
    }

    //===============================

    //Write semafor

    for (int i = 0; i < 2; ++i)
    {

        if((semop(semid, &lock[0], 2)) == -1)
        {
            printf("Semop");
            return -1;
        }

        if(i == 0){
            snprintf(shptr, 100, "Hello!");

            printf("Client send: Hello\n");

            usleep(200);
        }else{
            usleep(200);

            //Critical section(between two semop)
            printf("Mes: %s\n", shptr);

        }

        if((semop(semid, &unlock, 1)) == -1)
        {
            printf("Semop");
            return -1;
        }
    }
    
    if(semctl(semid, 1, IPC_RMID) == -1)
    {
        perror("Semctl");
        return -1;
    }

    // //Delete
    // if(shmdt(shptr) == -1)
    // {
    //     perror("shmdt");
    //     exit(1);
    // }

    //Disconnect
    if(shmctl(shmid,IPC_RMID,NULL) == -1)
    {
            perror("shmctl");
            exit(1);
    }
    
    //Delete files for ftok
    unlink("mshmem.txt");
    unlink("msemmem.txt");

    return 0;
}

