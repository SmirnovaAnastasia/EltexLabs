#include "../function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user* remove_user(struct user all_user[], int size, char* rem_name, char* rem_second_name)
{
	int is_searched = 0;
	for (int i = 0; i < size; ++i)
	{
		if(strcmp(all_user[i].name, rem_name) == 0 && strcmp(all_user[i].second_name, rem_second_name) == 0)
		{
			is_searched = 1;
			if(size > 1)
			{
				for (int j = i; j < size-1; ++j)
				{
					all_user[j] = all_user[j+1];
				}
				size--;
			}else{
				for (int j = 0; j < strlen(all_user[i].name); ++j)
				{
					all_user[i].name[j] = '0';
				}

				for (int j = 0; j < strlen(all_user[i].second_name); ++j)
				{
					all_user[i].second_name[j] = '0';
				}

				for (int j = 0; j < strlen(all_user[i].tel); ++j)
				{
					all_user[i].tel[j] = '0';
				}

				size--;
				all_user = (struct user*)realloc(all_user, (size * sizeof(struct user)));
			}
		}
	}

	if(is_searched == 0)
	{
		printf("Nothing was removed\n");
	}else
	{
		printf("User was removed!\n");
	}
	printf("==============================================\n\n");
	return all_user;
}