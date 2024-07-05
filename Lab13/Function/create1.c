#include "../chat.h"
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


void create_windows1(WINDOW ** wnd1, WINDOW **wnd2,  WINDOW ** subwnd1, WINDOW **subwnd2){
	
	//Main window
	*wnd1 = newwin(20, 60, 0, 0);
	*wnd2 = newwin(20, 20, 0, 60);

	wbkgd(*wnd1, COLOR_PAIR(1));
	wbkgd(*wnd2, COLOR_PAIR(1));

	*subwnd1 = derwin(*wnd1, 1, 9, 1, 2);
	*subwnd2 = derwin(*wnd2, 1, 8, 1, 8);

	wprintw(*subwnd1, "Messages:");
	wprintw(*subwnd2, "Users:");

	wbkgd(*subwnd1, COLOR_PAIR(2)|A_BOLD);
	wbkgd(*subwnd2, COLOR_PAIR(2)|A_BOLD);

}