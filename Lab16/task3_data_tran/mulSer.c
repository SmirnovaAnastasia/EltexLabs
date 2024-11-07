#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

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

    memset(&endpoint, 0, sizeof(endpoint));
    endpoint.sin_family = AF_INET;
    endpoint.sin_addr.s_addr = inet_addr("224.0.0.1");
    endpoint.sin_port = htons(7777);

    while(1)
    {
        ret = sendto(sockfd, "hello", 5,0,(struct sockaddr*)&endpoint,sizeof(endpoint));
        if(ret < 0)
        {
            perror("sendto failed");
            return -1;
        }
        else
        {
            printf("Server send \"hello\"\n");
        }
        sleep(2);

    }

    close(sockfd);
    return 0;
}