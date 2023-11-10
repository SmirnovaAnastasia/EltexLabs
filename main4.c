#include <stdio.h>
#include <math.h>

void three_change(int num, int change_num){
	int num_rec = num;
	int rec;
	printf("%d if we change three number on %d - ", num, change_num);

	int count = 0;
	int xor_num = 1 << 3;

	while(num_rec >= 1)
	{
		count++;
		num_rec = num_rec >> 1;
	}

	int num_and = pow(2, count) - 1;
	num_and = num_and ^ xor_num;

	if(change_num == 0){
		num = num & num_and;
	}else{
		num = num | 0b1000;
	}

	if(count < 4){
		count = 4;
	}

	for (int i = count - 1; i >= 0; --i)
	{
		rec = num >> i;
		rec = rec & 1;
		printf("%d", rec);
	}

	printf("\n");		
}

int main(){
	int dec_form, change_num;
	printf("Enter number: ");
	scanf("%d", &dec_form);
	printf("Enter number to change: ");
	scanf("%d", &change_num);
	if(dec_form >= 1 && (change_num == 1 || change_num == 0)){
		three_change(dec_form, change_num);
	}else{
		printf("Error! Wrong data!\n");
	}
	return 0;
}
