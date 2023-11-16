#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	printf("Print dimension of the matrix: ");
	scanf("%d", &n);
	int arr[n][n];

	int count = 0;
	int i = 0, j = 0;
	int max = n - 1, min = 0;
	int pos = 1;

	while(count != n * n){
		count++;
		arr[i][j] = count;
		switch(pos){
		case 1:
			if(j == max){
				pos = 2;
				i++;
			}
			else{
				j++;
			}
			break;
		case 2:
			if(i == max){
				pos = 3;
				max--;
				j--;
			}
			else{
				i++;
			}
			break;
		case 3:
			if(j == min){
				pos = 4;
				min++;
				i--;
			}
			else{
				j--;
			}
			break;
		case 4:
			if(i == min){
				pos = 1;
				j++;
			}
			else{
				i--;
			}
			break;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(arr[i][j] < 10){
				printf(" %d ", arr[i][j]);
			}
			else{
				printf("%d ", arr[i][j]);
			}
		}	
		printf("\n");	
	}
	return 0;
}
