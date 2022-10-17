/********************************************************************************************
* Fecha: 9 Agosto 2022 
* Profesor: John Corredor, PhD
* Autor: Edna Sofia Orjuela Puentes
* Tema: Construcción Benchmark Multiplicacion de matrices
*Evaluar de forma exhaustiva de cualquier aspecto (Jerarquia de memoria y procesamiento)
*********************************************************************************************/


#include <stdlib.h> /*Para el atof*/
#include "mm_lib.h"
#include <pthread.h>
#include <stdio.h>
#include <omp.h>

/** Se declaran las variables GLOBALES, en una estructura de datos**/



int main(int argc, char **argv){
	double *matA, *matB, *matC;
	/*Puntero no se de que dimension es, apunta a un metaVector cuya dimension no se cual es*/
	int N=(int)atof(argv[1]);
	int MAX_NUM_HILOS = omp_get_max_threads();
//	printf("\nNumero de hilos maximos permitidos: %d\n",MAX_NUM_HILOS);
	/*Num_Hilos<= num_max_hilos disponibles and Num_Hilos > 0*/
	int Num_Hilos = MAX_NUM_HILOS;

	//Se asigna un espacio en memoria de manera dinámica por medio del malloc
	matA = (double *)malloc(N*N* sizeof(double));
	matB = (double *)malloc(N*N*sizeof(double));
	matC = (double *)malloc(N*N*sizeof(double));

	inicializar_double(matA,matB,matC,N);
	impresion_double(matA,N);
	impresion_double(matB,N);
	punto_prueba_inicial();
	mm_f(matA,matB,matC,N,Num_Hilos);
	//mm_c_double(a,b,c,N);
	punto_prueba_final();
	impresion_double(matC,N);
	/** Liberacion de Reserva de memoria MALLOC **/

	free(matA);
	free(matB);
	free(matC);

return 0;
}


