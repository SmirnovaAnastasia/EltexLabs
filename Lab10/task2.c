#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t child_pid, child_pid1, child_pid2, parent_pid;
	int status;

	printf("It's parent pid = %d\n", getpid());
	for(int i = 0; i<=1; i++){
		child_pid = fork();
		if(child_pid == 0){
			if(i == 0){ //Make 2 children
				printf("\tIF: child_ppid = %d | child_pid= %d\n", getppid(), getpid());
				for (int j = 0; j < 2; j++)
				{
					child_pid1 = fork();
					if(child_pid1 == 0){
						printf("\t\tCh0: child_ppid = %d | child_pid= %d\n", getppid(), getpid());		
						exit(5);	
					}else{
						wait(&status);
						printf("\tIF: status = %d\n", WEXITSTATUS(status));
					}
				}
				exit(5);
			}else if(i == 1){ //Make 1 children
				printf("\tELSE: child_ppid = %d | child_pid= %d\n", getppid(), getpid());
				child_pid2 = fork();
				if(child_pid2 == 0){
					printf("\t\tCh1: child_ppid = %d | child_pid= %d\n", getppid(), getpid());		
					exit(5);	
				}else{
					wait(&status);
					printf("\tElSE: status = %d\n", WEXITSTATUS(status));
					exit(5);
				}

			}
		}else{
			wait(&status);
			printf("PARENT: status = %d\n", WEXITSTATUS(status));
		}
	}

	return 0;
}