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

void init(WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin) {
	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(FALSE);
	start_color();
	refresh();

	keypad(stdscr, 1);
	mousemask(BUTTON1_CLICKED, NULL);
	move(2,2);

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_CYAN);
	create_windows(wnd11, wnd21, wnd12, wnd22, wnd13, wnd23, wnd1d, wnd2d,
	subwnd11, subwnd12, subwnd13, subwnd21, subwnd22, subwnd23, tabwin);

}
