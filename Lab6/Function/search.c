#include "../function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void search_user(struct user all_user[], int size, char* search_name)
{
	int count = 0;
	printf("\n==============================================\n");
	printf("First name | Second name | Telefon number\n");
	printf("==============================================\n");

	for (int i = 0; i < size; ++i)
	{
		if(strcmp(all_user[i].name, search_name) == 0)
		{
			count++;
			printf("%d) %s | %s | %s\n", count, all_user[i].name, all_user[i].second_name, all_user[i].tel);
		}
	}

	if(count == 0){
		printf("Nothing wasn't searched!\n");
	}
	printf("==============================================\n\n");

}