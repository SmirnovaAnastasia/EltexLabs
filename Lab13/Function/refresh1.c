#include "../chat.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
// #include <curses.h>
#include <ncurses.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

void refresh_windows1(int message_number, int user_number, char *message_buf[20], char *user_buf[10],
	WINDOW ** wnd1, WINDOW **wnd2, WINDOW ** subwnd1, WINDOW **subwnd2){

	for (int i = 0; i < message_number; ++i)
	{
		wmove(*wnd1, 3+i, 2);
		wprintw(*wnd1, "%s", message_buf[i]);
	}

	for (int i = 0; i < user_number; ++i)
	{
		wmove(*wnd2, 3+i, 2);
		wprintw(*wnd2, "      ");
		wmove(*wnd2, 3+i, 2);
		wprintw(*wnd2, "%s", user_buf[i]);
	}

	wmove(*wnd2, 3+user_number, 2);
	wprintw(*wnd2, "            ");

	box(*wnd1, '|', '-');
	box(*wnd2, '|', '-');

	wrefresh(*wnd1);
	wrefresh(*wnd2);
}