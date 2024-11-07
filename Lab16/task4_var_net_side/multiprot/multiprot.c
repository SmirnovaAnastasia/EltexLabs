#include <arpa/inet.h> 
#include <sys/epoll.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <error.h>
#include <unistd.h> 
#include <errno.h>

int main()
{
	int sock_udp, sock_tcp;
	int ret;
	int epollfd;
	int nfds;
	struct sockaddr_in addr_udp, addr_tcp;
	struct epoll_event ev;
	struct epoll_event events[2];

	char buf[] = "Hello, world!";

	//======================================
	//Create sockets
	//======================================

	sock_udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sock_udp  == -1) {
		printf("udp socket create failed\n");
		exit(1);
	}

	bzero(&addr_udp, sizeof(addr_udp)); 

	addr_udp.sin_family = AF_INET;
	addr_udp.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr_udp.sin_port = htons(7777);

	ret = bind(sock_udp , (struct sockaddr*)&addr_udp, sizeof(addr_udp));
	if(ret != 0)
	{
		perror("udp bind failed");
		return 0;
	}

	//-------------------------------

	sock_tcp = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_tcp == -1) {
		printf("tcp socket create failed\n");
		exit(1);
	}

	bzero(&addr_tcp, sizeof(addr_tcp)); 

	addr_tcp.sin_family = AF_INET;
	addr_tcp.sin_addr.s_addr = inet_addr("127.0.0.2");
	addr_tcp.sin_port = htons(8888);

	ret = bind(sock_tcp, (struct sockaddr *)&addr_tcp, sizeof(addr_tcp));

	if (ret != 0) { 
		printf("bind failed\n"); 
		return(0); 
	} 

	ret = listen(sock_tcp, 1);
	if (ret != 0) { 
		printf("listen failed\n"); 
		return(0);
	}

	//======================================
	//Create epoll
	//======================================

	epollfd = epoll_create(2);
	if(epollfd == -1)
	{
		printf("epoll create failed\n");
		exit(1);
	}

	//Add to epoll_ev
	ev.data.fd = sock_udp;
	ev.events = EPOLLIN;

	ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, sock_udp, &ev);
	if(ret == -1)
	{
		printf("epoll_ctl failed\n");
		exit(1);
	}

	ev.data.fd = sock_tcp;
	ev.events = EPOLLIN;

	//Add by epoll_ctl
	ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, sock_tcp, &ev);
	if(ret == -1)
	{
		printf("epoll_ctl failed\n");
		exit(1);
	}

	while (1)
	{
		nfds = epoll_wait(epollfd, events, 2, -1);

		if (nfds == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}else{
				printf("epoll_wait failed\n");
				exit(1);
			}
		}

		char buf[256];
		memset(&buf, 0, sizeof(buf));

		for (int i = 0; i < nfds; ++i)
		{
			if(events[i].events & EPOLLIN)
			{
				if(events[i].data.fd == sock_udp)
				{
					int len = sizeof(addr_udp);
					
					ret = recvfrom(sock_udp, buf, 256, 0, (struct sockaddr *) &addr_udp, &len);
					if(ret == -1)
					{
						perror("udp recvfrom failed");
						return 0;
					}

					printf("Udp server recieve buf = %s\n", buf);

					printf("Udp server send \"hi_udp\"\n");
					
					ret = sendto(sock_udp, "hi_udp", 6, 0, (struct sockaddr*) &addr_udp, len);
					if(ret == -1)
					{
						perror("udp sendto failed");
						return 0;
					}
				}
				if(events[i].data.fd == sock_tcp)
				{
					int addrlen = sizeof(addr_tcp);
					int newfd = accept(sock_tcp, (struct sockaddr *)&addr_tcp, &addrlen); 
					
					ret = recv(newfd, &buf, sizeof(buf), 0);

					if(ret < 0){
						perror("tcp recieve failed");
						return 0;
					}

					printf("Tcp server recieve buf = %s\n", buf);

					ret = send(newfd, "hi_tcp", 6, 0);

					printf("Tcp server send \"hi_tcp\"\n");

					if(ret < 0){
						perror("tcp send failed");
						return 0;
					}
							
				}

			}
		
		}
	}
	
	close(sock_udp);
	close(sock_tcp);
	return 0;
}