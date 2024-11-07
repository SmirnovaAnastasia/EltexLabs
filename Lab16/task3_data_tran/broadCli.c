#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
    struct sockaddr_in endpoint;
    
    int ret;
    int sockfd, i, slen;

    bzero(&endpoint,sizeof(struct sockaddr_in));
    endpoint.sin_family = AF_INET;
    endpoint.sin_addr.s_addr = inet_addr("255.255.255.255");
    endpoint.sin_port = htons(7777);

    slen = sizeof(endpoint);

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        perror("socket failed");
        return -1;
    }

    int flag = 1;

    ret = setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));
    if(ret == -1)
    {
        perror("setsockopt failed");
        return -1;
    }

    ret = bind(sockfd,(struct sockaddr*)&(endpoint),slen);
    if(ret == -1)
    {
        perror("bind failed");
        return -1;
    }

    char buf[256];

    while(1)
    {
        ret = recvfrom(sockfd, buf, 256,0,(struct sockaddr*)&endpoint,&slen);
        if(ret <= 0)
        {
            perror("recvfrom failed");
            return -1;
        }
        else
        {
            printf("Client recieve buf = %s\n", buf);
        }
        sleep(1);
    }

    close(sockfd);
    return 0;
}