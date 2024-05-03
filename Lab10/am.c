#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	printf("%s %s\n", argv[1], argv[2]);
	int aint = atoi(argv[1]);
	int bint = atoi(argv[2]);

	printf("%d + %d = %d\n", aint, bint, aint + bint);
	return 0;
}