#ifndef __FUN_H__
#define __FUN_H__

typedef struct
{
	int arr[5];
	int back;
	int front;
	int count;
} Queue;

typedef struct
{
	int in;
	Queue *que;
	int fd;
	int other_sock;
	struct sockaddr_in other_str;
	int port;
} Pthstr;

//Queue Function
void initializeQueue(Queue *que);
void addQueue(Queue *que, int value);
int peek(Queue *que);
void delQueue(Queue *que);
int isEmpty(Queue *que);
int isFull(Queue *que);

//Server Function
int made_socket(struct sockaddr_in *serv, int port);
void *other_ser(void *info);

#endif