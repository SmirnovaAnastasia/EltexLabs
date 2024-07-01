#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#define READ 0
#define WRITE 1
#define size 50


int main(){
	int fd;

	char *mfifo = "./am.txt";
	mkfifo(mfifo, 0666);

	char arr1[80] = "Hi:)\n";
	while(1){
		fd = open(mfifo, O_WRONLY);
		write(fd, arr1, strlen(arr1)+1);
		close(fd);
	}
	return 0;
}
