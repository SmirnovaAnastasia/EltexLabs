#ifndef __TASK2_H__
#define __TASK2_H__

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
//#include </usr/include/ncurses.h>

#define M_KEY_ENTER 10
#define M_KEY_TAB 9
#define count 100

void sig_winch(int signo);
void init(WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin);
void create_windows(WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin);
void delete_windows(WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin);
void refresh_windows(struct dirent **dir1, struct dirent **dir2, int n1, int n2, char *path_dir1, char *path_dir2, 
	char* mas1[], char* mas2[], int but_y, int side, WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, 
	WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, WINDOW **subwnd21, WINDOW **subwnd22, 
	WINDOW **subwnd23, WINDOW ** tabwin);
int open_dir(struct dirent ***dir, char** mas, int y, char* path_dir_work, int n);
int close_dir(struct dirent***dir, int y, char* obj_for_path, int n);

#endif /* End of function.h */