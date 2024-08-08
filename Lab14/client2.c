#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>

#define SHARED_MEMORY_OBJECT_SIZE 50

int main (int argc, char ** argv) {
    int shm, len, cmd, mode = 0;
    char *addr;
    const char* mes1 = "Hello";
    sem_t *sem;

    const char* shmemname = "mshmem2.txt";
    const char* semmemname = "msemmem2.txt";

    if((sem = sem_open(semmemname, O_CREAT, 0666, 1)) == SEM_FAILED)
    {
        perror("sem_open");
        return 1;
    }

    if ( (shm = shm_open(shmemname, O_CREAT | O_RDWR, 0666)) == -1 ) {
        perror("shm_open");
        return 1;
    }

    if(sem_post(sem)){
        perror("sem_post");
        return 1;
    }

    //Cut file size
    if ( ftruncate(shm, SHARED_MEMORY_OBJECT_SIZE+1) == -1 ) {
        perror("ftruncate");
        return 1;
    }

    if(sem_wait(sem) < 0){
        perror("sem_wait");
    }

    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (char*)-1 ) {
        perror("mmap");
        return 1;
    }

    printf("Client recieves: %s\n", addr);
    sprintf(addr, "%s", mes1);
    printf("Client sendes: Hello\n");
    sleep(3);

    sem_close(sem);

    return 0;
}