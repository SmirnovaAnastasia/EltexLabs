#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> 
#include <sys/socket.h>
#include <unistd.h> 


int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	int ret;

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sockfd == -1) {
		printf("socket udp failed\n");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(7777);

	//Send

	ret = sendto(sockfd, "hello", 5, 0 , (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Client send \"hello\"\n");

	if(ret == -1)
	{
		perror("sendto error");
		return 0;
	}

	
	sleep(2);

    char buf[256];
    memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер

    int slen = sizeof(servaddr);
	
	ret = recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &servaddr, &slen); 
	if (ret == -1)
	{
		perror("recvfrom error");
		return 0;
	}

	printf("Client recieve buf = %s\n", buf);


	close(sockfd);
}
