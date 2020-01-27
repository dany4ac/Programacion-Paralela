/*
 ============================================================================
 Name        : mpi_band.c
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
    if(size != 4)
    {
        printf("Esta aplicación está diseñada para ejecutarse con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determine root's rank
    int root_rank = 0;

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
    char all_values[4] = {0, 1, 3, 8};
    char my_value = all_values[my_rank];
    char reduction_result = 0;
    MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BAND, root_rank, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        printf("El bit-wise y de todos los valores es %d.\n", reduction_result);
    }

    MPI_Finalize();

    return 0;
}
