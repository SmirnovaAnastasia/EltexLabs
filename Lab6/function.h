#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#define n 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

struct user
{
	char name[10];
	char second_name[10];
	char tel[10];
};	


struct user* add_user(struct user all_user[], int size);
void print_all(struct user all_user[], int size);
struct user* remove_user(struct user all_user[], int size, char* rem_name, char* rem_second_name);
void search_user(struct user all_user[], int size, char* search_name);

#endif /* End of function.h */