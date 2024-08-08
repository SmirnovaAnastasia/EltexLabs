#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "chat.h"
#include <signal.h>
#include <termios.h>
#define SHM_SIZE 200

struct shmemdata
{
    int count; //Count of how many
    char from_who[10];// from message or user
    char for_who[10];//
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
    int message_number;
    int user_number;
    char *my_name;
    char *message_buf[20];
    char *user_buf[20];
    int fin;
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


void *recieve_part(void* args)
{
    struct arg_struct_cl *arg = (struct arg_struct_cl*) args;

    int shmid, semid;
    key_t shkey, semkey;
    int size = SHM_SIZE;

    struct sembuf lock[2] = {{0,0,0},{0,1,0}};
    struct sembuf unlock= {0,-1,0};

    // char *shptr = NULL;
    struct shmemdata *shdata;
    

    //Create all
    shkey = ftok("mshmem3.txt",'m');
    if(shkey == (key_t)-1)
    {
        perror("Ftok shered mem");
        exit(1);
    }
    
    shmid = shmget(shkey,size,IPC_CREAT|0666);
    if(shmid == -1){
        perror("Shmget");
        exit(1);
    }

    shdata = (struct shmemdata*)shmat(shmid,NULL,0);// Create piece of shared memory

    if(shdata == (struct shmemdata*)-1) // Return void
    {
        perror("Shmat");
        exit(1);
    }

    semkey = ftok("msemmem3.txt",'m');
    if(semkey == (key_t)-1)
    {
        perror("Ftok semafor");
        exit(1);
    }

    semid = semget(semkey, 2, 0666);
    if(semid == -1){
        perror("Semget");
        exit(1);
    }

    char use = 0;
    char recieve_all = 0;
    char user_have = 0;

    //Work with it
    while(1)
    {

        if(arg->fin == 1){
            return((void*)1);
        }

        if((semop(semid, &lock[0], 2)) == -1)
        {
            printf("Semop");
            exit(1);
        }

        //What it should do
        if(strcmp(shdata->for_who, arg->my_name) == 0 || strcmp(shdata->for_who, "all") == 0)
        {
            //If it new user
            if(use == 0 && strcmp(shdata->for_who, arg->my_name) == 0){
                if(recieve_all == 0){
                    arg->user_number = shdata->count;
                    shdata->count = -1;
                    for (int i = 0; i < arg->user_number; ++i)
                    {
                        arg->user_buf[i] = malloc(sizeof(char) * 20);
                        arg->user_buf[i][0] = '\0';
                        strcpy(arg->user_buf[i], shdata->data[i]);
                    }
                    recieve_all++;
                    strcpy(shdata->for_who, "server");
                    strcpy(shdata->from_who, arg->my_name);
                }else{
                    arg->message_number = shdata->count;
                    shdata->count = -1;
                    for (int i = 0; i < arg->message_number; ++i)
                    {
                        arg->message_buf[i] = malloc(sizeof(char) * 20);
                        arg->message_buf[i][0] = '\0';
                        strcpy(arg->message_buf[i], shdata->data[i]);
                    }
                    strcpy(shdata->for_who, "server");
                    recieve_all = 0;
                    use++;
                }
                init1(&arg->wnd1, &arg->wnd2, &arg->subwnd1, &arg->subwnd2);
                refresh();
                refresh_windows1(arg->message_number, arg->user_number, arg->message_buf, 
                    arg->user_buf, &arg->wnd1, &arg->wnd2, &arg->subwnd1, &arg->subwnd2);
            }
            //Old user
            else if(strcmp(shdata->for_who, "all") == 0)
            {
                // Messages
                if(shdata->count > 0 && strcmp(shdata->data[0], arg->message_buf[arg->message_number-1]) != 0)
                {
                    arg->message_number++;
                    arg->message_buf[arg->message_number-1] = malloc(sizeof(char) * 20);
                    arg->message_buf[arg->message_number-1][0] = '\0';
                    strcpy(arg->message_buf[arg->message_number-1], shdata->data[0]);

                    if(strcmp(shdata->data[2], "user") == 0){
                        arg->user_number++;
                        if(arg->user_number > user_have){
                            arg->user_buf[arg->user_number-1] = malloc(sizeof(char) * 20);
                            arg->user_buf[arg->user_number-1][0] = '\0';  
                            user_have++;
                        }
                        strcpy(arg->user_buf[arg->user_number-1], shdata->data[1]);
                    }

                    if(strcmp(shdata->data[2], "exit") == 0){
                        for (int i = 0; i < arg->user_number; ++i)
                        {
                            int eq = strcmp(shdata->data[1],arg->user_buf[i]);
                            if(eq == 0){
                                if(i < (arg->user_number - 1)){
                                    for (int j = i; j < arg->user_number-1; ++j)
                                    {
                                        arg->user_buf[j][0] = '\0';
                                        strcpy(arg->user_buf[j],arg->user_buf[j+1]);
                                    }
                                }else{
                                    arg->user_buf[i][0] = '\0';
                                }
                            }
                        }
                        arg->user_number--;

                    }
                  
                    shdata->count--;
                    if(shdata->count == 0){
                        strcpy(shdata->data[2], "");
                    }
                }
                //Users
                if(shdata->count <= -1 && strcmp(shdata->data[0], arg->user_buf[arg->user_number-1]) != 0)
                {
                    shdata->count = -2;
                    arg->user_number = shdata->count;
                    arg->user_number++;
                    arg->user_buf[arg->user_number-1] = malloc(sizeof(char) * 20);
                    arg->user_buf[arg->user_number-1][0] = '\0';
                    strcpy(arg->user_buf[arg->user_number-1], shdata->data[0]);

                }
                refresh();
                refresh_windows1(arg->message_number, arg->user_number, arg->message_buf, 
                arg->user_buf, &arg->wnd1, &arg->wnd2, &arg->subwnd1, &arg->subwnd2);
            }    
        }

        if((semop(semid, &unlock, 1)) == -1)
        {
            printf("Semop");
            exit(1);
        }
    }
}

void *send_part(void* args)
{
    struct arg_struct_cl *arg = (struct arg_struct_cl*) args;

    //Init all
    int shmid, semid;
    key_t shkey, semkey;
    int size = SHM_SIZE;

    struct sembuf lock[2] = {{0,0,0},{0,1,0}};
    struct sembuf unlock= {0,-1,0};

    struct shmemdata *shdata;

    
    //Create
    shkey = ftok("mshmem3.txt",'m');
    if(shkey == (key_t)-1)
    {
        perror("Ftok shered mem");
        exit(1);
    }
    
    shmid = shmget(shkey,size,IPC_CREAT|0666);
    if(shmid == -1){
        perror("Shmget");
        exit(1);
    }

    shdata = (struct shmemdata*)shmat(shmid,NULL,0);// Create piece of shared memory

    if(shdata == (struct shmemdata*)-1) // Return void
    {
        perror("Shmat");
        exit(1);
    }

    //Semafor

    semkey = ftok("msemmem3.txt",'m');
    if(semkey == (key_t)-1)
    {
        perror("Ftok semafor");
        exit(1);
    }

    semid = semget(semkey, 2, 0666);
    if(semid == -1){
        perror("Semget");
        exit(1);
    }

    int use = 0;
    int recieve_time = 0;

    //Work
    while(1)
    {
        if(use == 1){
            sleep(30);
            use++;
        }

        if(recieve_time == 1){
            sleep(9);
            recieve_time = 0;
        }

        // sleep(1);

        if((semop(semid, &lock[0], 2)) == -1)
        {
            printf("Semop");
            exit(1);
        }

        //If it first use and server don't know us
        if(use == 0 && shdata->count == 0){
            //printf("New user!(Send)\n");
            strcpy(shdata->data[0],"New user");
            strcpy(shdata->for_who,"server");
            strcpy(shdata->from_who, arg->my_name);
            shdata->from_who[strlen(arg->my_name)] = '\0';
            use++;
            recieve_time = 1;
            init2(&arg->wnd3, &arg->subwnd3);

        //Know us
        }else if(shdata->count == 0){
     
            //What it should do
            if(shdata->count == 0){
                char mes[20];
                refresh();
                refresh_windows2(mes, &arg->wnd3, &arg->subwnd3);
                strcpy(shdata->from_who, arg->my_name);
               
                char ser[7] = "server";
                strcpy(shdata->for_who,ser);
                shdata->count = -2; //!!!Don't foget
                strcpy(shdata->data[0], mes);
                recieve_time = 1;

                if(strcmp(mes,"exit") == 0){
                    arg->fin = 1;
                    if((semop(semid, &unlock, 1)) == -1)
                    {
                        printf("Semop");
                        exit(1);
                    }
                    return((void*)1);
                }
            }
        }


        if((semop(semid, &unlock, 1)) == -1)
        {
            printf("Semop");
            exit(1);
        }
    }   
}

int main()
{
    //For sending

    WINDOW * wnd1, *wnd2, *wnd3;
    WINDOW * subwnd1, *subwnd2, *subwnd3;

    int *s;

    char my_name[20];
    int shmid, semid;
    char *message_buf[20];
    char *user_buf[20];

    printf("Print your name: ");
    if(fgets(my_name, 20, stdin) == NULL){
            perror("Critical error!");
    }


    //Sending and receiving
    args.wnd1 = wnd1;
    args.wnd2 = wnd2;
    args.wnd3 = wnd3;
    args.subwnd1 = subwnd1;
    args.subwnd2 = subwnd2;
    args.subwnd3 = subwnd3;
    args.my_name = my_name;
    args.my_name[strlen(my_name) - 1] = '\0';
    printf("How many sym: %ld\n", strlen(my_name));
    args.user_buf[0] = user_buf[0];
    args.message_buf[0] = message_buf[0];
    args.message_number = 0;
    args.user_number = 0;
    args.fin = 0;


    pthread_t thread, thread2;

    pthread_create(&thread, NULL, recieve_part, (void*)&args);
    pthread_create(&thread2, NULL, send_part, (void*)&args);

    if(pthread_join(thread, (void**)&s) != 0)
    {
        perror("Pthread_join");
        return -1;
    }
    
    if(pthread_join(thread2, (void**)&s) != 0)
    {
        perror("Pthread_join");
        return -1;
    }

    return 0;
}