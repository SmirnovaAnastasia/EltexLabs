#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/un.h>

// # define SER_PATH "/tmp/stream_ser"
# define CLI_PATH "/tmp/stream_cli"


int main(void)
{
	int sockfd = 0;
	struct sockaddr_un serv, client_addr; // Структуры для передачи
	
	int clientfd = 0;
	int ret = 0;

	int slen = sizeof(client_addr), recv_len;
	
	sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		perror("socket failed");
		return 0;
	}
	
	// bzero(&serv, sizeof(serv)); // Выделяем место под структуру
	// serv.sun_family = AF_LOCAL; // Заполняем структуру
	// strcpy(serv.sun_path, SER_PATH);

	bzero(&client_addr, sizeof(client_addr)); // Выделяем место под структуру
	client_addr.sun_family = AF_LOCAL; // Заполняем структуру
	strcpy(client_addr.sun_path, CLI_PATH);


	unlink(CLI_PATH);
	ret = bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
	if(ret == -1)
	{
		perror("bind error");
		return 0;
	}

	sleep(5);
	
	//fflush(stdout); //???
	char buf[256];
	memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер

	ret = recvfrom(sockfd, buf, 256, 0, (struct sockaddr *) &client_addr, &slen);
	
	if (ret == -1)
	{
		perror("recieve failed");
		return 0;
	}

	printf("Server recieve buf = %s\n", buf);
	
	// printf("Received packet from %sockfd:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	// printf("Data: %sockfd\n" , buf);
	
	printf("Server send \"hi\"\n");

	ret = sendto(sockfd, "hi", 2, 0, (struct sockaddr*) &client_addr, slen);
	if (ret == -1)
	{
		perror("recieve failed");
		return 0;
	}

	close(sockfd);
	return 0;
}