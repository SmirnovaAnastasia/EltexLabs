#include "eth.h"

#define PORT = 12345

struct udp_packet{
    struct udphdr udp_header;
    char payload[1024];
};

int main() {
    int ret;
    int sockfd, sockfd2;
    struct sockaddr_in client_addr, server_addr;
    int server_len = sizeof(server_addr);
    int client_len = sizeof(client_addr);
    char cli_buffer[512] = " ", ser_buffer[512] = " ";

    memset(cli_buffer, 0, sizeof(cli_buffer));
    memset(ser_buffer, 0, sizeof(ser_buffer));
    
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    memset(&client_addr, 0, sizeof(client_addr));
    memset(&server_addr, 0, sizeof(server_addr));

    //Destination
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2345); 
    inet_pton(AF_INET, SERV_ADDR, &server_addr.sin_addr);

    struct udp_packet packet;
    struct udp_packet packet2;
    memset(&packet, 0, sizeof(packet));

    packet.udp_header.source = htons(2345); // Исходный порт
    packet.udp_header.dest = htons(8080);
    packet.udp_header.len = htons(sizeof(struct udphdr) + 5); 
    packet.udp_header.check = 0; 

    char *hi = "Hello!";
    packet.payload[0] = '\0';
    strcpy(packet.payload, hi);

    printf("Client starts work!\n"); 
    for(int i = 0; i<5; i++)
    {
        sleep(3);
  
        // Client send mes
        ret = sendto(sockfd, &packet, sizeof(struct udphdr) + strlen(hi), 0, (struct sockaddr*)&server_addr, server_len);
        if (ret < 0)
		{
			perror("sendto error");
			return 0;
		}

        printf("Client sends message: %s\n", packet.payload);


        sockfd2 = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
        if (sockfd2 == -1) {
            perror("socket error");
            exit(EXIT_FAILURE);
        }

        int optval = 1;
        ret = setsockopt(sockfd2, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(optval));
        if (ret < -1) {
            perror("setsockopt error");
            close(sockfd2);
            exit(EXIT_FAILURE);
        }
        
        
        ret = recvfrom(sockfd2, cli_buffer, sizeof(cli_buffer), 0, (struct sockaddr*)&client_addr, &client_len);
        if (ret == -1)
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);
		}

        struct iphdr *ip_header = (struct iphdr*) cli_buffer;
        unsigned int ip_header_len = ip_header->ihl * 4;

        if(ip_header->protocol != IPPROTO_UDP)
        {
            printf("am1-udp\n");
            continue;
        }

        struct udphdr *udp_header = (struct udphdr*)(cli_buffer + ip_header_len);

        if(udp_header->dest != htons(2345))
        {
            printf("am2-port\n");
            continue;
        }

        printf("Client recieves message: ");

        for (int i = sizeof(struct udphdr) + sizeof(struct iphdr); i < sizeof(cli_buffer); i++)
        {
            printf("%c", cli_buffer[i]);
        }
        printf("\n");

    }

    char *bye = "Bye";
    packet.payload[0] = '\0';
    strcpy(packet.payload, bye);

    sleep(3);
  
    ret = sendto(sockfd, &packet, sizeof(struct udphdr) + strlen(hi), 0, (struct sockaddr*)&server_addr, server_len);
    if (ret < 0)
    {
        perror("sendto error");
        return 0;
    }

    printf("Client sends message: %s\n", packet.payload);
    printf("Client stops work\n");

    
    close(sockfd);
    close(sockfd2);
    return 0;
}