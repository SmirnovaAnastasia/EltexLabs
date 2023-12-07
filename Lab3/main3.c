#include <stdio.h>

int main(int argc, char const *argv[])
{
	int arr[10];
	int *ptr;

	for (int i = 1; i <= 10; ++i)
	{
		arr[i-1] = i;
	}

	ptr = &arr;
	printf("Print an arr using a pointer:\n");
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", *ptr);
		ptr++;
	}
	printf("\n");
	return 0;
}