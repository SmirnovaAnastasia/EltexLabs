#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"

int main(){
	int answer = 0;
	char answer_ch[2];
	char ap1_ch[5], ap2_ch[5];
	char *pEnd;
	int ap1, ap2;
	while(1){
		printf("1) Addition\n\
2) Subtraction\n\
3) Division\n\
4) Multiplication\n\
5) Exit\n\
============================================\n-> ");
		for (int i = 0; i < 5; ++i)
		{
			ap1_ch[i] = 0;
			ap2_ch[i] = 0;
		}

		if(fgets(answer_ch, 2, stdin) != NULL){
			answer = atoi(answer_ch);
		}else{
			perror("Critical error!");
		}

		getchar();

		if(answer != 5){
			printf("Print two integer numbers:\n");

			fgets(ap1_ch, 5, stdin);
			fgets(ap2_ch, 5, stdin);
			if(ap2_ch != NULL || ap2_ch != NULL){
				ap1 = atoi(ap1_ch);
				ap2 = atoi(ap2_ch);
			}else{
				perror("Critical error!");
			}
			//printf("answer = %d | ap1 = %d | ap2 = %d\n", answer, ap1, ap2);

			if(ap1 % 1 != 0 || ap2 % 1 != 0){ //
				printf("Wront numbers! Please write again\n");
				printf("============================================\n");
				break;
			}

			switch(answer){
			case 1:
				addfun(ap1, ap2);
				break;
			case 2:
				subfun(ap1, ap2);
				break;
			case 3:
				divfun(ap1, ap2);
				break;
			case 4:
				mulfun(ap1, ap2);
				break;
			default:
				printf("Wront data! Please write again\n");
				printf("============================================\n");
				break;
			}
		}else{
			return 0;
		}
	}
	return 0;
}