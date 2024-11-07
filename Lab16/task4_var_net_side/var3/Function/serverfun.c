#include <stdio.h>
#include<sys/socket.h>
#include <string.h>

#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <signal.h>
#include <time.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>

#include "../fun.h"

#define READ 0
#define WRITE 1

int made_socket(struct sockaddr_in *serv, int port)
{
    int ret;
    // Create main sock
	int ser_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (ser_sock == -1)
	{
		perror("socket failed");
		return 0;
	}
	
	
	serv->sin_family = AF_INET;
	serv->sin_port = htons(port);
	serv->sin_addr.s_addr = inet_addr("127.0.0.2");
	
	ret = bind(ser_sock , (struct sockaddr*)serv, sizeof(*serv));
	if(ret == -1)
	{
		perror("bind failed");
		return 0;
	}

    return ser_sock;
}

void *other_ser(void *info)
{

    while(1){
        Pthstr info2 = *(Pthstr*)info;
        printf("Server %d waits!\n", info2.in);

        while (isEmpty(info2.que) == 1)
        {
            //printf("Que count: %d\n", isEmpty(que) );
        }
        
        printf("Server %d starts work!\n", info2.in);

        int port = peek(info2.que);
        printf("Port: %d\n", port);
        delQueue(info2.que);

        // if(port >= 7777){
        //     port--;
        // }
        // printf("Port: %d\n", port);

        //Do new socket for connect with client
        struct sockaddr_in other_serv;
        int other_sock = made_socket(&other_serv, port);

        //Только прием
        int ret;

        char buf[256];
        memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер
        int slen = sizeof(other_serv);
    
        do
        {
            ret = recvfrom(other_sock, buf, 256, 0, (struct sockaddr *) &other_serv, &slen);
            if(ret == -1)
            {
                perror("recvfrom failed");
                exit(1);
            }

            printf("Server %d recieve buf = %s\n", info2.in, buf);
        }while(strcmp(buf, "exit") != 0);

        sleep(1);
        
    }
}