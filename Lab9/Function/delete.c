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


void delete_windows(WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin){
	
	delwin(*subwnd11);
	delwin(*subwnd21);

	delwin(*subwnd12);
	delwin(*subwnd22);

	delwin(*subwnd13);
	delwin(*subwnd23);

	delwin(*wnd11);
	delwin(*wnd21);

	delwin(*wnd12);
	delwin(*wnd22);

	delwin(*wnd13);
	delwin(*wnd23);

	delwin(*wnd1d);
	delwin(*wnd2d);

	delwin(*tabwin);
}
