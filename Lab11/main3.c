#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 3

long a = 0;
int store[5];

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int update_store(int store){
	int shift, variant;
	shift = rand() % 3000 + 1000;
	if(shift <= 0){
			perror("Data from rand() was wrong!");
			return 1;
		}
		variant = rand() % 2 + 1;
		if(variant <= 0){
			perror("Data from rand() was wrong!");
			return 1;
		}else if(variant == 1){
			store = 10000 + shift;
		}else{
			store = 10000 - shift;
	}
	return store;
}

int gen_thread(int thread){
	int shift, variant;
	shift = rand() % 30000 + 10000;
	if(shift <= 0){
			perror("Data from rand() was wrong!");
			return 1;
		}
		variant = rand() % 2 + 1;
		if(variant <= 0){
			perror("Data from rand() was wrong!");
			return 1;
		}else if(variant == 1){
			thread = 100000 + shift;
		}else{
			thread = 100000 - shift;
	}
	return thread;
}

void *thread_buy(){ //Rewrite
	int i, var;
	int thread_value;
	if((thread_value = gen_thread(thread_value)) <= 0){
		perror("Thread value generated wrong!");
	}
	printf("Thread id = %ld and th_value = %d\n", pthread_self(), thread_value);
	
	while(thread_value > 0){
		var = rand() % 4 + 0;
		pthread_mutex_lock(&m1);
		thread_value -= store[var];
		if (store[var] <= 0)
		{
			store[var] = update_store(store[var]);
		}
		pthread_mutex_unlock(&m1);
		printf("thread_value = %d\n", thread_value);
	}
	printf("Thread %ld buied all things\n", pthread_self());
	return NULL;
}

int main(void){
	srand(time(NULL));
	int *s;

	printf("==================\n");
	for (int i = 0; i < 5; ++i)
	{
		store[i] = 0;
		store[i] = update_store(store[i]);
		if(store[i] <= 0){
			perror("Store update was wrong!");
			return 1;
		}
		printf("store[%d] = %d\n", i, store[i]);
	}
	printf("==================\n");

	pthread_t thread[N];

	for (int i = 0; i < N; ++i)
	{
		pthread_create(&thread[i], NULL, thread_buy, NULL);
	}

	for (int i1 = 0; i1 < N; ++i1)
	{
		pthread_join(thread[i1], (void**)&s);
	}

	return 0;
}