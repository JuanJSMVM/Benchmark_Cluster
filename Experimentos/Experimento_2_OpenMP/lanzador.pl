#!/usr/bin/perl


=begin comment

Fecha: 23 Agosto 2022
Autor: Edna Sofia Orjuela Puentes
Tema: Ejecución automatizada de Benchmarks

Perl lenguaje interpretado
Fichero que quiero que interprete pasarlo a ejecutable
$ es para definir una variable 
=end comment
=cut

#Vector para los benchmarks
@Benchmarks = ("mpirun -host nodo1,nodo2,nodo3 ./mm_main_f");

#Vector para las cargas
@Cargas = ("1000","3000","7500");
#Número de repeticiones 
$n = 1;
#Se almacena la ubicacion
$Path ="/home/mpiuser/cloud/Experimentos/Experimento_2_OpenMP";

#Se itera sobre 
#la cantidad de ejecutable 
#sobre la cantidad de cargas
#la cantidad de repeticiones

foreach $exes(@Benchmarks){
	foreach $carga (@Cargas){
	#Se crea un fichero para almacenar los datos
	#Con . se concatena
	$file = "Soluciones/Serial-size-".$carga.".txt";
		#printf("$Path$file\n");
		for ($i=0;$i<$n;$i++){
		system("$exes $carga >>$file");
		#printf("$Path$exes $carga \n");
   	}
   	close($file);
   }
}

