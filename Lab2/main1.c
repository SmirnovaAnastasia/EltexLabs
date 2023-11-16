#include <stdio.h>

int main(int argc, char const *argv[])
{
	int count;
	printf("Print dimension of the matrix: ");
	scanf("%d", &count);

	int j = 0;
	for (int i = 1; i <= count * count; ++i)
	{
		j++;
		if(count * count > 10 && i < 10){
			printf(" %d ", j);
		}
		else{
			printf("%d ", j);
		}

		if(i % count == 0){
			printf("\n");
		}
	}
	return 0;
}