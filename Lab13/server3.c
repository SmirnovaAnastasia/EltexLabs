#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "chat.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>

#define N 20
//queue's struct

struct arg_struct_ser
{
	key_t msgkey;
	int qid;
	int user_number;
};

struct mess_buf
{
	long mtype; 
	int count;
	char sender[N];
	char mtext[N];
};

int main(int argc, char ** argv){
	int qid; //id
	pid_t pid;
	key_t msgkey;
	int length;
	int status;

	length = sizeof(struct mess_buf) - sizeof(long);
	
	char *message_buf[20];
	char *user_buf[5];
	int message_number = 0;
	int user_number = 0;

	int have_in = 0;
	int tr;
	int *s;

	msgkey = ftok("./",'m');
	if(msgkey == (key_t)-1){
		printf("Here!\n");
		perror("Ftok");
		return -1;
	} //For recieve

	qid = msgget(msgkey, IPC_CREAT | 0660);

	if(qid == -1){
		perror("Msgget");
		return -1;
	}

	if((msgctl(qid, IPC_RMID, 0)) < 0){
		perror("Msgctl");
		return -1;
	}

	msgkey = ftok("./",'m');
	if(msgkey == (key_t)-1){
		perror("Ftok");
		return -1;
	} //For recieve

	qid = msgget(msgkey, IPC_CREAT | 0660);

	if(qid == -1){
		perror("Msgget");
		return -1;
	}
	struct mess_buf buf;

	struct arg_struct_ser args;
	args.msgkey = msgkey;
	args.qid = qid;
	args.user_number = user_number;

	int count = 0;
	
	while(1){
		have_in = 0;

		if((msgrcv(qid, &buf, length, 6, 0)) < 0){
			perror("Msgrcv");
			return -1;
		}

		//Try to find user
		for (int i = 0; i < user_number; ++i)
		{
			tr = strcmp(user_buf[i], buf.sender);
			if(tr == 0) have_in++;
			//printf("have_in: %d\n", have_in);
		}

		//Old user
		if(have_in > 0){
			int eq = strcmp(buf.mtext,"exit");	
			//New message from old user
			if(eq != 0){
				message_number++;
				message_buf[message_number-1] = malloc(sizeof(char) * 20);
				message_buf[message_number-1][0] = '\0';

				//Do all message
				strcat(message_buf[message_number-1],buf.sender);
				strcat(message_buf[message_number-1],": ");
				strcat(message_buf[message_number-1],buf.mtext);

				buf.mtext[0] = '\0';
				strcat(buf.mtext,message_buf[message_number-1]);

				buf.sender[0] = '\0'; 
				strcat(buf.sender,"server");	

				//Send new message to all users
				for (int i = 2; i <= user_number + 1; ++i)
				{
					buf.mtype = i;
					if((msgsnd(qid, &buf, length, 0)) == -1){
						perror("Msgsnd");
						return -1;
					}
				}

			//User wants to exit
			}else{
				char new_mes[40] = "User ";
				strcat(new_mes, buf.sender);

				for (int i = 0; i < user_number; ++i)
				{
					eq = strcmp(user_buf[i],buf.sender);
					if(eq == 0){
						buf.count = i;
						if(i < (user_number - 1)){
							for (int j = i; j < user_number-1; ++j)
							{
								user_buf[j][0] = '\0';
								strcat(user_buf[j],user_buf[j+1]);
							}
						}else{
							user_buf[i][0] = '\0';
						}
					}
				}

				strcat(new_mes," exit");

				message_number++;
				message_buf[message_number-1] = malloc(sizeof(char) * 20);
				message_buf[message_number-1][0] = '\0';
				strcat(message_buf[message_number-1],new_mes);

				buf.sender[0] = '\0';
				strcat(buf.sender,"exit");

				for (int i = 2; i <= user_number + 1; ++i)
				{	
					if(i != buf.count + 2){
						buf.mtype = i;
						buf.mtext[0] = '\0';
						strcat(buf.mtext,new_mes);

						if((msgsnd(qid, &buf, length, 0)) == -1){
							perror("Msgsnd");
							return -1;
						}
						sleep(1);
					}

				}
				
			}
		//New user
		}else{
			// printf("Am1\n");
			user_number++;
			user_buf[user_number-1] = malloc(sizeof(char) * 20);
			user_buf[user_number-1][0] = '\0';
			strcat(user_buf[user_number-1],buf.sender);

			buf.mtext[0] = '\0';
			char new_mes[40] = "Add new user - ";
			strcat(new_mes,buf.sender);

			message_number++;
			message_buf[message_number-1] = malloc(sizeof(char) * 20);
			message_buf[message_number-1][0] = '\0';
			strcat(message_buf[message_number-1],new_mes);

			//Send all info to new user
			buf.mtype = 1;

			buf.mtext[0] = '\0';
			//Send count of users

			buf.count = user_number;
			buf.mtext[0] = '\0';
			strcat(buf.mtext,"count");

			if((msgsnd(qid, &buf, length, 0)) == -1){
				perror("Msgsnd");
				return -1;
			}

			sleep(1);

			for (int i = 0; i < user_number; ++i)
			{
				buf.mtext[0] = '\0';
				strcat(buf.mtext,user_buf[i]);

				if((msgsnd(qid, &buf, length, 0)) == -1){
					perror("Msgsnd");
					return -1;
				}
	
				sleep(1);

			}

			sleep(1);

			//Send count of messages
			buf.mtext[0] = '\0';
			
			buf.count = message_number;

			if((msgsnd(qid, &buf, length, 0)) == -1){
				perror("Msgsnd");
				return -1;
			}


			for (int i = 0; i < message_number; ++i)
			{
				buf.mtext[0] = '\0';
				strcat(buf.mtext,message_buf[i]);
				if((msgsnd(qid, &buf, length, 0)) == -1){
					perror("Msgsnd");
					return -1;
				}

				sleep(1);
			}

			printf("\n");

			buf.count = -1;
			buf.sender[0] = '\0';
			strcat(buf.sender,user_buf[user_number-1]);
			buf.mtext[0] = '\0';
			strcat(buf.mtext,new_mes);

			//Send new user's name to all users
			for (int i = 2; i <= user_number; ++i)
			{
				buf.mtype = i;
				if((msgsnd(qid, &buf, length, 0)) == -1){
					perror("Msgsnd");
					return -1;
				}

				sleep(1);
			}
			buf.count = 0;


		}
		printf("==Loop finish===\n");
	}	

	return 0;

}
