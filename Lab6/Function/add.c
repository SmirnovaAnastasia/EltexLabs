#include "../function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>


struct user* add_user(struct user all_user[], int size)
{
	size++;
	printf("Size user: %ld\n", size * sizeof(struct user));
	if(size = 1){
		all_user = (struct user*)malloc(sizeof(struct user));
	}else{
		all_user = (struct user*)realloc(all_user, (size * sizeof(struct user)));
		if(all_user == NULL){
			perror("Out of memory!");
			exit(EXIT_FAILURE);
		}
	}
	char ch_name, ch_second_name, ch_tel;
	printf("Print name: ");
	scanf("%s", all_user[size-1].name);
	printf("Print second name: ");
	scanf("%s", all_user[size-1].second_name);
	printf("Print telefon number: ");
	scanf("%s", all_user[size-1].tel);
	printf("User was added!\n");
	printf("==============================================\n\n");

	//printf("%d) %s | %s | %s\n", 1, all_user[0].name, all_user[0].second_name, all_user[0].tel);
	//printf("%d) %s | %s | %s\n", 2, all_user[1].name, all_user[1].second_name, all_user[1].tel);

	return all_user;
}
