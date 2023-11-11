#include <stdio.h>
#include <math.h>

void three_change(int num, int change_num){
	int rec;

	int num_and = pow(2, 31) - 1;

	int xor = 255 << 16;

	num_and = (num_and ^ xor);

	for (int i = 31; i >= 0; --i)
	{
		rec = num >> i;
		rec = rec & 1;
		printf("%d", rec);
	}
	printf(" <-- num before \n");

	num = num & num_and;
	num = num | (change_num << 16);

	for (int i = 31; i >= 0; --i)
	{
		rec = num >> i;
		rec = rec & 1;
		printf("%d", rec);
	}

	printf(" <-- num after \n");		
}

int main(){
	int dec_form, change_num;
	printf("Enter number: ");
	scanf("%d", &dec_form);
	printf("Enter number to change: ");
	scanf("%d", &change_num);
	if(dec_form >= 1 && change_num < 256){
		three_change(dec_form, change_num);
	}else{
		printf("Error! Wrong data!\n");
	}
	return 0;
}
