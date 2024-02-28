#include <stdio.h>
#include "function.h"
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char const *argv[])
{
	struct user *all_user;
	int size = 0;
	int answer = 0;
	while(1)
	{
		printf("1) Add user\n\
2) Remove user\n\
3) Search user by name\n\
4) Print all records\n\
5) Exit\n==============================================\n->");
		scanf("%d", &answer);
		printf("==============================================\n");

		switch(answer){
		case 1:
			all_user = add_user(all_user, size);
			size++;
			break;
		case 2:
			printf("Print name: ");
			char* rem_name = malloc(sizeof(*rem_name));
			scanf("%s", rem_name);
			printf("Print second name: ");
			char* rem_second_name = malloc(sizeof(*rem_second_name));
			scanf("%s", rem_second_name);
			all_user = remove_user(all_user, size, rem_name, rem_second_name);
			size--;
			break;
		case 3:
			printf("Print name: ");
			char* search_name = malloc(sizeof(*search_name));
			scanf("%s", search_name);
			search_user(all_user, size, search_name);
			break;
		case 4:
			print_all(all_user, size);
			break;
		case 5:
			return 0;
			break;
		default:
			printf("Wrong data! Please write again\n");
			printf("==============================================\n");
			break;
		}

	}
	free(all_user);
	return 0;
}