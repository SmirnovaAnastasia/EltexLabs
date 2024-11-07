#include <stdio.h>
#include<sys/socket.h>
#include <string.h>

#include<stdlib.h> 
#include<stdint.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <signal.h>
#include <time.h>
#include <sys/un.h>

#include "../fun.h"

void initializeQueue(Queue *que)
{
    que->front = -1;
    que->back = 0;
    que->count = 0;
}

void addQueue(Queue *que, int value)
{
    if(que->count == 5)
    {
        printf("Queue is full\n");
        exit(1);
    }
    que->arr[que->back] = value;
    que->back++;
    que->count++;
}

int peek(Queue *que)
{
    if(isEmpty(que))
    {
        printf("Queue is empty\n");
        exit(1);
    }
    return que->arr[que->front + 1];
}

void delQueue(Queue *que)
{
    if(isEmpty(que) == 1)
    {
        printf("Queue is empty\n");
        return;
    }
    que->front++;
    que->count--;
}

int isEmpty(Queue *que)
{
    int ans;
    if(que->count == 0)
    {
        ans = 1;
    }else
    {
        ans = 0;
    }
    return ans;
}

int isFull(Queue *que)
{
    int ans;
    if(que->count == 5)
    {
        ans = 1;
    }else
    {
        ans = 0;
    }
    return ans;
}