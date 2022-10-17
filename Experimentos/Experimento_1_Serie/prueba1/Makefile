#*************************************************
# * Fecha: 		09-agosto-2022
# * Autor: 		Brayan Stiven Castañeda Cruz
# * Materia: 	Parallel and Distribuited Computing
# * Tema: 		Construcción Benchmark Multiplicación de matrices
# * Tópico: 	Script Automatizacion Compilacion
#*************************************************/

# Comandos y banderas necesarias para la correcta compilación  
GCC = gcc
FLAGS = -ansi -std=c11 -pedantic -Wall -D_POSIX_C_SOURCE=199309L
MATHFLAG = -lm 

# Vector de los métodos de compilación
PROGRS = mm_main mm_main_rnd mm_main_double mm_main_double_rnd

# Método de llamado general para ejecutar las compilaciones de todos los bechmarks
all: $(PROGRS) 

# Compilación Benchmark ENTERO
mm_main: 
	$(GCC) $(FLAGS) -c $@.c
	$(GCC) $(FLAGS) -c mm_lib.c
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)

# Compilación Benchmark ENTERO ALEATORIO
mm_main_rnd: 
	$(GCC) $(FLAGS) -c $@.c
	$(GCC) $(FLAGS) -c mm_lib.c
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)

# Compilación Benchmark DOUBLE
mm_main_double: 
	$(GCC) $(FLAGS) -c $@.c
	$(GCC) $(FLAGS) -c mm_lib.c
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)

# Compilación Benchmark DOUBLE ALEATORIO
mm_main_double_rnd: 
	$(GCC) $(FLAGS) -c $@.c
	$(GCC) $(FLAGS) -c mm_lib.c
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)
	
# Método de Limpieza (Eliminación objetos .o y ejecutables) 
clean: 
	$(RM) *.o $(PROGRS)
	