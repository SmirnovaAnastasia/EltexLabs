#include<stdio.h>	//for printf
#include<string.h> //memset
#include<sys/socket.h>	//for socket ofcourse
#include<stdlib.h> //for exit(0);
#include<errno.h> //For errno - the error number
#include<netinet/udp.h>	//udp header
#include<netinet/ip.h>	//ip header
#include<netinet/if_ether.h> //ethernet header
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<net/if.h> //for if_nameindex

#include<netpacket/packet.h>
#include<ifaddrs.h>

#include<net/ethernet.h>

#include<linux/in.h>
#include<netinet/in.h>

#include "eth.h"

int main()
{
	int cli_fd, ret;
	struct sockaddr_ll ser_str = {0};
	struct udphdr udp_header;
	struct iphdr ip_header; 
    struct ethhdr eth_header;

	unsigned char my_mac[6] = CLI_MAC;
	unsigned char des_mac[6] = SER_MAC;

	char forcheck[1024];

	char message[7] = "Hello!";
	char buf[1500];
 
	cli_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (cli_fd == -1)
	{
		perror("socket error");
		return 0;
	}

	//Fill udp_header
	udp_header.uh_sport = htons(7777);
	udp_header.uh_dport = htons(41324);
	udp_header.len = htons(sizeof(struct udphdr)+ sizeof(message));
	udp_header.check = 0;

	//Fill ip_header
	ip_header.ihl = 5; //header lenght
	ip_header.version = 4;
	ip_header.tos = 0;
	ip_header.id = 0;
	ip_header.tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(message));
	ip_header.frag_off = 0;
	ip_header.ttl = 255; //life cycle
	ip_header.protocol = IPPROTO_UDP;	
	ip_header.check = 0; 
	ip_header.saddr = inet_addr(MY_ADDR);
	ip_header.daddr = inet_addr(SER_ADDR);

	ip_header.check = count_checksum((uint16_t*)&ip_header, ip_header.ihl * 4);

    //Fill eth_header

    eth_header.h_source[0] = 0x08; //Sour
    eth_header.h_source[1] = 0x00;
    eth_header.h_source[2] = 0x27;
    eth_header.h_source[3] = 0x83;
    eth_header.h_source[4] = 0x72;
    eth_header.h_source[5] = 0xaa;

	// memcpy(eth_header.h_source, my_mac, 6);

    eth_header.h_dest[0] = 0x08; //Dest
    eth_header.h_dest[1] = 0x00;
    eth_header.h_dest[2] = 0x27;
    eth_header.h_dest[3] = 0xc5;
    eth_header.h_dest[4] = 0xf2;
    eth_header.h_dest[5] = 0x10;

	// memcpy(eth_header.h_dest, des_mac, 6);

    eth_header.h_proto = htons(ETH_P_IP);

	// Fill sockaddr_ll
	ser_str.sll_family = AF_PACKET; //!always
    ser_str.sll_protocol = htons(ETH_P_ALL); 
    ser_str.sll_ifindex = if_nametoindex("enp0s3");//number for who
    ser_str.sll_halen = ETH_ALEN;

    ser_str.sll_addr[0] = 0x08; //Dest
    ser_str.sll_addr[1] = 0x00;
    ser_str.sll_addr[2] = 0x27;
    ser_str.sll_addr[3] = 0xc5;
    ser_str.sll_addr[4] = 0xf2;
    ser_str.sll_addr[5] = 0x10;

	// memcpy(ser_str.sll_addr, des_mac, 6);

	printf("Create socket!\n");

	memcpy(buf, &eth_header, sizeof(eth_header));
    memcpy((buf + sizeof(eth_header)), &ip_header, sizeof(ip_header));
	memcpy((buf + sizeof(eth_header) + sizeof(ip_header)), &udp_header, sizeof(udp_header));
	memcpy((buf + sizeof(eth_header) + sizeof(ip_header) + sizeof(udp_header)), message, sizeof(message));

	int buf_len = sizeof(eth_header) + sizeof(ip_header) + sizeof(udp_header) + sizeof(message);

	while(1)
	{
		sleep(3);
		ret = sendto(cli_fd, buf, buf_len, 0, (struct sockaddr *) &ser_str, sizeof(ser_str)); 
		if (ret == -1)
		{
			perror("recvfrom error");
			return 0;
		}


		printf("Client send message: %s\n", message);

		//=======================

		// int lent = sizeof(ser_str);

		// ret = recvfrom(cli_fd, buf, buf_len, 0, NULL, NULL); 
		// if (ret == -1)
		// {
		// 	perror("recvfrom error");
		// 	return 0;
		// }

		// printf("Client resieve message: %s\n", buf);

	}
	close(cli_fd);
	return 0;
}
