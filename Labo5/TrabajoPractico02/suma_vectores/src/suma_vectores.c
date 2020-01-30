/*
 ============================================================================
 Name        : suma_vectores.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

//#define MASTER 0
const int MASTER  = 0;
//#define RECIBE 1
const int RECIBE  = 1;
//#define SUMA 2
const int SUMA  = 2;

/* funciones */
void llenar__vector(int VECTOR[], int MAX);
void imprime__vectores(int VECTOR[], int MAX);

int main(int argc, char *argv[])
{
	int rank, size;
	int MAX = atoi(argv[1]);
	int VECTOR__A[MAX], VECTOR__B[MAX];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == MASTER)
	{

		llenar__vector(VECTOR__A, MAX);
		llenar__vector(VECTOR__B, MAX);
		/* mensajes enviados */
		MPI_Send(VECTOR__A, MAX, MPI_INT, RECIBE, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR__B, MAX, MPI_INT, RECIBE, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (rank == RECIBE)
		{
			/* codigo para el nodo que recibirá los vectores */
			MPI_Recv(VECTOR__A, MAX, MPI_INT, MASTER, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(VECTOR__B, MAX, MPI_INT, MASTER, 3, MPI_COMM_WORLD, &status);
			printf("Vector A\n");
			imprime__vectores(VECTOR__A, MAX);
			printf("VECTOR B\n");
			imprime__vectores(VECTOR__B, MAX);
			MPI_Send(VECTOR__A, MAX, MPI_INT, SUMA, 2, MPI_COMM_WORLD);
			MPI_Send(VECTOR__B, MAX, MPI_INT, SUMA, 3, MPI_COMM_WORLD);
		}
		else
		{
			if (rank == SUMA)
			{
				/* codigo para el nodo que sumará los vectores */
				MPI_Recv(VECTOR__A, MAX, MPI_INT, RECIBE, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR__B, MAX, MPI_INT, RECIBE, 3, MPI_COMM_WORLD, &status);
				int VECTOR__RES[MAX];
				int i;
				for(i = 0; i < MAX; i++)
				{
					VECTOR__RES[i] = (VECTOR__A[i] + VECTOR__B[i]);
				}
				printf("VECTOR RESULTANTE\n");
				imprime__vectores(VECTOR__RES, MAX);
			}
		}
	}
	MPI_Finalize();
	return 0;
}

void llenar__vector(int VECTOR[], int MAX)
{
	srand(time(NULL));
	int i;
	for(i = 0; i < MAX; i++)
	{
		VECTOR[i] = (rand()%150) + 1;
	}
}

void imprime__vectores(int VECTOR[], int MAX)
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		printf("%d\n", VECTOR[i]);
	}
}
