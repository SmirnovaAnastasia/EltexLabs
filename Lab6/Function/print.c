#include "../function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_all(struct user all_user[], int size)
{	
	printf("\n==============================================\n");
	printf("First name | Second name | Telefon number\n");
	printf("==============================================\n");
	if(size > 0)
	{
		for (int i = 0; i < size; ++i)
		{
			printf("%d) %s | %s | %s\n", i+1, all_user[i].name, all_user[i].second_name, all_user[i].tel);
		}
	}else
	{
		printf("Nothing to print!\n");
	}

	printf("==============================================\n\n");

}