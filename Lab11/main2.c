#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define n 5
int num = 0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *increase(){
	pthread_mutex_lock(&m1);
	num++;
	printf("I = %d\n", num);
	pthread_mutex_unlock(&m1);
}

int main()
{
	pthread_t thread[n];
	int *s;
	long* sum;

	for (int i = 0; i < n; ++i)
	{
		pthread_create(&thread[i], NULL, increase, NULL);	
	}

	for (int i1 = 0; i1 < n; ++i1)
	{
		pthread_join(thread[i1], (void**)&s);
	}

	return 0;
}