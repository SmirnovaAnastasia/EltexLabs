#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#define SHM_SIZE 100

struct shmemdata
{
    int count; //Count of how many
    int what[10];// message or user
    char data[20][20];
};

struct arg_struct_cl
{
    WINDOW *wnd1;
    WINDOW *wnd2;
    WINDOW *wnd3;
    WINDOW *subwnd1;
    WINDOW *subwnd2;
    WINDOW *subwnd3;
    char qid;
    key_t msgkey;
};

struct arg_struct_cl args;

void sig_winch(int signo){
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
    resizeterm(size.ws_row, size.ws_col);
    nodelay(stdscr, 1);
    while (wgetch(stdscr) != ERR);
    nodelay(stdscr, 0);
}


//Прием
void *recieve_part(void* args)
{
    char *message_buf[20];
    char *user_buf[5];
    int message_number = 0;
    int user_number = 0;

	for (int i = 0; i < 2; ++i)
    {

        if((semop(semid, &lock[0], 2)) == -1)
        {
            printf("Semop");
            return -1;
        }



        // if(i == 0){
        //     snprintf(shptr, 100, "Hello!");

        //     printf("Client send: Hello\n");

        //     usleep(200);
        // }else{
        //     usleep(200);

        //     //Critical section(between two semop)
        //     printf("Mes: %s\n", shptr);

        // }

        if((semop(semid, &unlock, 1)) == -1)
        {
            printf("Semop");
            return -1;
        }
    }

}

//Отправка
void *send_part(void* args)
{
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

}

int main()
{
	//For sending
	char *message_buf[20];
	char *user_buf[5];
	int message_number = 0;
	int user_number = 0;

    WINDOW * wnd1, *wnd2, *wnd3;
    WINDOW * subwnd1, *subwnd2, *subwnd3;

    int *s;

	//===============================

	//For sem and shmem
	int shmid, semid;
    key_t shkey, semkey;
    int size = SHM_SIZE;
    
    // char *shptr = NULL;
    struct shmemdata shdata;

    //Create files
    // fopen("mshmem.txt", "m");
    // fopen("msemmem.txt", "m");
    struct sembuf lock[2] = {{0,0,0},{0,1,0}};
    struct sembuf unlock= {0,-1,0};
    
    //Shared memory

    //Create key for shmem
    shkey = ftok("mshmem3.txt",'m');
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

    //Semafor

    //Create key for sem
    semkey = ftok("msemmem3.txt",'m');
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

    shdata = shmat(shmid,NULL,0);// Create piece of shared memory

    if(shdata == (struct shmemdata*)-1) // Return void
    {
        perror("Shmat");
        return 1;
    }

    //===============================

    //Sending and receiving

    args.wnd1 = wnd1;
    args.wnd2 = wnd2;
    args.wnd3 = wnd3;
    args.subwnd1 = subwnd1;
    args.subwnd2 = subwnd2;
    args.subwnd3 = subwnd3;
    args.qid = qid;
    args.msgkey = msgkey;

    pthread_t thread, thread2;

    pthread_create(&thread, NULL, recieve_part, (void*)&args);
    pthread_create(&thread2, NULL, send_part, (void*)&args);

    pthread_join(thread, (void**)&s);
    pthread_join(thread2, (void**)&s);
    // recieve_part();
    // send_part();

    //===============================

    if(semctl(semid, 1, IPC_RMID) == -1)
    {
        perror("Semctl");
        return -1;
    }

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
