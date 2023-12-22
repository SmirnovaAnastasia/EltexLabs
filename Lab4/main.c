#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define n 100

struct user
{
	char name[10];
	char second_name[10];
	char tel[10];
};

int add_user(struct user all_user[], int size)
{
	if(size <= 100)
	{
		size++;
		char ch_name, ch_second_name, ch_tel;
		printf("Print name: ");
		scanf("%s", all_user[size-1].name);
		printf("Print second name: ");
		scanf("%s", all_user[size-1].second_name);
		printf("Print telefon number: ");
		scanf("%s", all_user[size-1].tel);
		printf("User was added!\n");
		printf("==============================================\n\n");
	}else
	{
		printf("Overflow of the directory! You can't add new user!\n");
		printf("==============================================\n\n");
	}

	return size;
}

int remove_user(struct user all_user[], int size, char* rem_name, char* rem_second_name)
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
	return size;
}

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

int main(int argc, char const *argv[])
{
	struct user all_user[n];
	int size = 100;

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
			size = add_user(all_user, size);
			break;
		case 2:
			printf("Print name: ");
			char* rem_name = malloc(sizeof(*rem_name));
			scanf("%s", rem_name);
			printf("Print second name: ");
			char* rem_second_name = malloc(sizeof(*rem_second_name));
			scanf("%s", rem_second_name);
			size = remove_user(all_user, size, rem_name, rem_second_name);
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

	return 0;
}