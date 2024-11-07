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

	servfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (servfd == -1)
	{
		perror("socket error");
		return 0;
	}

	memset((char *) &serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8888);
	serv.sin_addr.s_addr = INADDR_ANY;

	char buf[256];
	memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер

	ret = sendto(servfd, "hello", 5, 0 , (struct sockaddr *) &serv, slen);
	printf("Client send \"hello\"\n");

	if(ret == -1)
	{
		perror("sendto error");
		return 0;
	}

	sleep(2);
	
	ret = recvfrom(servfd, buf, 256, 0, (struct sockaddr *) &serv, &slen); 
	if (ret == -1)
	{
		perror("recvfrom error");
		return 0;
	}

	printf("Client recieve buf = %s\n", buf);
	
	close(servfd);

	close(servfd);
	return 0;
}