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
#include<stdint.h>
#include <pthread.h>

#include "fun.h"


int main()
{
    pid_t child_pid;
    int status;
	int main_sock;
	int *s;
	int ret;
	int fd[3][2];
    int arr[3];
	struct sockaddr_in mainserv;
    
    Pthstr info[3];
    int numport = 7770;

    //Создаем главный поток

    memset((char *) &mainserv, 0, sizeof(mainserv));
    main_sock = made_socket(&mainserv, 7770);
    
	char buf[256];
	memset(&buf, 0, sizeof(buf)); 

	int slen = sizeof(mainserv);

    //Создаем очередь

	Queue que;
	initializeQueue(&que);

    //Потоки
    pthread_t thread[4];

    //Создаем три процесса для работы

    int qport = 7770;


    for (int i = 0; i < 3; ++i)
	{
        arr[i] = i + 1;
        info[i].in = arr[i];
        info[i].que = &que;
        printf("info.in = %d\n", info[i].in);
		int j = pthread_create(&thread[i], NULL, other_ser, (void*)&info[i]);	
		if(j){
			printf("ERROR: thread isn't create!");
			exit(EXIT_FAILURE);
		}
	}

    int i = 1;

    //Работаем с запросами клиентов
    while(1)
    {
        //Получаем запрос
        ret = recvfrom(main_sock, buf, 256, 0, (struct sockaddr *) &mainserv, &slen); 
        if (ret == -1)
        {
            perror("recvfrom user error");
            return 0;
        }

        //Генерим порт
        printf("Server recieve mes = %s\n", buf);
        int port = numport + i;
        int dport = port;
        i++;

        //Переводим в чар
        char whmes[6];
        for (int j = 3; j >= 0; j--)
        {
            int in = (dport % 10);
            // printf("in = %d\n", in);
            whmes[j] = in + '0';
            dport = dport / 10;
        }
        whmes[5] = '\0';

        printf("Server send new port - %s\n", whmes);
        
        //Отправляем номер порта
        ret = sendto(main_sock, whmes, 6, 0 , (struct sockaddr *) &mainserv, slen);

        if(ret == -1)
        {
            perror("sendto error");
            return 0;
        }

        printf("Add new to queue: %d\n", port);
        //Добавляем порт в очередь
        printf("isEmpty: %d\n", isEmpty(&que));
        
        addQueue(&que, port);
        // printf("Que count: %d | %d\n", que.count, isEmpty(&que));

        printf("=========================\n");

    }

    for (int i1 = 0; i1 < 3; ++i1)
	{
		pthread_join(thread[i1], (void**)&s);
	}
    
	return 0;
}