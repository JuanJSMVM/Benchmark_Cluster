/*************************************************
 * Fecha:   09-agosto-2022
 * Autor:   Juan Pablo Barrios Suarez
 * Materia: Parallel and Distribuited Computing
 * Tema:    Construcción Benchmark Multiplicación de matrices
**************************************************/
#include "mm_lib.h"
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/**** 
 * Definición de las estructuras de tomas de tiempo de inicio y fin  
****/
struct timespec inicio_cuenta, fin_cuenta;

/**** 
 * Función evaluación inicio de tiempo  
****/
void punto_prueba_inicial(){
    clock_gettime(CLOCK_MONOTONIC, &inicio_cuenta);
}

/**** 
 * Función evaluación final de tiempo e impresión de resultado  
****/
void punto_prueba_final(){
    double total_time;
    clock_gettime(CLOCK_MONOTONIC, &fin_cuenta);
    total_time = (fin_cuenta.tv_sec - inicio_cuenta.tv_sec) * 1e9;
    total_time = (total_time + fin_cuenta.tv_nsec - inicio_cuenta.tv_nsec)* 1e-9;
    printf("%f\n",total_time);
}

/****
 * Inicialización de matrices (entera)
****/
void inicializacion_mm_int(int *a, int *b, int *c, int N){
    int i, j;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            a[i+j*N] = 2 * (i+j);
            b[i+j*N] = 2 * i + 3 * j;
            c[i+j*N] = 0;
        }
    }
}

/****
 * Inicialización de matrices (double)
****/
void inicializacion_mm_double(double *a, double *b, double *c, int N){
    int i, j;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            a[i+j*N] = 2.1 * (i+j);
            b[i+j*N] = 2.2 * i + 3.3 * j;
            c[i+j*N] = 0.0;
        }
    }
}

/****
 * Impresión de matrices (entera)
****/
void impresion_mm_int(int *matriz, int N){
    if(N<5){
        int i, j;
        for (i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                printf("%d  ", matriz[j+i*N]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

/****
 * Impresión de matrices (double)
****/
void impresion_mm_double(double *matriz, int N){
    if(N<5){
        int i, j;
        for (i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                printf("%f  ", matriz[j+i*N]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

/****
 * Función Multiplicación Enteros
 * (multiplicación de matrices de valores enteros)
****/
void multiplicacion_mm_int(int *a, int *b, int *c, int N){
    int i, j, k;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            int suma = 0;

            /**** Punteros auxiliares ****/
            int *pA, *pB;
            pA = a + (j*N);
            pB = b + i;

            for (k = 0; k < N; k++, pA++, pB+=N) {
                /**** Multiplicación y suma de resultados ****/ 
                suma += (*pA * *pB);
            }
            c[j+i*N] = suma;
        }
    }
}

/****
 * Función Multiplicación Double
 * (multiplicación de matrices de valores de tipo double)
****/
void multiplicacion_mm_double(double *a, double *b, double *c, int N){
    int i, j, k;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            double suma = 0.0 ;
            /* Punteros auxiliares */
            double *pA, *pB;
            pA = a + (j*N);
            pB = b + i;

            for (k = 0; k < N; k++, pA++, pB+=N) {
                /* Multiplicación y suma de resultados */ 
                suma += (*pA * *pB);
            }
            c[j+i*N] = suma;
        }
    }
}

/****
 * Función para crear enteros aleatorios
****/
int random_int(){
    int min = 0, max = 9;
    static int flag = -1;
    if((flag = (flag<0)))
        srand(time(NULL) + getpid());
    if(min > max) return errno = EDOM, NAN;

    return min + (int) rand()/((int) RAND_MAX/(max-min));
}

/****
 * Función para crear valores double aleatorios
****/
double random_double(){
    double min = 0.0, max = 9.9;
    static int flag = -1;
    if((flag = (flag<0)))
        srand(time(NULL) + getpid());
    if(min > max) return errno = EDOM, NAN;

    return min + (double) rand()/((double) RAND_MAX/(max-min));
}

/****
 * Inicialización de matrices aleatoria (enteros)
****/
void inicializacion_mm_int_rnd(int *a, int *b, int *c, int N){
    int i, j;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            a[i+j*N] = random_int();
            b[i+j*N] = random_int();
            c[i+j*N] = 0;
        }
    }
}

/****
 * Inicialización de matrices aleatoria (double)
****/
void inicializacion_mm_double_rnd(double *a, double *b, double *c, int N){
    int i, j;
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            a[i+j*N] = random_double();
            b[i+j*N] = random_double();
            c[i+j*N] = 0;
        }
    }
}
