/*************************************************
 * Fecha:   09-agosto-2022
 * Autor:   Juan Pablo Barrios Suarez
 * Materia: Parallel and Distribuited Computing
 * Tema:    Construcción Benchmark Multiplicación de matrices
**************************************************/
#include "mm_lib.h"
#include <stdio.h>
#include <stdlib.h>

/****
 * Benchmark MM con valores ENTREROS ALEATORIOS
****/

/****
 * Se requiere reservar un espacio de memoria 
****/
#define DATA_SIZE (1024 * 1024 * 64 * 3)
static int MEM_CHUNK[DATA_SIZE];

/****
 * Función principal de la aplicación 
****/
int main(int argc, char **argv){

    /*** Captura del tamaño de la matriz ***/
    int N; 
    N = (int) atof(argv[1]);
    
    /*** Declaración de matrices con apuntadores a memoria ***/
    int *a, *b, *c;
    a = MEM_CHUNK;
    b =  a + N*N;
    c =  b + N*N;

    inicializacion_mm_int_rnd(a, b, c, N);
    // impresion_mm_int(a, N);
    // impresion_mm_int(b, N);
    

    /****
     * Inicio de toma de tiempo
     * Multiplicación de las matrices A y B
     * Fin de toma de tiempo 
    ****/
    punto_prueba_inicial();
    multiplicacion_mm_int(a, b, c, N);
    punto_prueba_final();

    // impresion_mm_int(c, N);
    
    return 0;
}
