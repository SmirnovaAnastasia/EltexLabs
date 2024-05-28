#include "../task2.h"
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


void create_windows(WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin){
	
	//=========================================
	//Main window
	*wnd11 = newwin(21, 20, 0, 0);
	*wnd21 = newwin(21, 20, 0, 40);

	*wnd12 = newwin(21, 12, 0, 17);
	*wnd22 = newwin(21, 12, 0, 57);

	*wnd13 = newwin(21, 12, 0, 28);
	*wnd23 = newwin(21, 12, 0, 68);

	//Down side
	*wnd1d = newwin(4, 40, 20, 0);
	*wnd2d = newwin(4, 40, 20, 40);

	wbkgd(*wnd11, COLOR_PAIR(1));
	wbkgd(*wnd21, COLOR_PAIR(1));
	wbkgd(*wnd12, COLOR_PAIR(1));
	wbkgd(*wnd22, COLOR_PAIR(1));
	wbkgd(*wnd13, COLOR_PAIR(1));
	wbkgd(*wnd23, COLOR_PAIR(1));

	wbkgd(*wnd1d, COLOR_PAIR(1));
	wbkgd(*wnd2d, COLOR_PAIR(1));

	*subwnd11 = derwin(*wnd11, 1, 4, 1, 8);
	*subwnd21 = derwin(*wnd21, 1, 4, 1, 8);
	*subwnd12 = derwin(*wnd12, 1, 5, 1, 3);
	*subwnd22 = derwin(*wnd22, 1, 5, 1, 3);
	*subwnd13 = derwin(*wnd13, 1, 8, 1, 2);
	*subwnd23 = derwin(*wnd23, 1, 8, 1, 2);

	*tabwin = derwin(*wnd11, 1, 19, 2, 1);


	wprintw(*subwnd11, "Name");
	wprintw(*subwnd21, "Name");
	wprintw(*subwnd12, "Size");
	wprintw(*subwnd22, "Size");
	wprintw(*subwnd13, "Mod time\n");
	wprintw(*subwnd23, "Mod time\n");

	wbkgd(*subwnd11, COLOR_PAIR(2)|A_BOLD);
	wbkgd(*subwnd12, COLOR_PAIR(2)|A_BOLD);
	wbkgd(*subwnd21, COLOR_PAIR(2)|A_BOLD);
	wbkgd(*subwnd22, COLOR_PAIR(2)|A_BOLD);
	wbkgd(*subwnd13, COLOR_PAIR(2)|A_BOLD);
	wbkgd(*subwnd23, COLOR_PAIR(2)|A_BOLD);

	wbkgd(*tabwin, COLOR_PAIR(3));
}