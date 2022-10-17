#/*******************************************************************
#* Fecha: 2 - Agosto - 2022
#* Profesor: John Corredor, PhD
#* Autor: Edna Sofia Orjuela Puentes
#* Materia: Parallel and Distributed Computing 
#* Tema: Introducción a Lenguajde de programación en C
#* Tópico : Script automatización compilación
#*******************************************************************/

GCC = gcc
FLAGS = -ansi -std=c99 -pedantic -Wall  -Wno-unknown-pragmas -D_POSIX_C_SOURCE=199309L
MATHFLAG = -lm -fopenmp

PROGRS = mm_main_double mm_main_clasica mm_main_f

all: $(PROGRS)



mm_main_double:
	$(GCC) $(FLAGS) -c $@.c 
	$(GCC) $(FLAGS) -c mm_lib.c 
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)
		
mm_main_clasica:
	$(GCC) $(FLAGS) -c $@.c $(MATHFLAG)
	$(GCC) $(FLAGS) -c mm_lib.c $(MATHFLAG)
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)	
	
mm_main_f:
	$(GCC) $(FLAGS) -c $@.c $(MATHFLAG)
	$(GCC) $(FLAGS) -c mm_lib.c $(MATHFLAG)
	$(GCC) $(FLAGS) -o $@ $@.o mm_lib.o $(MATHFLAG)	
	

clean:
	$(RM) *.o $(PROGRS)
