/*
 ============================================================================
 Name        : mpi_max.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 5)
    {
        printf("Esta aplicación está diseñada para ejecutarse con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determine root's rank
    int root_rank = 0;

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int reduction_result = 0;
    MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_MAX, root_rank, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        printf("El máximo de todos los rangos es %d.\n", reduction_result);
    }

    MPI_Finalize();

    return 0;
}
