/*
 ============================================================================
 Name        : OMP.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	int i, j, k, l, m, n;
	float det;
	struct timeval ti, tf;
	double tiempo;
	//int id;

	struct timeval ti1, tf1;
	double tiempo1;

	printf("Introducir el ORDEN DE LA MATRIZ : N = ");
	scanf("%d", &n);
	m = n - 1;

	printf("------------------------ \n ");

	float A[n][n];
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			A[i][j] = rand() % 51;
		}
	}

	/* SI QUEREMOS LEER LOS ELEMENTOS DE LA MATRIZ LISTADOS */
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++)
			printf("\t\t\tA(%d,%d) =%8.4f\n", i, j, A[i][j]);
	}

	//secuencial
	float B[n][n];
	float det1;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++)
			B[i][j] = A[i][j];
	}

	gettimeofday(&ti, 0);
	det1 = B[1][1];
	for (k = 1; k <= m; k++) {
		l = k + 1;
		for (i = l; i <= n; i++) {
			for (j = l; j <= n; j++)
				B[i][j] = (B[k][k] * B[i][j] - B[k][j] * B[i][k]) / B[k][k];
		}
		det1 = det1 * B[k + 1][k + 1];
	}
	gettimeofday(&tf, 0);
	tiempo = (tf.tv_sec - ti.tv_sec) * 1.0f
			+ (tf.tv_usec - ti.tv_usec) / 1000000.0f;

	printf("DETERMINANTE = %f \n", det1);
	printf("tiempo - Secuencial: %lf milisegundos \n", tiempo);

	//paralelizado
	gettimeofday(&ti1, 0);
	det = A[1][1];
#pragma omp parallel
	{int	id = omp_get_thread_num();
	int nt = omp_get_num_threads();
	int size = n / nt;
	int ini = id * size + 1;
	int fin = ini + size - 2;

	for (k = ini; k <= fin; k++) {
		l = k + 1;
		for (i = l; i <= n; i++) {
			for (j = l; j <= n; j++)
				A[i][j] = (A[k][k] * A[i][j] - A[k][j] * A[i][k]) / A[k][k];
		}
		det = det * A[k + 1][k + 1];
	}
	}
	gettimeofday(&tf1, 0);
	tiempo1 = (tf1.tv_sec - ti1.tv_sec) * 1.0f
			+ (tf1.tv_usec - ti1.tv_usec) / 1000000.0f;

	printf("DETERMINANTE = %f \n", det);
	printf("tiempo - Paralelo: %lf milisegundos \n", tiempo1);

	return 0;
}

