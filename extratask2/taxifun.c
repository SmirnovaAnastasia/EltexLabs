#include "taxih.h"

//Create command and take his pid
pid_t create_driver()
{

    pid_t pid = fork();  

    if (pid < 0) {
        perror("fork failed");
        exit(0);
    }


    else if (pid == 0) {
        while(1)
        {
            char filename[20];
            snprintf(filename, sizeof(filename), "%d", getpid());

            int sockfd_child, sockfd_non_block;
            int ret;
            struct sockaddr_in child_addr;
            int child_len = sizeof(child_addr);
            char child_buffer[BUFFER_SIZE];

            memset(&child_buffer, 0, sizeof(child_buffer));
            memset(&child_addr, 0, sizeof(child_addr));


            sockfd_child= socket(AF_INET, SOCK_DGRAM, 0);
            if(sockfd_child == -1)
            {
                perror("socket error");
                exit(EXIT_FAILURE);
            }

            child_addr.sin_family = AF_INET;
            child_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); ///!!!!
            child_addr.sin_port = htons(getpid()); ///!!!!

            ret = bind(sockfd_child, (const struct sockaddr*)&child_addr, child_len);
            if(ret == -1 )
            {
                perror("bind error");
                exit(EXIT_FAILURE);
            }

            while (1)
            {
                
                ret = recvfrom(sockfd_child, child_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&child_addr, &child_len);
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    int b = 0;
                }
                else if(ret == -1 )
                {
                    perror("recvfrom error");
                    exit(EXIT_FAILURE);
                }

                // printf("Find: %s\n", child_buffer);

                if(strcmp(child_buffer, "FREE") == 0 || strcmp(child_buffer, "OK") == 0 || strcmp(child_buffer, "BUSY") == 0 || strcmp(child_buffer, "") == 0)
                {
                    continue;
                }else if(strcmp(child_buffer, "ADD") == 0){
                    child_buffer[0] = '\0';
                    strcat(child_buffer, "FREE");
                    ret = sendto(sockfd_child, child_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&child_addr, child_len);
                    if(ret == -1 )
                    {
                        perror("sendto error");
                        exit(EXIT_FAILURE);
                    }
                    continue;
                }

                int timer_int = atoi(child_buffer);
                // printf("Int: %d\n", timer_int);

                child_buffer[0] = '\0';
                strcat(child_buffer, "OK");
                ret = sendto(sockfd_child, child_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&child_addr, child_len);
                if(ret == -1 )
                {
                    perror("sendto error");
                    exit(EXIT_FAILURE);
                }

                // printf("Driver %d send: %s\n", getpid(), child_buffer);

                int msec = 0, trigger = timer_int * 1000;
                clock_t before = clock();

                struct timeval read_timeout;
                read_timeout.tv_sec = 0;
                read_timeout.tv_usec = trigger;

                if (fcntl(sockfd_child, F_SETFL, O_NONBLOCK, 1) == -1) {
                    exit(EXIT_FAILURE);
                }

                do         
                {
                    ret = recvfrom(sockfd_child, child_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&child_addr, &child_len);
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        int a = 0;
                    }
                    else if(ret == -1 )
                    {
                        perror("recvfrom error");
                        exit(EXIT_FAILURE);
                    }


                    child_buffer[0] = '\0';
                    strcat(child_buffer, "BUSY");

                    ret = sendto(sockfd_child, child_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&child_addr, child_len);
                    if(ret == -1 )
                    {
                        perror("sendto error");
                        exit(EXIT_FAILURE);
                    }
                    
                    clock_t difference = clock() - before;
                    msec = difference * 1000 / CLOCKS_PER_SEC;
                }while(msec < trigger);

                if (fcntl(sockfd_child, F_SETFL, O_NONBLOCK, 0) == -1) {
                    exit(EXIT_FAILURE);
                }

            } 

            close(sockfd_child);
        }
    }else{
        return pid;
    }
}



