/*
 ============================================================================
 Name        : Laboratorio13.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
#define max 5
int main (int argc, char *argv[]) {
  srand(time(NULL));
  int tid,numThreads ;
  int sumcritical=0,sum=0;
  int x[max];
  printf("\nValores aleatorios: ");
  for(int i=0; i<max;i++){
       x[i]=rand()%10;
       printf("\n %d",x[i]);
  }

  omp_set_num_threads(max);

  #pragma omp parallel private(tid,numThreads)
  {
      int sumlocal=0;
        tid = omp_get_thread_num();
        numThreads = omp_get_num_threads();

        for(int i=tid*(max/numThreads); i<(tid+1)*(max/numThreads);i++){

            sumlocal=sumlocal+x[i];
            //printf("\nHilo %d : %d %d",tid,x[i],sumlocal);
        }
        sum+=sumlocal;
      #pragma omp critical
        {
        sumcritical+=sumlocal;
        }



  }
  printf("\n\tSuma empleando exclusion mutua: %d",sumcritical);
  printf("\n\tSuma sin exclusion mutua: %d \n",sum);

 return 0;
}



