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
	struct sockaddr_in serv, client_addr;
	
	int ret;
	int sockfd, i, slen = sizeof(client_addr);
	
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (sockfd == -1)
	{
		perror("socket failed");
		return 0;
	}
	
	memset((char *) &serv, 0, sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8888);
	serv.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(sockfd , (struct sockaddr*)&serv, sizeof(serv));
	if(ret == -1)
	{
		perror("bind failed");
		return 0;
	}


	char buf[256];
	memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер
	
	ret = recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &client_addr, &slen);
	if(ret == -1)
	{
		perror("recvfrom failed");
		return 0;
	}

	printf("Server recieve buf = %s\n", buf);

	printf("Server send \"hi\"\n");
	
	ret = sendto(sockfd, "hi", 2, 0, (struct sockaddr*) &client_addr, slen);
	if(ret == -1)
	{
		perror("sendto failed");
		return 0;
	}

	close(sockfd);
	return 0;
}