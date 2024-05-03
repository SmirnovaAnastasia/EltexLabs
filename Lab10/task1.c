#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t child_pid;
	int status;

	printf("Parent pid = %d\n", getpid());
	child_pid = fork();
	if(child_pid == 0){
		printf("child_ppid = %d | child_pid= %d\n", getppid(), getpid());
		exit(5);
	}else{
		wait(&status);
		printf("status = %d\n", WEXITSTATUS(status));	
	}

	return 0;
}