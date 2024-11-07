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

#define STREAM_SERVER_MSG_FILE "/tmp/local_server_tcp"

int main(int argc, char *argv[])
{
	int ret;
	int sockfd; // Дискриптор
	struct sockaddr_un serv;

	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		perror("socket error");
		return -1;
	}

	bzero(&serv, sizeof(serv));
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, STREAM_SERVER_MSG_FILE);

	ret = connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	// Запоминаем, куда отправляем все данные

	if(ret < 0)
	{
		close(sockfd);
		perror("connect error");
		return -3;
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

	return 0;
}