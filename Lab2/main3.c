#include <stdio.h>

int main(int argc, char const *argv[])
{
	int count;
	printf("Print dimension of the matrix: ");
	scanf("%d", &count);

	for (int i = 1; i <= count; ++i)
	{
		for (int j = 1; j <= count; ++j)
		{
			if(i + j >= count + 1){
				printf("1 ");
			}
			else{
				printf("0 ");
			}
		}
		printf("\n");
	}
	return 0;
}