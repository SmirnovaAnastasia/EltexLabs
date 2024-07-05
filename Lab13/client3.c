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

#define N 20
//queue's struct

struct mess_buf
{
	long mtype; 
	int count;
	char sender[N];
	char mtext[N];
};

struct arg_struct_cl
{
	WINDOW *wnd1;
	WINDOW *wnd2;
	WINDOW *wnd3;
	WINDOW *subwnd1;
	WINDOW *subwnd2;
	WINDOW *subwnd3;
	char *my_name;
	char qid;
	key_t msgkey;
};

struct arg_struct_cl args;

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
	resizeterm(size.ws_row, size.ws_col);
	nodelay(stdscr, 1);
	while (wgetch(stdscr) != ERR);
	nodelay(stdscr, 0);
}

void *send_mes(void* args)
{
	char *message_buf[40];
	char *user_buf[10];

	struct arg_struct_cl arg = *(struct arg_struct_cl*) args;
	WINDOW *wnd1 = arg.wnd1;
	WINDOW *wnd2 = arg.wnd2;
	WINDOW *wnd3 = arg.wnd3;
	WINDOW *subwnd1 = arg.subwnd1;
	WINDOW *subwnd2 = arg.subwnd2;
	WINDOW *subwnd3 = arg.subwnd3;
	char *my_name = arg.my_name; 

	pid_t qid = arg.qid;
	key_t msgkey = arg.msgkey;

	struct mess_buf buf;
	int length = sizeof(struct mess_buf) - sizeof(long);
	int count = 0;
	//sleep(4);
	int eq = -1;

	while(1){
		char text[40]; // For messege from refresh
		text[0] = '\0';
		count++;
		if(count == 1){
			init2(&wnd3, &subwnd3);
		}
		int eq = -1;
		refresh();
		refresh_windows2(text, &wnd3, &subwnd3);

		eq = strcmp(text,"");
		if(eq != 0){
			sleep(3);
			buf.mtype = 6;
			buf.sender[0] = '\0';
			int br = 0;
			strcat(buf.sender, my_name);
			eq = -1;
			//Equal "exit"
			eq = strcmp(text,"exit");	

			if(eq != 0){ //Not qual
				buf.mtext[0] = '\0';
				strcat(buf.mtext, text);
				buf.sender[0] = '\0';
				strcat(buf.sender, my_name);

				if((msgsnd(qid, &buf, length, 0)) == -1){
					perror("Msgsnd");
					exit(-1);
				}
			}else{ //Equal
				buf.mtext[0] = '\0';
				strcat(buf.mtext, text);
				buf.sender[0] = '\0';
				strcat(buf.sender, my_name);
				if((msgsnd(qid, &buf, length, 0)) == -1){
					perror("Msgsnd");
					exit(-1);
				}
				br++;
			}
			if(br > 0) exit(0);
		}
		
	}

}

