#ifndef ETH_H
#define ETH_H

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
#include<net/if.h>

#include<netpacket/packet.h>
#include<ifaddrs.h>

#include<net/ethernet.h>

#include<linux/in.h>
#include<netinet/in.h>

#define SER_MAC {0x08, 0x00, 0x27, 0xc5, 0xf2, 0x10}
#define CLI_MAC {0x08, 0x00, 0x27, 0x83, 0x72, 0xaa}
#define MY_ADDR "192.168.56.101"
#define SER_ADDR "192.168.56.102"

int count_checksum(uint16_t* buf, int len); 

#endif