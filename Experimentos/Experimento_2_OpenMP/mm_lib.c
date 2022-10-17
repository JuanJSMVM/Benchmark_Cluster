/********************************************************************************************
* Fecha: 9 Agosto 2022 
* Profesor: John Corredor, PhD
* Autor: Edna Sofia Orjuela Puentes
* Tema: Construcción Benchmark Multiplicacion de matrices
* Evaluar de forma exhaustiva de cualquier aspecto (Jerarquia de memoria y procesamiento)
*********************************************************************************************/


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

typedef struct argumentos_hilos{
	/*Matrices doubles*/
	double *Arg_matA;
	double *Arg_matB;
	double *Arg_matC;  
	int Arg_Num_Hilos; /*Cantidad de hilos*/
	int Arg_N;         /*Dimension de la matriz*/
	int Arg_ID_hilo;

}arg_hilos;

/** Funcion puntero para envio de PROBLEMA **/
/* La idea principal es dividir la Matriz A en porciones,
* tal que cada porcion vaya a un hilo. Cada hilo se podrá
* identificar, pasando como argumento a la función. La
* solución planteada envia toda la matriz B para cada hilo.
*/

void *mm_clasica(void *argHILO_mm ){
//Se castea argHilo como arg_hilos de la estructura de datos 
double *a= ((arg_hilos *)argHILO_mm)->Arg_matA;
double *b= ((arg_hilos *)argHILO_mm)->Arg_matB;
double *c= ((arg_hilos *)argHILO_mm)->Arg_matC;
int ID_Hilo = ((arg_hilos *)argHILO_mm)->Arg_ID_hilo;//Identificación del hilo
int N_mm = ((arg_hilos *)argHILO_mm)->Arg_N;
int NumHilos_mm = ((arg_hilos *)argHILO_mm)->Arg_Num_Hilos;

int porcion = N_mm /NumHilos_mm;//Porcion de la matriz
int ini_porcion, fin_porcion;//Inicio y fin de la porcion
ini_porcion = ID_Hilo*porcion;//Inicio de la porcion
fin_porcion = (ID_Hilo+1)*porcion;//Fin de la porcion

for(int i=ini_porcion;i<fin_porcion;i++){
	for(int j=0;j<N_mm ;j++){
		double suma= 0;
		/**Punteros Auxiliares **/
		double *pA,*pB;
		  pA = a + (i*N_mm);
		  pB = b + j;
		for(int k=0;k<N_mm ;k++,pA++,pB+=N_mm ){
			suma+=(*pA * *pB);
		}
		c[j+i*N_mm ] = suma;
	}

}
return EXIT_SUCCESS;
}

/**************** Función Inicialización ****************/
void inicializar_double(double *matrizA,double *matrizB, double *matrizC,int n){
	int i,j;
	/*Todo lo que pasa en esta funcion se ve reflejado en el vector a,b,c */
	for (i=0;i<n;i++){
		for(j=0;j<n;j++){
		  matrizA[i+j*n]= 2.0*(i+j);
		  matrizB[i+j*n] = 2.0*i+3.0*j;
		  matrizC[i+j*n]= 0.0;
		}
	}
}

/**************** Función Impresión ****************/
void impresion_double(double *matriz, int n){
	int  i,j;
	if(n<5){
	for (i=0;i<n;i++){
		for(j=0;j<n;j++){
		  printf(" %f",matriz[j+i*n]);	  
		}
		printf("\n");
	}
	printf("\n\n");
	}
}


/**** Benchmark 01 *****/
/***** Multiplicación de Matrices: Por punteros*****/
void mm_c_double(double *matrizA, double *matrizB, double *matrizC, int N){
	double suma;
	int i,j,k;
	for (i=0;i<N;i++){
		for(j=0;j<N;j++){
		  suma=0.0;
		  /**Punteros Auxiliares **/
		  double  *pA,*pB;
		  pA = matrizA + (i*N);
		  pB = matrizB + j;
		  /*Puntero A aumenta por la misma fila*/
		  /*Puntero B aumenta por la misma columna, lo hace por saltos*/
			for(k=0;k<N;k++,pA++,pB+=N){
				suma+=(*pA * *pB);
			}
			matrizC[j+i*N]=suma;
		}
	}
}

/*Estructura de datos, metodos que representan una estructura de tipo main*/
struct timespec inicioCuenta,  finCuenta;

/****Funcion evaluacion inicio del tiempo *****/
void punto_prueba_inicial(){
	/*Clock principal del kernell*/
	/*Balanceo de cargas multicores*/
	/*Tiempo global Lo ve desde arriba la ejecucion de procesos*/
	/*Planificador poder identificador de proceso, pedir en que momento pedir el tiempo, y segun que hace el proceso
	  			
	*/
 	clock_gettime(CLOCK_MONOTONIC,&inicioCuenta);
}

/****Funcion evaluacion final del tiempo, impresión de resultados *****/
void punto_prueba_final(){
	double total_time;
 	clock_gettime(CLOCK_MONOTONIC,&finCuenta);
 	total_time = (finCuenta.tv_sec - inicioCuenta.tv_sec)*1e9;
 	total_time = (total_time + finCuenta.tv_nsec - inicioCuenta.tv_nsec)*1e-9;
 	/*De segundos a nanosegundos y luego a segundos*/
 	printf("%f\n",total_time); 	
}

/*Benchmark 06: Se hará uso de openMP con el propósito
* de hacer el balanceo o la división de cargas, para cada hilo usando
* el API, la idea principal es no hacer la división de forma manual como 
* pthreads, sino que sea transparente por parte del API de openMP*/

/*Multiplicación de matrices: clásica*/
void mm_c(double *matrizA, double *matrizB, double *matrizC, int N, int num_hilos){
	omp_set_num_threads(num_hilos); //definir el número de hilos
	
 //declara un zona en paralelo
#pragma omp parallel
{
	int i,j,k;
	double suma;
//el próximo for se va a paralelizar
#pragma omp for 
	for (i=0;i<N;i++){
		for(j=0;j<N;j++){
		  suma=0.0;
		  /**Punteros Auxiliares **/
		  double  *pA,*pB;
		  pA = matrizA + (j*N);
		  pB = matrizB + i;
		  /*Puntero A aumenta por la misma fila*/
		  /*Puntero B aumenta por la misma columna, lo hace por saltos*/
			for(k=0;k<N;k++,pA++,pB+=N){
				suma+=(*pA * *pB);
			}
			matrizC[j+i*N]=suma;
		}
	}
}

}


/*Para aprovechar el principio de localidad espacial, 
*se transformará la multiplicación de matrices filas x filas */
void mm_f(double *matrizA, double *matrizB, double *matrizC, int N, int num_hilos){
	omp_set_num_threads(num_hilos); //definir el número de hilos
	
 //declara un zona en paralelo
#pragma omp parallel
{
	int i,j,k;
	double suma;
//el próximo for se va a paralelizar
#pragma omp for 
	 
	for (i=0;i<N;i++){
		for(j=0;j<N;j++){
		  suma=0.0;
		  /**Punteros Auxiliares **/
		  double  *pA,*pB;
		  pA = matrizA + (i*N);
		  pB = matrizB + (j*N);
		  /*Puntero A aumenta por la misma fila*/
		  /*Puntero B aumenta por la misma columna, lo hace por saltos*/
			for(k=0;k<N;k++,pA++,pB++){
				suma+=(*pA * *pB);
			}
			matrizC[N*i+j]=suma;
		}
	}
}

}




