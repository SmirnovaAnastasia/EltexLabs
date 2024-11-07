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

	servfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (servfd == -1)
	{
		perror("socket error");
		return 0;
	}

	memset((char *) &serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(6666);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	char buf[256];
	memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер

	ret = bind(servfd, (struct sockaddr *)&serv, sizeof(serv));
	if(ret == -1)
	{
		perror("bind error");
		return 0;
	}

	printf("Work!\n");
	sleep(2);
	
	while(1)
	{
		ret = recvfrom(servfd, buf, 256, 0, (struct sockaddr *) &serv, &slen); 
		if (ret == -1)
		{
			perror("recvfrom error");
			return 0;
		}

		printf("Client recieve buf = %s\n", buf);
		
	}
	close(servfd);
	return 0;
}