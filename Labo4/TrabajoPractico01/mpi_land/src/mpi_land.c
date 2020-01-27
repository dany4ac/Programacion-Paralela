/*
 ============================================================================
 Name        : mpi_land.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Obtenga el número de procesos y verifique que solo se utilicen 4.
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

    // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
    bool my_value = (my_rank != 3);
    bool reduction_result = false;
    MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LAND, root_rank, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        printf("El lógico y de todos los valores es %s.\n", reduction_result ? "true" : "false");
    }

    MPI_Finalize();

    return 0;
}
