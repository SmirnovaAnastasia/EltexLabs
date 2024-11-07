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

    Pthstr info2 = *(Pthstr*)info;
	printf("Server %d waits!\n", info2.in);

    //Do new socket for connect with server
    // int cowima_sock = made_socket(&cowima_serv, 7770);

	//Только прием
	int ret;

    char buf[256];
    memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер
    int slen = sizeof(info2.other_str);
    
    while(1){
        do
        {
            ret = recvfrom(info2.other_sock, buf, 256, 0, (struct sockaddr *) &info2.other_str, &slen);
            if(ret == -1)
            {
                perror("recvfrom failed");
                exit(1);
            }

            printf("Server %d recieve buf = %s\n", info2.in, buf);
        }while(strcmp(buf, "exit") != 0);

        printf("im free!\n");

        // //Send that we free
        char mes[11];
        char buffer2[256];

        printf("Num: %d\n", (info2.port % 10));
        mes[0] = (info2.port % 10)+ '0';
        strcat(mes, " ser_exit");
        printf("Server %d send \"%s\"\n", info2.in, mes);

        write(info2.fd, mes, 10);

        // read(fd[READ], buffer2, 10);

        // printf("Server %d recieve \"%s\"\n", in, buffer2);
        // write(fd[WRITE], mes, 10);
        
        do
        {
            ret = recvfrom(info2.other_sock, buf, 256, 0, (struct sockaddr *) &info2.other_str, &slen);
            if(ret == -1)
            {
                perror("recvfrom failed");
                exit(1);
            }
            printf("New client!\n");
            printf("Server %d recieve buf = %s\n", info2.in, buf);
        }while(strcmp(buf, "exit") == 0);
        
    }

}