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
    int message_number;
    int user_number;
    char *message_buf[20];
    char *user_buf[20];
};

//Прием
void *recieve_part(void* args)
{
    struct arg_struct_cl *arg = (struct arg_struct_cl*) args;

    int shmid, semid;
    key_t shkey, semkey;
    int size = SHM_SIZE;
    char *shptr = NULL;
    struct shmemdata *shdata;

    printf("Im here!\n");

    struct sembuf lock[2] = {{0,0,0},{0,1,0}};
    struct sembuf unlock= {0,-1,0};
    
    //Shared memory

    //Create key for shmem
    shkey = ftok("mshmem3.txt",'m');
    if(shkey == (key_t)-1)
    {
        perror("Ftok shered mem");
        exit(1);
    }

    //Create piece of shared memory 
    shmid = shmget(shkey, size, 0666 | IPC_CREAT);
    if(shmid == -1){
        perror("ShmgetRec");
        exit(1);
    }

    //Semafor

    //Create key for sem
    semkey = ftok("msemmem3.txt",'m');
    if(semkey == (key_t)-1)
    {
        perror("Ftok semafor");
        exit(1);
    }

    semid = semget(semkey, 2, 0666 | IPC_CREAT);
    if(semid == -1){
        perror("SemgetRec");
        exit(1);
    }

    //Create 2 semafors (only here)

    if(semctl(semid, 0, SETVAL, 0) == -1)
    {
        perror("Semctl1");
        exit(1);
    }

    if(semctl(semid, 1, SETVAL, 0) == -1)
    {
        perror("Semctl2");
        exit(1);
    }

    shdata = (struct shmemdata*)shmat(shmid,NULL,0);// Create piece of shared memory

    if(shdata == (struct shmemdata*)-1) // Return void
    {
        perror("Shmat");
        exit(1);
    }


    int use = 0;
    int send_time = 0;

    int user_have = 0;
    int message_have = 0;
    
	while(1)
    {

        if(send_time == 1 || send_time == 2){
            sleep(1);
            if(send_time == 1){
                send_time = 2;
            }else{
                send_time = 0;
            }
        }

        if((semop(semid, &lock[0], 2)) == -1)
        {
            printf("Semop");
            exit(1);
        }

        //What it should do
        if(use == 0){
            shdata->count = 0; //Count of how many
            arg->message_number = 0;
            arg->user_number = 0;
            arg->message_buf[0] = "";
            arg->user_buf[0] = "";
            
            sleep(10);
        }else if(shdata->count != -3)
        {
            //New user
            if(strcmp(shdata->for_who, "server") == 0 && strcmp(shdata->data[0], "New user") == 0 && shdata->count != -1)
            {
                printf("NewUser!\n");
                arg->user_number++;

                if(arg->user_number > user_have){
                    arg->user_buf[arg->user_number-1] = malloc(sizeof(char) * 20);
                    arg->user_buf[arg->user_number-1][0] = '\0';  
                    user_have++;
                }
                strcpy(arg->user_buf[arg->user_number-1], shdata->from_who);
                printf("Add new user: %s\n", arg->user_buf[arg->user_number-1]);
                
                arg->message_number++;
                if(arg->message_number > message_have){
                    arg->message_buf[arg->message_number-1] = malloc(sizeof(char) * 20);
                    arg->message_buf[arg->message_number-1][0] = '\0';  
                    message_have++;
                }
                char new_mes[40] = "";
                strcat(new_mes, shdata->data[0]);
                strcat(new_mes, " - ");
                strcat(new_mes, shdata->from_who);
                strcpy(arg->message_buf[arg->message_number-1], new_mes);
                printf("Add new message: %s\n", arg->message_buf[arg->user_number-1]);

                //printf("%s\n", shdata->data[0]);
                printf("Rec: Users: %d | Messages: %d\n", arg->user_number, arg->message_number);
                shdata->count = -1;
                printf("=================================\n");
            }
            //New message
            else if(strcmp(shdata->for_who, "server") == 0 && shdata->count == -2)
            {
                printf("OldUser\n");
                char new_mes[40] = "";
                if(strcmp(shdata->data[0], "exit") == 0){
                    arg->message_number++;
                    arg->message_buf[arg->message_number-1] = malloc(sizeof(char) * 20);
                    arg->message_buf[arg->message_number-1][0] = '\0';
                    strcat(new_mes, "User ");
                    strcat(new_mes, shdata->from_who);
                    strcat(new_mes, " exit");

                    strcpy(shdata->data[1], shdata->from_who);
                    strcat(shdata->data[2], "exit");
                    shdata->data[2][4] = '\0';
                    for (int i = 0; i < arg->user_number; ++i)
                    {
                        int eq = strcmp(shdata->from_who,arg->user_buf[i]);
                        if(eq == 0){
                            if(i < (arg->user_number - 1)){
                                for (int j = i; j < arg->user_number-1; ++j)
                                {
                                    arg->user_buf[j][0] = '\0';
                                    strcat(arg->user_buf[j],arg->user_buf[j+1]);
                                }
                            }else{
                                arg->user_buf[i][0] = '\0';
                            }
                        }
                        printf("s[%d] = %s\n", i, arg->user_buf[i]);
                    }
                    arg->user_number -= 1;

                }else{
                    arg->message_number++;
                    arg->message_buf[arg->message_number-1] = malloc(sizeof(char) * 20);
                    arg->message_buf[arg->message_number-1][0] = '\0';
                    strcat(new_mes, shdata->from_who);
                    strcat(new_mes, ": ");
                    strcat(new_mes, shdata->data[0]);
                }
                strcpy(arg->message_buf[arg->message_number-1], new_mes);
                
                shdata->count = -1;
                strcpy(shdata->for_who, "server");
                printf("=================================\n");
                send_time = 1;
            }
        }

        if((semop(semid, &unlock, 1)) == -1)
        {
            printf("Semop");
            exit(1);
        }
        use++;
    }

}

