#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "eth.h"

#define PORT 8080
#define BUFFER_SIZE 512

struct udp_packet
{
    struct udphdr udp_header;
    char payload[1024];
};

int main(){
    int sockfd, sockfd2;
    int ret;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);
    int serv_len = sizeof(server_addr);
    char serv_buffer[BUFFER_SIZE] = " ", client_buffer[BUFFER_SIZE] = " ";
    
    HashTable *ht = create_table(10);

    memset(&client_buffer, 0, sizeof(client_buffer));
    memset(&serv_buffer, 0, sizeof(serv_buffer));

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sockfd == -1)
    {
        perror("socket error");
		exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    int optval = 1;
    ret = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(optval));
    if(ret < 0)
    {
        perror("setsockopt error");
        close(sockfd);
		exit(EXIT_FAILURE);
    }

    printf("Server starts work!\n");
    int numofmes = 0;
    char word[512] = " ";

    while (1)
    {
        ret = recvfrom(sockfd, client_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
        if(ret == -1 )
        {
            perror("recvfrom error");
		    exit(EXIT_FAILURE);
        }
        

        struct iphdr *ip_header = (struct iphdr*) client_buffer;
        unsigned int ip_header_len = ip_header->ihl * 4;

        if(ip_header->protocol != IPPROTO_UDP)
        {
            continue;
        }

        struct udphdr *udp_header = (struct udphdr*)(client_buffer + ip_header_len);

        if(udp_header->dest != htons(PORT))
        {
            continue;
        }

        if(get(ht, udp_header->source, -1) >= 0){
            ret = update(ht, udp_header->source, get(ht, udp_header->source, -1) + 1);
        }else{
            upset(ht,udp_header->source, 1);
        }

        int j=0;
        word[0] = '\0';
        // printf("Server recieve: ");
        for (int i = sizeof(struct udphdr) + sizeof(struct iphdr); i < sizeof(client_buffer); i++)
        {
            // printf("%c", client_buffer[i]);
            word[j] = client_buffer[i];
            j++;
        }
        printf("\n");
        
        if(strcmp(word, "Bye") != 0)
        {
            printf("Server recieves message from %d: %s\n", htons(udp_header->source), word);
            strcat(word, " - ");

            // printf("Server makes line: %s\n", word);
            char numch[2] = " ";
            numch[0] = get(ht, udp_header->source, -1) + '0';
            // printf("Char to Int: %s\n", numch);
            strcat(word, numch);
            word[strlen(word)] = '\0';

            // printf("Server makes line: %s\n", word);

            sockfd2 = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
            if(sockfd2 == -1)
            {
                perror("socket error");
                exit(EXIT_FAILURE);
            }

            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(8080);
            server_addr.sin_addr.s_addr = ip_header->saddr;
            // inet_pton(AF_INET, &ip_header->saddr, &server_addr.sin_addr);
            
            struct udp_packet packet;
            memset(&packet, 0, sizeof(packet));

            packet.udp_header.source = htons(8080);
            packet.udp_header.dest = udp_header->source; ///!!!!
            packet.udp_header.len = htons(sizeof(struct udphdr) + 5);
            packet.udp_header.check = 0;

            strcpy(packet.payload, word);
        
            sleep(2);

            ret = sendto(sockfd2, &packet, sizeof(struct udphdr) + strlen(word), 0, (struct sockaddr*)&server_addr, serv_len);
            if(ret == -1 )
            {
                perror("sendto error");
                exit(EXIT_FAILURE);
            }

            printf("Server sends message for %d: %s\n", htons(udp_header->source),word);
        }else{
            ret = update(ht, udp_header->source, 0);
            printf("Client with port %d stops his work\n", htons(udp_header->source));   
        }
    }
    
    close(sockfd);
    return 0;
}