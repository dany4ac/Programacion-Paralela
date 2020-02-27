/*
 ============================================================================
 Name        : Lab13-Directiva-Critical.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */

int f(int m) {
	int r = m;
	printf("\n :>%d", r);
	return r;
}

int g(int n, int id) {
	int r = n * n;
	printf("\n :>%d, Hilo:%d", r, id);
	return r;
}

int main(int argc, char *argv[]) {

	int max = 10;
	int x=0;
	int s = 0;
	/* This creates a team of threads; each thread has own copy of variables  */
#pragma omp parallel num_threads(4)
	{
		for (int i = 0; i < max; ++i) {
			x = f(i);

			#pragma omp critical
			{
				int id = omp_get_thread_num();
				s+=g(x, id);
			}
		}
	}

	/* This creates a team of threads; each thread has own copy of variables  */

	printf("\n :>>>>>>> %d",s);
	printf("\n ::::::::::::::::::::::: New Threads \n ");
	s = 0;
#pragma omp parallel num_threads(4)
	{
		for (int i = 0; i < max; ++i) {
			x = f(i);
			int id = omp_get_thread_num();
			s +=g(x, id);
		}
	}
	printf("\n :>>>>>>> %d",s);

	return 0;
}

