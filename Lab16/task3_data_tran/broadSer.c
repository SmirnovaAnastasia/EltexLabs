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

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        perror("socket failed");
        return -1;
    }

    int flag = 1;
    
    ret = setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));
    //Option for broadcast
    if(ret == -1)
    {
        perror("setsockopt failed");
        return -1;
    }
    
    bzero(&endpoint,sizeof(struct sockaddr_in));
    endpoint.sin_family = AF_INET;
    endpoint.sin_addr.s_addr = inet_addr("255.255.255.255");
    endpoint.sin_port = htons(7777);
    
    slen = sizeof(endpoint);
    
    while(1)
    {
        sleep(1);
        int ret = sendto(sockfd, "hello", 5,0,(struct sockaddr*)&endpoint, slen);//Publish a message to the broadcast address
        if(ret < 0)
        {
            perror("sendto failed");
            return -1;
        }
        else
        {
            printf("Server send \"hello\"\n");
        }

    }

    close(sockfd);
    return 0;
}