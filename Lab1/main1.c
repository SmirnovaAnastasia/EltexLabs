#include <stdio.h>

void bin_tran(int num){	
	int res[64];
	int num_rec = num;
	printf("%d in binary form - ", num);

	int count = 0;
	while(num_rec >= 1)
	{
		res[count] = num >> count;
		res[count] = res[count] & 1;
		count++;
		num_rec /= 2;
	}

	for (int i = count - 1; i >= 0; --i)
	{
		printf("%d", res[i]);
	}
	printf("\n");		
}

int main(){
	int dec_form;
	printf("Enter positive number: ");
	scanf("%d", &dec_form);
	if(dec_form >= 1){
		bin_tran(dec_form);
	}else{
		printf("Error! Wrong data!\n");
	}
	return 0;
}