// //Отправка
void *send_part(void* args)
{
    struct arg_struct_cl *arg = (struct arg_struct_cl*) args;
    int shmid, semid;
    key_t shkey, semkey;
    int size = SHM_SIZE;
    
    struct shmemdata *shdata;

    struct sembuf lock[2] = {{0,0,0},{0,1,0}};
    struct sembuf unlock= {0,-1,0};
    
    shkey = ftok("mshmem3.txt",'m');
    if(shkey == (key_t)-1)
    {
        perror("Ftok shered mem");
        exit(1);
    }

    //Create piece of shared memory 
    shmid = shmget(shkey, size, 0666 | IPC_CREAT);
    if(shmid == -1){
        perror("ShmgetSend");
        exit(1);
    }

    //Semafor

    //Create key for sem
    semkey = ftok("msemmem3.txt",'m');
    if(semkey == (key_t)-1)
    {
        perror("Ftok semafor");
        exit(1);
    }

    sleep(20);

    semid = semget(semkey, 2, 0666);
    if(semid == -1){
        perror("SemgetSend");
        exit(1);
    }

    shdata = (struct shmemdata*)shmat(shmid,NULL,0);// Create piece of shared memory

    if(shdata == (struct shmemdata*)-1) // Return void
    {
        perror("Shmat");
        exit(1);
    }

    int send_by_user = 0;
    int send_by_message = 0;

    int send_all = 0;

    int use = 0;

    int recieve_time = 0;
    int users_send = -1;

	while(1)
    {
        if((semop(semid, &lock[0], 2)) == -1)
        {
            printf("Semop");
            exit(1);
        }

        if(use == 0){
            sleep(7);
            use++;
        }

        if(recieve_time == 1 ){
            sleep(9);
            recieve_time = 0;
        }

        if((shdata->count == -1 || shdata->count == -3) && strcmp(shdata->for_who, "server") == 0)
        {
            printf("Send: Users: %d | Messages: %d\n", arg->user_number, arg->message_number);
            printf("New information!\n");
            //Send all users and messages for new user
            if(send_by_user < arg->user_number)
            {
                printf("NewUser for send!\n");
                //Send all users
                if(send_all == 0)
                {
                    users_send++;
                    printf("send %d users\n", arg->user_number);
                    for (int i = 0; i < arg->user_number; ++i)
                    {
                        strcpy(shdata->data[i], arg->user_buf[i]);
                        shdata->data[i][strlen(arg->user_buf[i])] = '\0';
                        printf("send user: %s\n", arg->user_buf[i]);
                    }
                    send_all++;
                    strcpy(shdata->from_who, "server");
                    shdata->count = arg->user_number;
                    strcpy(shdata->for_who, arg->user_buf[users_send]);
                    printf("=================================\n");
                }
                //Send all messages
                else if(send_all == 1)
                {
                    printf("send %d messages\n", arg->message_number);
                    for (int i = 0; i < arg->message_number; ++i)
                    {
                        strcpy(shdata->data[i], arg->message_buf[i]);
                        printf("send mess: %s\n", arg->message_buf[i]);
                    }
                    strcpy(shdata->from_who, "server");
                    strcpy(shdata->for_who, arg->user_buf[users_send]);
                    shdata->count = arg->message_number;
                    printf("=================================\n");
                    send_all = 2;
                }
                //Send new message for all user
                else if(send_all == 2 ){
                    printf("Need to send all?\n");
                    send_by_user++;
                    if(send_by_user == arg->user_number && arg->user_number > 1){
                        printf("Yes!\n");
                        shdata->count = -3;
                        strcpy(shdata->for_who, "server");
                    }else{
                        printf("No! us_num = %d\n", arg->user_number);
                        shdata->count = 0;
                        strcpy(shdata->for_who, "me");

                    }
                    send_all = 0;
                }
                printf("message_number: %d | user_number: %d\n", arg->message_number, arg->user_number);
                printf("=================================\n");
            }
            //Send only one message
            else if((send_by_message < arg->message_number) || (shdata->count == -3 && arg->user_number > 1))
            {
                printf("Send for all users!\n");
                //for all users
                if(shdata->count == -3){
                    printf("am | %d\n", shdata->count );
                    strcpy(shdata->data[1], arg->user_buf[arg->user_number-1]);
                    strcpy(shdata->data[2], "user");
                    shdata->count = arg->user_number - 1;  
                }else{
                    printf("am %d\n", shdata->count);
                    printf("user_number: %d\n", arg->user_number);
                    shdata->count = arg->user_number;
                }
                strcpy(shdata->for_who, "all");
                strcpy(shdata->from_who, "server");

                strcpy(shdata->data[0], arg->message_buf[arg->message_number-1]);
                printf("for %d send %s\n", arg->user_number, arg->message_buf[arg->message_number-1]);

                printf("=================================\n");
                recieve_time = 1;
                send_by_message++;

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
	int message_number = 0;
	int user_number = 0;
    int shmid, semid;
    struct arg_struct_cl args;
    int *s;
    args.message_number = 0;
    args.user_number = 0;

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
    //===============================

    if(semctl(semid, 1, IPC_RMID) == -1)
    {
        perror("SemctlAll");
        return -1;
    }

    //Disconnect
    if(shmctl(shmid,IPC_RMID,NULL) == -1)
    {
            perror("ShmctlAll");
            exit(1);
    }
    
    //Delete files for ftok
    unlink("mshmem3.txt");
    unlink("msemmem3.txt");

    return 0;
}
