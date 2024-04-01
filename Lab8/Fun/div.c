#include <stdio.h>
#include "../operation.h"

void divfun(int ap1, int ap2){
	double answer = 0;
	double ap1_d = ap1;
	double ap2_d = ap2;
	answer = ap1_d / ap2_d;
	printf("%d : %d = %.3f\n", ap1, ap2, answer);
	printf("============================================\n");
}
