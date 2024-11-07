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
	int sockfd = 0;
	struct sockaddr_un serv, client_addr; // Структуры для передачи
	
	int clientfd = 0;
	int ret = 0;

	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	socklen_t client_length = sizeof(client_addr);
	// Семейство(локальное), тип(потоковое), протокол

	if(sockfd < 0)
	{
		perror("socket error");
		return 0;
	}

	bzero(&serv, sizeof(serv)); // Выделяем место под структуру
	serv.sun_family = AF_LOCAL; // Заполняем структуру
	unlink(STREAM_SERVER_MSG_FILE);
	strcpy(serv.sun_path, STREAM_SERVER_MSG_FILE);

	ret = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	// Привязываем энпоинт 

	if(ret < 0)
	{
		close(sockfd);
		perror("bind error");
		return 0;
	}

	ret = listen(sockfd, 1); // Передаем дескриптор и длину очереди

	if(ret < 0)
	{
		close(sockfd);
		perror("listen error");
		return 0;
	}

	clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
	// Ожидание подсоединения клиента

	if (clientfd > 0) // При подключении
	{
		char buf[256];
		memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер
		
		// Recieve
		ret = recv(clientfd, &buf, sizeof(buf), 0); // Получаем данные

		if(ret < 0){
			perror("recieve failed");
			return 0;
		}

		printf("Server recieve buf = %s\n", buf);

		// Send
		ret = send(clientfd, "hi", 2, 0); // Отправляем сообщение

		printf("Server send \"hi\"\n");

		if(ret < 0){
			perror("send failed");
			return 0;
		}



		close(clientfd);
	}

	close(sockfd);

	return 0;
}
