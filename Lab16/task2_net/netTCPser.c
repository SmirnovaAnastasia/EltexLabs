#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

#define MAX 80 

int main() 
{ 
	int sockfd = 0, clientfd; 
	struct sockaddr_in servaddr, client_addr; 
	socklen_t client_length = sizeof(client_addr);
	int ret;

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	if (sockfd == -1) { 
		printf("socket failed\n"); 
		return(0);
	} 

	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(7777); 

	ret = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	if (ret != 0) { 
		printf("bind failed\n"); 
		return(0); 
	} 

	ret = listen(sockfd, 1);
	if (ret != 0) { 
		printf("listen failed\n"); 
		return(0);
	}

	clientfd = accept(sockfd, (struct sockaddr *)&servaddr, &client_length); 

	if (clientfd > 0) {  

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
}
