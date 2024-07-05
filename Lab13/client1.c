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

	struct mess_buf buf = {1, "Hi"}; //buf
	struct mess_buf buf2;

	int length;
	int i;
	int status;

	length = sizeof(struct mess_buf) - sizeof(long);

	msgkey = ftok("/home/mqueue",'m'); //???
	qid = msgget(msgkey, IPC_CREAT | 0660);

	msgsnd(qid, &buf, length, 0);
	printf("Client sends message: %s\n", buf.mtext);

	sleep (2);
	msgrcv(qid, &buf2, length, 1, 0);
	printf("Client recieves message: %s\n", buf2.mtext);

	msgctl(qid, IPC_RMID, 0);
	return 0;
}