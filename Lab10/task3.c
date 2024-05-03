#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t child_pid;
	int status;
	while(1){
		printf("======================================\n");
		printf("Print path, file and two arguments:\n");
		char path[20], name[10], arg1[7], arg2[7];
		scanf("%s%s%s%s", path, name, arg1, arg2);
		child_pid = fork();
		if(child_pid == 0){
			execl(path, name, arg1, arg2, NULL);
			exit(5);
		}else{
			wait(&status);
		}
	}
	return 0;
}