void *client_main(void* args)
{
	struct arg_struct_cl arg = *(struct arg_struct_cl*) args;
	WINDOW *wnd1 = arg.wnd1;
	WINDOW *wnd2 = arg.wnd2;
	WINDOW *wnd3 = arg.wnd3;
	WINDOW *subwnd1 = arg.subwnd1;
	WINDOW *subwnd2 = arg.subwnd2;
	WINDOW *subwnd3 = arg.subwnd3;
	char *my_name = arg.my_name; 

	int qid = arg.qid; //id
	key_t msgkey = arg.msgkey;
	int length;

	struct mess_buf buf;
	length = sizeof(struct mess_buf) - sizeof(long);
	
	char *message_buf[40];
	char *user_buf[10];
	int message_number = 0;
	int user_number = 0;

	int have_in = 0;

	int my_number = 0;

	buf.mtype = 1;
	buf.sender[0] = '\0';
	strcat(buf.sender,my_name);

	//Recieve

	while(1){

	//If new
		if(user_number == 0){
			//Send name to server
			buf.mtype = 6;
			buf.mtext[0] = '\0';
			strcat(buf.mtext,my_name);
			if((msgsnd(qid, &buf, length, 0)) == -1){
				perror("Msgsnd");
				exit(-1);
			}

			sleep(2);

			//Recieve number of users
			if((msgrcv(qid, &buf, length, 1, 0)) < 0){
				perror("Msgrcv");
				exit(-1);
			}
			user_number = buf.count;

			//Recieve all users
			for (int i = 0; i < user_number; ++i)
			{
				if((msgrcv(qid, &buf, length, 1, 0)) < 0){
					perror("Msgrcv");
					exit(-1);
				}
				user_buf[i] = malloc(sizeof(char) * 10);
				user_buf[i][0] = '\0';
				strcat(user_buf[i],buf.mtext);
			}

			my_number = user_number + 1;

			//Recieve number of messages
			if((msgrcv(qid, &buf, length, 1, 0)) < 0){
				perror("Msgrcv");
				exit(-1);
			}
			message_number = buf.count;

			//Recieve all messages
			for (int i = 0; i < message_number; ++i)
			{
				if((msgrcv(qid, &buf, length, 1, 0)) < 0){
					perror("Msgrcv");
					exit(-1);
				}
				message_buf[i] = malloc(sizeof(char) * 40);
				message_buf[i][0] = '\0';
				strcat(message_buf[i],buf.mtext);
			}

			init1(&wnd1, &wnd2, &subwnd1, &subwnd2);
			refresh();
			refresh_windows1(message_number, user_number, message_buf, 
				user_buf, &wnd1, &wnd2, &subwnd1, &subwnd2);

		//If old
		}else{
			
			if((msgrcv(qid, &buf, length, my_number, 0)) < 0){
				perror("Msgrcv");
				exit(-1);
			}

			int eq = strcmp(buf.sender,"exit");	
			//Just mess
			if(eq != 0){

				if(buf.count == -1){
					message_buf[message_number] = malloc(sizeof(char) * 40);
					message_buf[message_number][0] = '\0';
					strcat(message_buf[message_number],buf.mtext);
					
					message_number++;

					user_buf[user_number] = malloc(sizeof(char) * 40);
					user_buf[user_number][0] = '\0';
					strcat(user_buf[user_number],buf.sender);
					user_number++;

				}else{
					message_buf[message_number] = malloc(sizeof(char) * 40);
					message_buf[message_number][0] = '\0';
					strcat(message_buf[message_number],buf.mtext);
					message_number++;

				}
			//Somebody wants to exit
			}else{
				message_buf[message_number] = malloc(sizeof(char) * 40);
				message_buf[message_number][0] = '\0';
				strcat(message_buf[message_number],buf.mtext);
				message_number++;

				user_buf[buf.count][0] = '\0';
				for (int i = buf.count; i < user_number; ++i)
				{
					if(i < user_number-1){
						user_buf[i][0] = '\0';
						strcat(user_buf[i],user_buf[i+1]);
					}
				}
				user_number--;

				if(my_number > user_number) my_number --;
			}

			refresh();
			refresh_windows1(message_number, user_number, message_buf, 
				user_buf, &wnd1, &wnd2, &subwnd1, &subwnd2);
		}

	}
}

int main(int argc, char ** argv){

	WINDOW * wnd1, *wnd2, *wnd3;
	WINDOW * subwnd1, *subwnd2, *subwnd3;

	int qid; //id
	key_t msgkey;
	int length;

	length = sizeof(struct mess_buf) - sizeof(long);
	
	msgkey = ftok("./",'m');
	if(msgkey == (key_t)-1){
		perror("Ftok");
		return -1;
	} //For recieve

	qid = msgget(msgkey, IPC_CREAT | 0660);

	char my_name[20];
	int *s;

	printf("Print your name: ");
	if(fgets(my_name, 20, stdin) == NULL){
			perror("Critical error!");
	}
	//printf("\n");

	struct mess_buf buf;

	args.wnd1 = wnd1;
	args.wnd2 = wnd2;
	args.wnd3 = wnd3;
	args.subwnd1 = subwnd1;
	args.subwnd2 = subwnd2;
	args.subwnd3 = subwnd3;
	args.my_name = my_name;
	args.qid = qid;
	args.msgkey = msgkey;

	pthread_t thread, thread2;

	pthread_create(&thread, NULL, client_main, (void*)&args);
	pthread_create(&thread2, NULL, send_mes, (void*)&args);

	pthread_join(thread, (void**)&s);
	pthread_join(thread2, (void**)&s);
	return 0;

}
