/*
 ============================================================================
 Name        : hilos.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

int sum;
void *fibo(void *param);

int main(int argc, char *argv[])
{
	int count, i;
	//pthread_attr_t attr;

	if (argc != 2) {
		fprintf(stderr,"uso de pthreads para fibonacci\n");
		return -1;
	}

	count = atoi(argv[1]);
	if (count < 1) {
		fprintf(stderr,"%d debe ser mayor o igual que 1\n", count);
		return -1;
	}

	//pthread_attr_init(&attr);

	for(i=1;i<=count;i++){
		pthread_t thread;
		pthread_create(&thread,NULL,fibo,(void*)i);
		pthread_join(thread,NULL);
		printf("fibonacci de %d es %d\n", i, sum);
	}
}

void *fibo(void *param)
{
	sum = fibonacci((int)param);
	pthread_exit(0);
}

int fibonacci (int x)
{
    if (x <= 1) {
        return 1;
    }
    return fibonacci(x-1) + fibonacci(x-2);
}


