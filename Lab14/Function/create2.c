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


void create_windows2(WINDOW **wnd3, WINDOW **subwnd3){
	
	*wnd3 = newwin(4, 80, 20, 0);

	wprintw(*subwnd3, "Print your message...");

	wbkgd(*wnd3, COLOR_PAIR(1));


}