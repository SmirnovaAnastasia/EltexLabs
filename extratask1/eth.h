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

#define SERV_ADDR "192.168.0.105"

#define MAX_SIZE 100

typedef struct KeyAndValue
{
    int key;
    int value;
    struct KeyAndValue *next;
} KeyAndValue;

typedef struct
{
    KeyAndValue **table;
    int size;
} HashTable;


int count_checksum(uint16_t* buf, int len); 

unsigned int hash(int key, int size);
HashTable* create_table(int size);
void upset(HashTable *ht, int key, int value);
int get(HashTable *ht, int key, int def_value);
int update(HashTable *ht, int key, int new_value);
void free_table(HashTable *ht);

#endif
