#include <stdio.h>

//int -> 4 baits
//char -> 1 baits

int main(int argc, char const *argv[])
{
	int pos_num, change_num;
	printf("Enter postive number: ");
	scanf("%d", &pos_num);

	printf("Enter number for change: ");
	scanf("%d", &change_num);

	if(pos_num <= 0 || change_num > 255){
		printf("Warning! Wrong data!\n");
	}else{
		printf("This number in system: ");
		char *ptr = &pos_num;
		printf("%d.", *ptr);
		ptr++;
		printf("%d.", *ptr);
		ptr++;
		printf("%d.", *ptr);
		int three_bait = *ptr;
		*ptr = change_num;
		ptr++;
		printf("%d\n", *ptr);

		printf("Changing %d to %d\n", three_bait, change_num);
		printf("Result: %d\n", pos_num);
	}
	return 0;
}

//660806 -> 4 baits
//00001010.00010101.01000110 
//0.10.21.70

//20 = 10100
//00010100.00010101.01000110 
//0.20.21.70