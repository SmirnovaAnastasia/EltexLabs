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
	
	char message[] = "Hello!";
	char buf[1024];

	cli_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (cli_fd == -1)
	{
		perror("socket error");
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

	printf("Create socket!\n");

	memcpy((void*)buf, (void*)&udp_header, sizeof(udp_header));//???
	memcpy((void*)(buf + sizeof(udp_header)), (void*)message, sizeof(message));//???

	int buf_len = sizeof(udp_header) + sizeof(message);

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