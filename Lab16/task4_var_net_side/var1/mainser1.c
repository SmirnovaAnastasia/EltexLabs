#include <stdio.h>
#include<sys/socket.h>
#include <string.h>

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

void other_ser(int port, int in)
{

	int other_sock;
	struct sockaddr_in other_serv;

	//Только прием
	int ret;

	// Create new addr
	other_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (other_sock == -1)
	{
		perror("socket failed");
		exit(1);
	}
	
	memset((char *) &other_serv, 0, sizeof(other_serv));
	
	other_serv.sin_family = AF_INET;
	other_serv.sin_port = htons(port);
	other_serv.sin_addr.s_addr = inet_addr("127.0.0.2");
	
	ret = bind(other_sock , (struct sockaddr*)&other_serv, sizeof(other_serv));
	if(ret == -1)
	{
		perror("bind failed");
		exit(1);
	}

	while(1)
	{
		int slen = sizeof(other_serv);
		char buf[256];
		memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер
		
		ret = recvfrom(other_sock, buf, 256, 0, (struct sockaddr *) &other_serv, &slen);
		if(ret == -1)
		{
			perror("recvfrom failed");
			exit(1);
		}

		printf("Server %d recieve buf = %s\n", in, buf);
	}
}

int main()
{
	pid_t child_pid;
	int status;
	int ser_sock;
	int *s;
	int ret;

	struct sockaddr_in serv;

	// Create main sock
	ser_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (ser_sock == -1)
	{
		perror("socket failed");
		return 0;
	}
	
	memset((char *) &serv, 0, sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(7770);
	serv.sin_addr.s_addr = inet_addr("127.0.0.2");
	
	ret = bind(ser_sock , (struct sockaddr*)&serv, sizeof(serv));
	if(ret == -1)
	{
		perror("bind failed");
		return 0;
	}

	int newport = 7770;

	char buf[256];
	memset(&buf, 0, sizeof(buf)); // Выделяем память под буфер

	for(int i = 0; i < 5;i++)
	{
		printf("Try i = %d\n", i);

		int slen = sizeof(serv);
		int in = i;

		newport++;
		int port = newport;

		sleep(3);

		//Resv from user
		ret = recvfrom(ser_sock, buf, 256, 0, (struct sockaddr *) &serv, &slen); 
		if (ret == -1)
		{
			perror("recvfrom error");
			return 0;
		}

		printf("Server recieve mes = %s\n", buf);
		

		char mes[5];
		memset(&mes, 0, sizeof(mes));

		for (int j = 0; j < 3; j++)
		{
			mes[j] =  7 + '0';
		}

		mes[3] = (newport % 10) + '0';	
		mes[4] = '\0';
		printf("Server send new port - |%s|\n", mes);	
		
		ret = sendto(ser_sock, mes, 4, 0, (struct sockaddr*) &serv, slen);
		if(ret == -1)
		{
			perror("sendto failed");
			return 0;
		}

		child_pid = fork();
		if(child_pid == 0){
			other_ser(port, in);
			exit(5);
		}


		sleep(5);
	}
	return 0;
}