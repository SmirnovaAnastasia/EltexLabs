#include <stdio.h>

void count_one(int num){	
	int res;
	int num_rec = num;
	//printf("%d in binary form - ", num);

	int num_count = 0;
	int one_count = 0;
	while(num_rec >= 1)
	{
		res = num >> num_count;
		res = res & 1;
		if(res == 1){ one_count++; }
		num_count++;
		num_rec /= 2;
	}
	printf("Count of 1 in %d = %d\n", num, one_count);	
}

int main(){
	int dec_form;
	printf("Enter positive number: ");
	scanf("%d", &dec_form);
	if(dec_form >= 1){
		count_one(dec_form);
	}else{
		printf("Error! Wrong data!\n");
	}
	return 0;
}

