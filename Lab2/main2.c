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

	for (int i = 0; i <= n/2; ++i)
	{
		int swap = arr[i];
		arr[i] = arr[n - 1 - i];
		arr[n - 1 - i] = swap;
	}

	printf("Reverse array:\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}