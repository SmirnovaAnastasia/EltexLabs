#include <fcntl.h>
#include <stdio.h>

int main(){
	int f1, f2;
	char buf1[19] = "String from file:)";
	char buf2[19];
	char buf3[3] = ":(";
	f1 = open("amam.c", O_WRONLY);
	f2 = open("amam.c", O_RDONLY);
	write(f1, buf1, 19);
	read(f2, buf2, 19);
	printf("%s\n", buf2);
	lseek(f1, 16, SEEK_SET);
	write(f1, buf3, 3);
	lseek(f2, 0, SEEK_SET);
	read(f2, buf2, 19);
	printf("%s\n", buf2);
	return 0;
}