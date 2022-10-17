/********************************************************************************************
* Fecha: 9 Agosto 2022 
* Profesor: John Corredor, PhD
* Autor: Edna Sofia Orjuela Puentes
* Tema: Construcción Benchmark Multiplicacion de matrices
*Evaluar de forma exhaustiva de cualquier aspecto (Jerarquia de memoria y procesamiento)
*********************************************************************************************/

#ifndef MM_LIB_H_INCLUDED /*Si no esta definido */
#define MM_LIB_H_INCLUDED /*definalo */

void mm_c(double *matrizA, double *matrizB, double *matrizC, int N, int num_hilos);
void mm_f(double *matrizA, double *matrizB, double *matrizC, int N, int num_hilos);
void *mm_clasica(void *args);
/**************** Función Inicialización ****************/
void inicializar_double(double *matrizA,double *matrizB,double *matrizC,int n);

/**************** Función Impresión ****************/
void impresion_double(double*matriz, int n);

/***** Multiplicación de Matrices: Clasica *****/
/*void mm_c_regular(int *matrizA,int *matrizB,int *matrizC,int n);*/

/***** Multiplicación de Matrices: Por punteros*****/
void mm_c_double(double *matrizA,double *matrizB,double*matrizC,int N);

void punto_prueba_inicial();

/****Funcion evaluacion final del tiempo, impresión de resultados *****/
void punto_prueba_final();

#endif
