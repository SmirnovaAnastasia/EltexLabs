#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("Print dimension of the array: ");
	int n;
	scanf("%d", &n);
	int arr[n];

	printf("Print array:\n");
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
	}

	printf("Reverse array:\n");
	for (int i = n - 1; i >= 0 ; --i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}