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

void init2(WINDOW **wnd3, WINDOW **subwnd3) {
	initscr();
	signal(SIGWINCH, sig_winch);
	keypad(*wnd3, TRUE);
	curs_set(FALSE);
	start_color();
	refresh();

	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_CYAN);
	create_windows2(wnd3,subwnd3);

}