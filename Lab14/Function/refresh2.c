#include "../chat.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <form.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int iasdasdasd = 0;

struct arg_struct
{
	WINDOW **wnd3;
	char *text;
	int len;
};


void get_message(WINDOW **wnd3, char *text, int len)
{
	int x,y;
	int idx = 0;
	char ch;
	int max_i = idx;
	wmove(*wnd3, 1, 2);
	while(((ch = wgetch(*wnd3)) != 10) && (idx < len-1))
	{
		if(ch == 8 || ch == 127 || ch == '\b')
		{

			for (int i = 0; i < 3; ++i)
			{
				getyx(*wnd3,y,x);
				mvwaddch(*wnd3, y, x-1, ' ');
				wrefresh(*wnd3);
				wmove(*wnd3, y, x-1);

			}
			text[idx] = '\0';
			idx -= 1;
	
		}else{
			text[idx] = ch;
			idx++;
		}
	}
	text[idx] = '\0';
	
	wechochar(*wnd3, '\n'); 
	wmove(*wnd3, 1, 2);
}

void refresh_windows2(char text[20], WINDOW **wnd3, WINDOW **subwnd3){
	
	int *s;
	box(*wnd3, '|', '-');

	pthread_mutex_lock(&m1);
	get_message(wnd3, text, 20);
	pthread_mutex_unlock(&m1);

	wmove(*wnd3, 10,0);

	wrefresh(*wnd3);
}