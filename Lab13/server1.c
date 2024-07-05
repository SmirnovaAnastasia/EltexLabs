#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define N 20
//queue's struct
struct mess_buf
{
  long mtype;
  char mtext[N];
};

int main()
{
	int qid; //id
	key_t msgkey; //key

	struct mess_buf buf; //buf
	struct mess_buf buf2 = {1, "Hello"};

	int length;
	int i;
	char newtext[6] = "Hello";

	length = sizeof(struct mess_buf) - sizeof(long);

	msgkey = ftok("/home/mqueue",'m'); //???
	qid = msgget(msgkey, IPC_CREAT | 0660);

	sleep (2);
    msgrcv(qid, &buf, length, 1, 0);
    printf("Server recieves message: %s\n", buf.mtext);

    sleep (2);
    buf.mtext[sizeof(newtext)] = '\0';
    msgsnd(qid, &buf2, length, 0);
    printf("Server sends message: %s\n", buf2.mtext);

	msgctl(qid, IPC_RMID, 0);
	return 0;
}