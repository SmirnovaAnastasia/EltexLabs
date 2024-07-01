#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


#define READ 0
#define WRITE 1
#define size 50


int main(){
	int fd[2];
	char c;
	char buffer[size] = "Hi!:)";
	char buffer2[size];
	int len = strlen(buffer) + 1;
	pid_t pid;
	int status;

	if(pipe(fd)){
		perror("pipe");
		return 1;
	}

	if(pid = fork() > 0){ //Parent
		close(fd[READ]);
		//c = 9;
		write(fd[WRITE], buffer, len);
		printf("Parent process pid: %d\n", getpid());
		printf("Buffer: %s\n", buffer);
		close(fd[WRITE]);
		wait(&status);
	}else if(pid == 0){ //Child
		close(fd[WRITE]);
		read(fd[READ], buffer2, len);
		printf("Child process pid: %d\n", getpid());
		printf("Buffer: %s\n", buffer2);
		//printf
		//puts(buffer2);
		close(fd[READ]);
		exit(5);
		//execl("prog", "prog", NULL);
	}
	return 0;
}
