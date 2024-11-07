#include "eth.h"

int count_checksum(uint16_t* buf, int len)
{
    unsigned long sum = 0;

	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	
	if(len == 1)
	{
		sum += *(uint8_t*)buf;
	}

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
    return ~sum;
}