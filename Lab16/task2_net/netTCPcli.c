#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> 
#include <sys/socket.h>
#include <unistd.h> 

#define MAX 80

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	int ret;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(7777);

	ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	if (ret != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}

	//Send
	ret = send(sockfd, "hello", 5, 0); // Отправляем сообщение

    printf("Client send \"hello\"\n");

	if(ret < 0){
        perror("send failed");
        return 0;
    }

    sleep(2);

    char buf[256];
    memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер

    ret = recv(sockfd, &buf, sizeof(buf), 0); // Получаем данные

    if(ret < 0){
        perror("recieve failed");
        return 0;
    }

    printf("Client recieve buf = %s\n", buf);


	close(sockfd);
}
