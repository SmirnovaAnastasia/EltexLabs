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
#include <time.h>


void refresh_windows(struct dirent **dir1, struct dirent **dir2, int n1, int n2, char *path_dir1, char *path_dir2, 
	char* mas1[], char* mas2[], int but_y, int side, WINDOW ** wnd11, WINDOW **wnd21, WINDOW **wnd12, WINDOW **wnd22, 
	WINDOW **wnd13, WINDOW **wnd23, WINDOW **wnd1d, WINDOW **wnd2d, WINDOW ** subwnd11, WINDOW **subwnd12, WINDOW **subwnd13, 
	WINDOW **subwnd21, WINDOW **subwnd22, WINDOW **subwnd23, WINDOW ** tabwin){

	char new_path_dir[count];
	struct stat st;

	int i = 0;
	//int count = n;


	for (int i = 0; i < n1; ++i)
	{
		mas1[i] = dir1[i+1]->d_name;
	}

	for (int i = 0; i < n2; ++i)
	{
		mas2[i] = dir2[i+1]->d_name;
	}

	//Left side
	for (int i = 0; i < n1-1; ++i)
	{
		wmove(*wnd11, 2+i, 2);
		wprintw(*wnd11, dir1[i+1]->d_name);
	}

	for (int i = 0; i < n2-1; ++i)
	{
		wmove(*wnd21, 2+i, 2);
		wprintw(*wnd21, dir2[i+1]->d_name);
	}

	move(0,0);
	//Middle side
	for (int i = 0; i < n1-1; ++i)
	{
		for (int j = 0; j < strlen(path_dir1); ++j)
		{
			new_path_dir[j] = path_dir1[j];
		}
		new_path_dir[strlen(path_dir1)] = '\0';

		if(strcmp(new_path_dir, "/\0") != 0){
			strncat(new_path_dir, "/", 2);
		}
		int len = strlen(dir1[i+1]->d_name);
		strncat(new_path_dir, dir1[i+1]->d_name, len);

		if(stat(new_path_dir, &st) == 0 && !(st.st_mode & S_IFDIR)){
			wmove(*wnd12, 2+i, 2);
			wprintw(*wnd12, "%ld byt", st.st_size);

			//dir1[i+1]->d_reclen
		}else{
			wmove(*wnd12, 2+i, 2);
			wprintw(*wnd12, "it's dir");
		}

	}

	for (int i = 0; i < n2-1; ++i)
	{
		for (int j = 0; j < strlen(path_dir2); ++j)
		{
			new_path_dir[j] = path_dir2[j];
		}
		new_path_dir[strlen(path_dir2)] = '\0';

		if(strcmp(new_path_dir, "/\0") != 0){
			strncat(new_path_dir, "/", 2);
		}
		int len = strlen(dir2[i+1]->d_name);
		strncat(new_path_dir, dir2[i+1]->d_name, len);

		if(stat(new_path_dir, &st) == 0 && !(st.st_mode & S_IFDIR)){
			wmove(*wnd22, 2+i, 2);
			wprintw(*wnd22, "%ld byt", st.st_size);

			//dir1[i+1]->d_reclen
		}else{
			wmove(*wnd22, 2+i, 2);
			wprintw(*wnd22, "it's dir");
		}

	}

	//Right side
	for (int i = 0; i < n1-1; ++i)
	{
		for (int j = 0; j < strlen(path_dir1); ++j)
		{
			new_path_dir[j] = path_dir1[j];
		}
		new_path_dir[strlen(path_dir1)] = '\0';

		if(strcmp(new_path_dir, "/\0") != 0){
			strncat(new_path_dir, "/", 2);
		}
		int len = strlen(dir1[i+1]->d_name);
		strncat(new_path_dir, dir1[i+1]->d_name, len);

		if(stat(new_path_dir, &st) == 0){
			char buff[100];
			strftime(buff, sizeof(buff), "%D", gmtime(&st.st_mtime));
			wmove(*wnd13, 2+i, 2);
			wprintw(*wnd13, "%s", buff);

			//dir1[i+1]->d_reclen
		}
	}

	for (int i = 0; i < n2-1; ++i)
	{
		for (int j = 0; j < strlen(path_dir2); ++j)
		{
			new_path_dir[j] = path_dir2[j];
		}
		new_path_dir[strlen(path_dir2)] = '\0';

		if(strcmp(new_path_dir, "/\0") != 0){
			strncat(new_path_dir, "/", 2);
		}
		int len = strlen(dir2[i+1]->d_name);
		strncat(new_path_dir, dir2[i+1]->d_name, len);

		if(stat(new_path_dir, &st) == 0){
			char buff[100];
			strftime(buff, sizeof(buff), "%D", gmtime(&st.st_mtime));
			wmove(*wnd23, 2+i, 2);
			wprintw(*wnd23, "%s", buff);

			//dir1[i+1]->d_reclen
		}
	}

	switch(side){
	case 1:
		wbkgd(*tabwin, COLOR_PAIR(2));
		delwin(*tabwin);
		*tabwin = derwin(*wnd11, 1, 19, but_y, 1);
		wbkgd(*tabwin, COLOR_PAIR(3));
		wrefresh(*wnd11);
		break;
	case 2:
		wbkgd(*tabwin, COLOR_PAIR(2));
		delwin(*tabwin);
		*tabwin = derwin(*wnd21, 1, 19, but_y, 1);
		wbkgd(*tabwin, COLOR_PAIR(3));
		wrefresh(*wnd11);
		break;
	}

	wmove(*wnd1d, 1, 2);
	wprintw(*wnd1d, path_dir1);
	wmove(*wnd2d, 1, 2);
	wprintw(*wnd2d, path_dir2);
	
	box(*wnd11, '|', '-');
	box(*wnd21, '|', '-');

	box(*wnd12, '|', '-');
	box(*wnd22, '|', '-');

	box(*wnd13, '|', '-');
	box(*wnd23, '|', '-');

	box(*wnd1d, '|', '-');
	box(*wnd2d, '|', '-');
	wrefresh(*tabwin);

	wrefresh(*wnd11);
	wrefresh(*wnd21);

	wrefresh(*wnd12);
	wrefresh(*wnd22);

	wrefresh(*wnd13);
	wrefresh(*wnd23);

	wrefresh(*wnd1d);
	wrefresh(*wnd2d);
	

	wrefresh(*tabwin);
}