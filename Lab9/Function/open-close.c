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

int close_dir(struct dirent*** dir, int y, char* obj_for_path, int n){
	
	//move(0,0);
	//printw("\nstart n = %d\n", n);
	int len = strlen(obj_for_path);
	char path_dir_work[len];
	//move(0,0);
	//printw("1\n");

	for (int i = 0; i <= len; ++i)
	{
		path_dir_work[i] = obj_for_path[i];
	}

	//printw("Obj: %s | Path: %s\n", obj_for_path, path_dir_work);
	char *sl = strrchr(path_dir_work, '/');
	int slint = sl - path_dir_work;
	if(slint == 0){
		slint++;
	}
	path_dir_work[slint] = '\0';
	n = scandir(path_dir_work, dir, 0, alphasort);
	//but_y = 2;

	for (int i = 0; i <= len; ++i)
	{
		obj_for_path[i] = path_dir_work[i];
	}
	//printw("end n = %d\n", n);

	return n;
}

int open_dir(struct dirent ***dir, char** mas, int y, char* path_dir_work, int n){
	int len = strlen(path_dir_work);
	char new_dir_work[count];


	for (int i = 0; i <= len; ++i)
	{
		new_dir_work[i] = path_dir_work[i];
	}

	new_dir_work[len] = '\0';

	//printw("Mas: %s", mas[1]);

	if(strcmp(new_dir_work, "/\0") != 0){
		strncat(new_dir_work, "/", 2);
	}
	
	strncat(new_dir_work, mas[y - 2], strlen(mas[y - 2]));
	// printw("Mas: %s\n", mas[y-2]);
	 //printw("Obj: %s | New: %s\n", path_dir_work, new_dir_work);
	struct stat s;

	//printw("%d | %d\n",stat(new_dir_work, &s), (s.st_mode & S_IFDIR));

	if(stat(new_dir_work, &s) == 0 && (s.st_mode & S_IFDIR)){
		move(0,0);
		// printw("Obj: %s | Path: %s\n", *obj_for_path, new_dir_work);
		n = scandir(new_dir_work, dir, 0, alphasort);
		len = strlen(new_dir_work);
		for (int i = 0; i <= len; ++i)
		{
			path_dir_work[i] = new_dir_work[i];
		}
		//printw("2\n");
	}
	
	return n;
}