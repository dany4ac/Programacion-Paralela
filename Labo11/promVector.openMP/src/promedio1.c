/*
 ============================================================================
 Name        : promedio1.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
//#define NUM_THREADS 4
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	int n,i;
	float s = 0.0;
	float prom;

	printf("Ingrese numero de elementos: ");
	scanf("%d", &n);
	int A[n];

	for(int m = 0; m<n; m++){
		A[m] = rand()%51;
	}

	for(int m=0; m<n; m++){
		printf("%d ", A[m]);
	}

	printf("\n 01 Fuera de la region Paralela ...\n\n");

	omp_set_num_threads(5);

	float sum[omp_get_num_threads()];

	/* This constructor for parallel threads  */
	#pragma omp parallel
	{
		int id = omp_get_thread_num(); //
		int nt = omp_get_num_threads();

		for(i=id, sum[id]=0.0; i<n; i=i+nt){
			sum[id] = sum[id] + A[i];

		}
		printf("%f ", sum[id]);

	}

	printf("\n 02 Fuera de la region Paralela ...\n\n");

	for(int j=0; j<5; j++){ // tenia q ser 5
		s = s+sum[j];

	}

	prom = s/n;

	printf("El promedio es %6.12f\n", prom);

	return 0;
}

