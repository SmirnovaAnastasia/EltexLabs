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
#include "task2.h"

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
	resizeterm(size.ws_row, size.ws_col);
	nodelay(stdscr, 1);
	while (wgetch(stdscr) != ERR);
	nodelay(stdscr, 0);
}

int main(int argc, char ** argv){

	WINDOW * wnd11, *wnd21, *wnd12, *wnd22, *wnd13, *wnd23, *wnd1d, *wnd2d;
	WINDOW * subwnd11, *subwnd12, *subwnd13, *subwnd21, *subwnd22, *subwnd23;
	WINDOW * tabwin;

	struct dirent **dir1;
	struct dirent **dir2;
	char* mas1[count], *mas2[count];
	int n1, n2, i;
	char path_dir_work1[count] = "/home/jkalisto/Desktop/EltexLabs";
	char path_dir_work2[count] = "/home/jkalisto/Desktop/EltexLabs";

	int but_y = 2, side = 1;

	n1 = scandir("/home/jkalisto/Desktop/EltexLabs", &dir1, 0, alphasort);
	n2 = scandir("/home/jkalisto/Desktop/EltexLabs", &dir2, 0, alphasort);
	move(0,0);
	printf("AM1 ");
	init(&wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
	printf("AM2 ");
	refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
	printf("AM2 ");
	refresh();
	int key;
	MEVENT event;
	while (key = getch()) {
		delete_windows(&wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
		create_windows(&wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
		if (key == KEY_MOUSE) {
			
			
			getmouse(&event);
			move(0, 0);
			printw("Mouse button pressed at %i, %i\n", event.x, event.y);


			if(event.y == 2){
				if(event.x <= 40){
					n1 = close_dir(&dir1, event.y, path_dir_work1, n1);
					//printw("Path: %s\n", path_dir_work1);
				}else{
					n2 = close_dir(&dir2, event.y, path_dir_work2, n2);
				}
				but_y = 2;
			}else if(event.y > 2){
				if(event.x <= 40 && event.y <= n1){
					n1 = open_dir(&dir1, mas1, event.y, path_dir_work1, n1);
				}else if(event.x > 40 && event.y <= n2){

					// move(0,0);
					// printw("Obj: %s | Path: %s\n", *obj_for_path, path_dir_work1);

					n2 = open_dir(&dir2, mas2, event.y, path_dir_work2, n2);
				}
				but_y = 2;
			}

		refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);

		}
		else{
			//printw("aboba");
			switch(key)
			{
				case KEY_UP:
					move(0, 0);
					printw("Pushed UP!");
					if(but_y > 2){
						but_y--;
					}
					refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
					break;
				case KEY_DOWN:
					move(0, 0);
					printw("Pushed DOWN!");
					switch(side){
						case 1:
							if(but_y != n1){
								but_y++;
							}
							break;
						case 2:
							if(but_y != n2){
								but_y++;
							}
							break;
					}
					refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
					break;
				case M_KEY_TAB:
					move(0, 0);
					printw("Pushed TABE!");
					switch(side){
						case 1:
							side = 2;
							but_y = 2;
							break;
						case 2:
							side = 1;
							but_y = 2;
							break;
					}
					refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
					break;
				case M_KEY_ENTER:
					move(0, 0);
					printw("Pushed ENTER!");
					if(but_y == 2){
						if(side == 1){

							n1 = close_dir(&dir1, but_y, path_dir_work1, n1);
						}else{

							n2 = close_dir(&dir2, but_y, path_dir_work2, n2);
						}
						but_y = 2;
					}else if(but_y > 2){
						if(side == 1){
							n1 = open_dir(&dir1, mas1, but_y, path_dir_work1, n1);
						}else{
							move(0,0);
							//printw("Obj: %s | Path: %s\n", *obj_for_path, path_dir_work1);

							n2 = open_dir(&dir2, mas2, but_y, path_dir_work2, n2);
						}
						but_y = 2;
					}
					// printw("REFRESHG!!!!!WAAAAGH!");
					refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
					break;
				default:
					move(0, 0);
					printw("Pushed another!");
					printw("%d", key);
					break;
			}
		}
		

		refresh_windows(dir1, dir2, n1, n2, path_dir_work1, path_dir_work2, mas1, mas2, but_y, side, &wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);


		refresh();
		move(event.y, event.x);
	} 

	delete_windows(&wnd11, &wnd21, &wnd12, &wnd22, &wnd13, &wnd23, &wnd1d, &wnd2d, &subwnd11, &subwnd12, &subwnd13, &subwnd21, &subwnd22, &subwnd23, &tabwin);
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);

	return 0;
}
