/*
 ============================================================================
 Name        : faltorial.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long *factorial(long n){
	long *r = (long*)malloc(1*sizeof(long));
	long i = 1;
	long f = 1;

	while(i<=n){
		f = f*i;
		i++;
	}

	r[0] = f;
	printf("factorial de %ld es %ld\n", n, f);

	return r;
}

void* factorial_(void* args){
	long n = *((long*)args);
	return (void*)factorial(n);
}

int main(int args, char **argv){
	long n;
	pthread_t thread[1];
	printf("El factorial del numero: ");
	scanf("%ld", &n);

	pthread_create(&thread[0], NULL, factorial_, &n);
	pthread_join(thread[0], NULL);
	return 0;

}

/*
 *
 *
 *
 *
 *
 * */




