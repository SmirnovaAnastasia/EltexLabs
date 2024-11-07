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
#include <stdint.h>
#include <pthread.h>

#include "fun.h"

#define READ 0
#define WRITE 1


int main()
{
	pid_t child_pid;
	int status;
	int ser_sock[5], main_sock;
	int *s;
	int ret;
	int fd[5][2];
	struct sockaddr_in serv[5];
	struct sockaddr_in mainserv;

	pthread_t thread[5];
	
	Pthstr info[5];
	
	for (int i = 0; i < 5; i++)
	{		
		if(pipe(fd[i])){
			perror("pipe");
			return 1;
		}
	}

	//Make queue
	Queue que;
	initializeQueue(&que);

	//Add all numbers of servers
	for (int i = 0; i < 5; i++)
	{
		addQueue(&que, i+1);
	}

	//Make 5 adresses
    int port = 7771;
	for (int i = 0; i < 5; i++)
    {
        memset((char *) &serv[i], 0, sizeof(serv[i]));
        ser_sock[i] = made_socket(&serv[i], port);
        port++;
    }

	memset((char *) &mainserv, 0, sizeof(mainserv));
    main_sock = made_socket(&mainserv, 7770);
    
	char buf[256];
	memset(&buf, 0, sizeof(buf)); 

	int i = 0;
	int numport = 7770;
	int slen = sizeof(mainserv);

	sleep(2);
	
	while(1)
	{
		printf("===================================\n");
		//If we have server for work
		if(isEmpty(&que) == 0)
		{
			int in = i;
			int inport = 0;
			printf("Try i = %d\n", i+1);

			// numport++;
			// if(numport >= 5){
			// 	port = numport % 5;
			// }else{
			// 	port = numport;
			// }

			sleep(3);


			//Resv from user
			ret = recvfrom(main_sock, buf, 256, 0, (struct sockaddr *) &mainserv, &slen); 
			if (ret == -1)
			{
				perror("recvfrom user error");
				return 0;
			}


			printf("Server recieve mes = %s\n", buf);
			
			//Find substring
			char text[9] = "ser_exit";
			char *substring_ptr = strstr(text, buf);

			//If server
			if(substring_ptr)
			{
				int newel = buf[0] - '0';
				printf("New el - %d", newel);
				addQueue(&que, numport+newel);

			//If user
			}else
			{
				char mes[5];
				memset(&mes, 0, sizeof(mes));

				for (int j = 0; j < 3; j++)
				{
					mes[j] =  7 + '0';
				}


				//Use free port
				int pe = peek(&que);
				inport = numport + pe;
				printf("Peek: %d | port: %d\n", pe, inport);
				delQueue(&que);

				mes[3] = (inport % 10) + '0';	
				mes[4] = '\0';
				printf("Server send new port - |%s|\n", mes);	
				
				ret = sendto(main_sock, mes, 4, 0, (struct sockaddr*) &mainserv, slen);
				if(ret == -1)
				{
					perror("sendto failed");
					return 0;
				}

				//Create process for servers
				// if(in < 5){
				// 	child_pid = fork();
				// 	if(child_pid == 0){
				// 		//close(fd[in][READ]);
				// 		other_ser(fd[in], inport, in, ser_sock[in], &serv[in], main_sock, &mainserv);
				// 		exit(5);
				// 	}else
				// 	{
				// 		close(fd[in][WRITE]);
				// 	}
				// }

				if(in < 5){
					info[in].in = in;
					info[in].que = &que;
					info[in].fd = fd[in][WRITE];
					info[in].other_sock = ser_sock[in];
					info[in].other_str = serv[in];
					info[in].port = inport;
					printf("info.in = %d\n", info[in].in);
					int j = pthread_create(&thread[in], NULL, other_ser, (void*)&info[in]);	
					if(j){
						printf("ERROR: thread isn't create!");
						exit(EXIT_FAILURE);
					}
				}


				i++;
				sleep(5);
			}
			
		//If no, wait mes from server
		}else
		{
			sleep(7);
			char buffer2[256];
			//If server free, add his number
			for (int j = 0; j < 5; j++)
			{
				read(fd[j][READ], buffer2, 10);

				printf("Server recieve mes = %s\n", buf);

				int newel = buf[0] - '0';
				printf("New el - %d\n", newel);
				addQueue(&que, numport+newel);
			}

		}
		printf("===================================\n\n");
	}
	return 0;
}