//Create task for driver (mb signal), we need send time
void send_task(int pid, int task_timer)
{
    int sockfd_fun;
    int ret;
    struct sockaddr_in par_addr;
    int par_len = sizeof(par_addr);
    char par_buffer[BUFFER_SIZE];

    memset(&par_buffer, 0, sizeof(par_buffer));
    memset(&par_addr, 0, sizeof(par_addr));

    sprintf(par_buffer, "%d", task_timer);

    sockfd_fun = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_fun == -1)
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    par_addr.sin_family = AF_INET;
    par_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    par_addr.sin_port = htons(pid);
        
    ret = sendto(sockfd_fun, par_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&par_addr, par_len);
    if(ret == -1 )
    {
        perror("sendto error");
        exit(EXIT_FAILURE);
    }

    printf("Function send: %s\n", par_buffer);

    ret = recvfrom(sockfd_fun, par_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&par_addr, &par_len);
    if(ret == -1 )
    {
        perror("recvfrom error");
        exit(EXIT_FAILURE);
    }

    if(strcmp(par_buffer, "OK") == 0){
        printf("Driver %d start his task\n", pid);
    }else{
        printf("Driver %d is busy now\n", pid);
    }
    
}

//Get status of driver
void get_status(pid_t *arr_drivers, int *status, int *number_of_drivers, char *cli_pid)
{
    pid_t cli_pid_int = atoi(cli_pid);
    
    int num = search_driver(arr_drivers, cli_pid_int, number_of_drivers);

    if(num == -1)
    {
        printf("Can't find driver with this number\n");
    }else{
         int sockfd_fun;
        int ret;
        struct sockaddr_in par_addr;
        int par_len = sizeof(par_addr);
        char par_buffer[BUFFER_SIZE] = "ADD";

        memset(&par_buffer, 0, sizeof(par_buffer));
        memset(&par_addr, 0, sizeof(par_addr));

        sockfd_fun = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd_fun == -1)
        {
            perror("socket error");
            exit(EXIT_FAILURE);
        }
        
        par_addr.sin_family = AF_INET;
        par_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
        par_addr.sin_port = htons(arr_drivers[num]);
        printf("port: %d\n", arr_drivers[num]);
       
        strcat(par_buffer, "ADD");
       
        ret = sendto(sockfd_fun, par_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&par_addr, par_len);
        if(ret == -1 )
        {
            perror("sendto error");
            exit(EXIT_FAILURE);
        }

        ret = recvfrom(sockfd_fun, par_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&par_addr, &par_len);
        if(ret == -1 )
        {
            perror("resvfrom error");
            exit(EXIT_FAILURE);
        }

        if(strcmp(par_buffer, "BUSY") == 0){
            printf("%d        BUSY\n", arr_drivers[num]);
        }else if(strcmp(par_buffer, "FREE") == 0){
            printf("%d        FREE\n", arr_drivers[num]);
        }
    }
    
}

//Print all list of drivers
void get_drivers(pid_t *arr_drivers, int *status, int *number_of_drivers)
{
    printf("Number    Status  All: %d\n", *number_of_drivers);
    for (int i = 0; i < *number_of_drivers; i++)
    {
        int sockfd_fun;
        int ret;
        struct sockaddr_in par_addr;
        int par_len = sizeof(par_addr);
        char par_buffer[BUFFER_SIZE] = "ADD";

        struct timeval timer_out;
        timer_out.tv_sec = 2 * 1000;

        memset(&par_buffer, 0, sizeof(par_buffer));
        memset(&par_addr, 0, sizeof(par_addr));


        sockfd_fun = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd_fun == -1)
        {
            perror("socket error");
            exit(EXIT_FAILURE);
        }

        par_addr.sin_family = AF_INET;
        par_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); ///!!!!
        par_addr.sin_port = htons(arr_drivers[i]); ///!!!!

        strcat(par_buffer, "ADD");
       
        ret = sendto(sockfd_fun, par_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&par_addr, par_len);
        if(ret == -1 )
        {
            perror("sendto error");
            exit(EXIT_FAILURE);
        }

        ret = recvfrom(sockfd_fun, par_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&par_addr, &par_len);
        if(ret == -1 )
        {
            perror("resvfrom error");
            exit(EXIT_FAILURE);
        }

        if(strcmp(par_buffer, "BUSY") == 0){
            printf("%d        1\n", arr_drivers[i]);
        }else if(strcmp(par_buffer, "FREE") == 0){
            printf("%d        0\n", arr_drivers[i]);
        }
    }
    
}
