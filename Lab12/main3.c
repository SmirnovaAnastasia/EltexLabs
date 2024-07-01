#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(){
	pid_t child_pid;
	int status;
	char buf[20][100];

	while(1){
		printf("======================================\n");
		printf("Dou want file or regular expression (1 or 2):\n");
		int var = 0;
		scanf("%d", &var);

		if(var == 1){
			printf("Print path, file and two arguments:\n");
			char path[20], name[10], arg1[7], arg2[7];
			scanf("%s%s%s%s", path, name, arg1, arg2);
			child_pid = fork();
			if(child_pid == 0){
				execl(path, name, arg1, arg2, NULL);
			}else{
				wait(&status);
			}
		}else if(var == 2){
			//printf("Print regular expression:\n");
			int fd[2];

			if(pipe(fd)){
				printf("Can't create pipe!");
				return -1;
			}

			//char path1[20], flag_sym[7], and_sym[10], path2[7], find_sym[7];
			char symbol[10];
			printf("Print phrase which you want to find:\n");
			scanf("%s", symbol);

			child_pid = fork();
			if(child_pid < 0){
				perror("fork");
				exit(1);
			}

			if(child_pid == 0){
				close(fd[0]);
				dup2(fd[1], 1);
				char* args[3];
				args[0] = "/usr/bin/ls";
				args[1] = "-la";
				args[2] = NULL;
				execv(args[0], args);
				close(fd[1]);
				printf("Wrong with ls!\n");
			}else{
				wait(&status);
				close(fd[1]);
			}

			child_pid = fork();
			if(child_pid < 0){
				perror("fork");
				exit(1);
			}

			if(child_pid == 0){
				//printf("It's grep pid = %d\n", getpid());
				close(fd[1]);
				dup2(fd[0], 0);
				char* args[3];
				args[0] = "/usr/bin/grep";
				args[1] = symbol;
				args[2] = NULL;
				execv(args[0], args);
				printf("Wrong with grep!\n");
			}else{
				wait(&status);
				close(fd[0]);
			}

		}else{
			printf("Wrong data! Please write again!\n");
		}

	}
	return 0;
}