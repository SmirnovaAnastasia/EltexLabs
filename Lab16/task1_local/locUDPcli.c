#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/un.h>

# define SER_PATH "/tmp/stream_ser"
# define CLI_PATH "/tmp/stream_cli"

void die(char *sockfd)
{
	perror(sockfd);
	exit(1);
}

int main(void)
{
	int ret;
	struct sockaddr_un serv, cli;
	int sockfd, slen; // Дискриптор

	sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		perror("socket error");
		return -1;
	}

	bzero(&serv, sizeof(serv));
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, SER_PATH);
	slen = sizeof(serv);

	bzero(&cli, sizeof(cli));
	cli.sun_family = AF_LOCAL;
	strcpy(cli.sun_path, CLI_PATH);
	slen = sizeof(cli);

	unlink(SER_PATH);
	ret = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	if(ret == -1)
	{
		perror("bind error");
		return 0;
	}

	sleep(2);

	char buf[256];
	memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер
	//gets(message);
	
	//send the message
	ret = sendto(sockfd, "hello", 256, 0 , (struct sockaddr *) &cli, slen);
	printf("Client send \"hello\"\n");

	if(ret < 0){
        perror("send failed");
        return 0;
    }

    sleep(2);

    ret = recvfrom(sockfd, buf, 256, 0, NULL, NULL);
	if(ret < 0){
        perror("recieve failed");
        return 0;
    }

	printf("Client recieve buf = %s\n", buf);

	close(sockfd);
	return 0;
}