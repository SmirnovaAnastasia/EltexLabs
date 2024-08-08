#ifndef __CHAT2_H__
#define __CHAT2_H__

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>


void create_windows1(WINDOW ** wnd1, WINDOW **wnd2,  WINDOW ** subwnd1, WINDOW **subwnd2);
void create_windows2(WINDOW **wnd3, WINDOW **subwnd3);
void delete_windows(WINDOW ** wnd1, WINDOW **wnd2, WINDOW **wnd3,
	WINDOW ** subwnd1, WINDOW **subwnd2, WINDOW **subwnd3);
void init1(WINDOW ** wnd1, WINDOW **wnd2, WINDOW ** subwnd1, WINDOW **subwnd2);
void init2(WINDOW **wnd3, WINDOW **subwnd3);
void refresh_windows1(int message_number, int user_number, char *message_buf[20], char *user_buf[20],
	WINDOW ** wnd1, WINDOW **wnd2, WINDOW ** subwnd1, WINDOW **subwnd2);
void refresh_windows2(char text[20], WINDOW **wnd3, WINDOW **subwnd3);
void get_message(WINDOW **wnd3, char *text, int len);
void sig_winch(int signo);
void *send_mes(void* args);
void *client_main(void* args);
void *server_exit(void* args);

void *recieve_part(void* args);
void *send_part(void* args);
	
#endif /* End of function.h */