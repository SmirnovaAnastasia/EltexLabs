#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define n 5

void *read_index(void *t){
	//printf("amin ");
	long num = (long)t;
	printf("Thread %ld\n", num);
}

int main()
{
	pthread_t thread[n];
	int *s;
	long t = 0;

	for (int i = 0; i < n; ++i)
	{
		t++;
		int j = pthread_create(&thread[i], NULL, read_index, (void*)t);	
		if(j){
			printf("ERROR: thread isn't create!");
			exit(EXIT_FAILURE);
		}
	}

	for (int i1 = 0; i1 < n; ++i1)
	{
		pthread_join(thread[i1], (void**)&s);
	}

	return 0;
}