#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

bool stop = false;
 
void hdl(int sig)
{   
    stop = true;
}
 
void* blocking_read(void* arg)
{
    if(stop)
    {
        printf("Stop process!\n");
        pthread_exit((void *)0); 
    }
        
    sigset_t set, orig; //Several sinals
    sigemptyset(&set); // Init set of signals
    sigaddset(&set, SIGINT); // Add signals signum
    sigemptyset(&orig); // Init orig signals
    pthread_sigmask(SIG_BLOCK, &set, &orig); // Change mask
    
    if(stop) // If stop change mask to origin
    {
        printf("Stop process!\n");
        pthread_sigmask(SIG_SETMASK, &orig, 0);
        pthread_exit((void *)0);
    }
        
    printf("Can't stop process!\n");

    sleep(15);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Init socket
    const int optval = 1;
    
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    // Change flags

    struct sockaddr_in addr;
    
    bzero(&addr, sizeof(addr)); // Allocate space
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)); // Add address                                                      
    
    struct pollfd clients[1];
    clients[0].fd = sockfd;
    clients[0].events = POLLIN | POLLHUP;
    clients[0].revents = 0;
    
    ppoll((struct pollfd*) &clients, 1, NULL, &orig);
    //Wait print by client?

    printf("\nNow you can stop!\n");
    
    if(stop) // If stop change mask to origin
    {
        printf("Stop process!\n");
        close(sockfd);
        pthread_sigmask(SIG_SETMASK, &orig, 0); 
    }
    
    close(sockfd);   
    pthread_exit((void *)0);  
}
 
int main()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act)); 
    act.sa_handler = hdl;
 
    sigemptyset(&act.sa_mask); // Init set of signals                                                             
    sigaddset(&act.sa_mask, SIGINT); // Add signals signum 
    sigaction(SIGINT, &act, 0);
    
    pthread_t th1;
    pthread_create(&th1, NULL, blocking_read, NULL); // Create new thread

    sleep(1);
 
    sleep(5);
    pthread_kill(th1, SIGINT); 
 
    pthread_join(th1, NULL);
}