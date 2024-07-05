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


void delete_windows(WINDOW ** wnd1, WINDOW **wnd2, WINDOW **wnd3,
	WINDOW ** subwnd1, WINDOW **subwnd2, WINDOW **subwnd3){
	
	delwin(*subwnd1);
	delwin(*subwnd2);
	delwin(*subwnd3);

	delwin(*wnd1);
	delwin(*wnd2);
	delwin(*wnd3);
}
