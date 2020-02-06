/*
 ============================================================================
 Name        : facto.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Calculate Pi in MPI
 ============================================================================
 */
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int myRank;
    int size;
    int fact;
    int lower,upper;
    int i;
    double local_result = 1.0;
    double total;

    /* initialize MPI */
    MPI_Init(&argc,&argv);
    /* Obtener mi rango y el tamaño del comunicador */
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* obtener la entrada (solo si tengo rango 0) */
    if(myRank==0){
        printf("ingresa numero:");
        scanf("%d",&fact);
    }
    /* ya que solo el proceso con rango 0 tiene la entrada,
     * Lo debemos pasar a todos los demás procesos. */

    MPI_Bcast(&fact, /* in/out parameter */
              1,     /* count */
              MPI_INT, /* datatype */
              0,       /* root */
              MPI_COMM_WORLD); /* communicator */

    /* calcular los límites superior e inferior
     * para cada proceso
     */
    if(myRank==0){
        lower = 1;
    }else
        lower = myRank * (fact / size) + 1;
    if(myRank==(size-1))
        upper = fact;
    else
        upper = (myRank + 1) * (fact / size);

    /* ahora que sabemos superior e inferior,
     * multiplicamos en nuestra área local
     */
    for(i=lower;i<=upper;i++){
        local_result = local_result * (double)i;
    }

    /* combine todos los resultados locales multiplicándolos
     * juntos
     */
    MPI_Reduce(&local_result, /* operand */
               &total,        /* result */
               1,             /* count */
               MPI_DOUBLE,    /* datatype */
               MPI_PROD,      /* operator */
               0,             /* root rank */
               MPI_COMM_WORLD); /* communicator */

    /* dar la salida al usuario */
    if(myRank==0){
        printf("el factorial de %d is %lf, y se calculo usando %d procesos\n",fact,total,size);
    }

    /* apague MPI */
    MPI_Finalize();

    return 0;
}
