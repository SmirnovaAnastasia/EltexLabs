#include<stdio.h>	//for printf
#include<string.h> //memset
#include<sys/socket.h>	//for socket ofcourse
#include<stdlib.h> //for exit(0);
#include<errno.h> //For errno - the error number
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
	int cli_fd, ret;
	struct sockaddr_in ser_str;
	struct udphdr udp_header;
	struct iphdr ip_header; 

	char message[] = "Hello!";
	char buf[1024];

	cli_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (cli_fd == -1)
	{
		perror("socket error");
		return 0;
	}

	int fl = 1;
	ret = setsockopt(cli_fd, IPPROTO_IP, IP_HDRINCL, &fl, sizeof(fl));
	if (ret < 0)
	{
		perror("setsockopt error");
		return 0;
	}


	//Fill sockaddr_in
	ser_str.sin_family = AF_INET;
	ser_str.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	//Fill udp_header
	udp_header.uh_sport = htons(7777);
	udp_header.uh_dport = htons(6666);
	udp_header.len = htons(sizeof(udp_header)+strlen(message));
	udp_header.check = 0;

	//Fill ip_header
	ip_header.ihl = 5; //header lenght
	ip_header.version = 4;
	ip_header.tos = 0;
	ip_header.id = 0;
	ip_header.tot_len = htons(sizeof(ip_header) + sizeof(udp_header) +strlen(message));
	ip_header.frag_off = 0;
	ip_header.ttl = 255; //life cycle
	ip_header.protocol = IPPROTO_UDP;	
	ip_header.check = 0;
	ip_header.saddr = htonl(INADDR_LOOPBACK);
	ip_header.daddr = htonl(INADDR_LOOPBACK);

	printf("Create socket!\n");

	memcpy((void*)buf, (void*)&ip_header, sizeof(ip_header));
	memcpy((void*)(buf + sizeof(ip_header)), (void*)&udp_header, sizeof(udp_header));
	memcpy((void*)(buf + sizeof(ip_header) + sizeof(udp_header)), (void*)message, sizeof(message));

	int buf_len = sizeof(ip_header) + sizeof(udp_header) + sizeof(message);

	while(1)
	{
		ret = sendto(cli_fd, buf, buf_len, 0, (struct sockaddr *) &ser_str, sizeof(ser_str)); 
		if (ret == -1)
		{
			perror("recvfrom error");
			return 0;
		}

		printf("Client send message: %s\n", message);

		sleep(3);
	}
	close(cli_fd);
	return 0;
}

//Complete