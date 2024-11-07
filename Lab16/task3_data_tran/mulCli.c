#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in endpoint;
    
    int ret;
    int sockfd, i, slen;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        perror("socket failed");
        return -1;
    }

    endpoint.sin_family = AF_INET; 
    endpoint.sin_addr.s_addr = htonl(INADDR_ANY);
    endpoint.sin_port = htons(7777);

    ret = bind(sockfd,(struct sockaddr*)&endpoint,sizeof(endpoint));
    if(ret < 0)
    {
        perror("bind failed");
        return -1;
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.1");//Broadcast address
    mreq.imr_interface.s_addr = htonl(INADDR_ANY); //Our addr?

    ret = setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
    if(ret < 0)
    {
        perror("setsockopt failed");
        return -1;
    }

    slen = sizeof(endpoint);
    char buf[256];

    while(1)
    {
        memset(buf, 0, 256);

        ret = recvfrom(sockfd, buf, 256, 0, (struct sockaddr*)&endpoint, &slen); 
        if(ret < 0)
        {
            perror("recvfrom failed");
            return -1;
        }
        else
        {
            printf("Client recieve buf = %s\n", buf);
        }
        sleep(2);
    }

    close(sockfd);
    return 0;
} 