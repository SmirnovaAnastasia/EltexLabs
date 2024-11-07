#include<stdio.h>	
#include<string.h> 
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

int main(void)
{
	struct sockaddr_in serv;
	int servfd, i, slen = sizeof(serv);
	int ret;

    //First connect
	servfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (servfd == -1)
	{
		perror("socket error");
		return 0;
	}

	memset((char *) &serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(7770);
	serv.sin_addr.s_addr = inet_addr("127.0.0.2");

	char buf[256];
	memset(&buf, 0, sizeof(buf));

    //Send hello
    ret = sendto(servfd, "hello", 5, 0 , (struct sockaddr *) &serv, slen);
        printf("Client send \"hello\"\n");

    if(ret == -1)
    {
        perror("sendto error");
        return 0;
    }

    //Recv new port
    //printf("Try recive!\n");
    ret = recvfrom(servfd, buf, 256, 0, (struct sockaddr *) &serv, &slen); 
    if (ret == -1)
    {
        perror("recvfrom error");
        return 0;
    }

    printf("Client recieve new port = %s\n", buf);

    char *am;
    int port = 7770;
    port += buf[3] - '0';
    printf("New port - %d\n", port);

    //Second connect with new port
    servfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (servfd == -1)
	{
		perror("socket error");
		return 0;
	}

	memset((char *) &serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = inet_addr("127.0.0.2");

    sleep(3);


    while(1){
        ret = sendto(servfd, "hello", 5, 0 , (struct sockaddr *) &serv, slen);
        printf("Client send \"hello\"\n");

        if(ret == -1)
        {
            perror("sendto error");
            return 0;
        }

        sleep(2);
    }

	close(servfd);
	return 0;
}