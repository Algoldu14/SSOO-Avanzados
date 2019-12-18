#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include "parser.h"
void mils(orden *O)
	{
	//Necesitamos esta vez otro tipo de descriptor y estructura
	DIR *dir;
	struct dirent *ent;
	//Abrimos el directorio y comprobamos que haya introducido algo el usuario
	if ((O->argv[1] == NULL)||((dir = opendir (O->argv[1]))==NULL)) 
		{
		dir = opendir ("."); //Crea el directorio con el nombre de .
  		} 
	//Obtenemos todos directorios hasta que no haya mas
	while ((ent = readdir (dir)) != NULL)
		{
		//Imprimimos su nombre
    	printf ("%s\n", ent->d_name);
 		}
	//Se cierra el directorio
  	closedir (dir);
	
	}
