/*
 ============================================================================
 Name        : secuencial.c
 Author      : Dany
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>


int main(){
	int arreglo[16], i, n, contador;
	contador = 0;
	
	for(i = 0; i < 16; i++){
		printf("\n Digite en %d numero de la lista: ", i);
		scanf("%d", &arreglo[i]);
	}
	
	printf("Digite el numero a encontrar: ");
	scanf("%d", &n);
	
	for(i = 0; i < 16; i++){
			if(n == arreglo[i]){
				contador++;
			}
		}
	
	printf("El elmento %d, se repite %d veces", n, contador);
	
	
	return 0;
}
