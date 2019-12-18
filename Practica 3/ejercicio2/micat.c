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

void micat(orden *O)
{
	//Usamos stat para hallar el tamano del archivo
	struct stat est;
    off_t tam;
    char *mapa;
    int fd;
    //Abrimos el archivo al que hacer cat
    if ((fd = open (O->argv[1], O_RDONLY)) == -1) //Se abre solo con permiso de escritura
	{
    	perror ("open");
    }
	//Obtenmos sus datos
    if (fstat (fd, &est) == -1) 
	{
        fprintf(stderr,"\n	ERROR: no se ha realizado el stat");
    }
	//Realizamos su proyeccion a memoria con mmap
    mapa = mmap (0, est.st_size, PROT_READ, MAP_SHARED, fd, 0);
	//En caso de que falle
    if (mapa == MAP_FAILED) 
	{
    	fprintf(stderr,"\n	ERROR: no se ha proyectado bien a memoria");
    }
	//Como tenemos los datos en memoria cerramos el archivo
    if (close (fd) == -1) 
	{
	    fprintf(stderr,"\n	ERROR: no se ha cerrado el archivo");
    }
	//Vamos imprimiendo cada caracter del archivo que se ha llamado mapa
    for (tam = 0; tam < est.st_size; tam++){ putchar(mapa[tam]); } 
	//Liberamos finalmente la memoria con munmap
    if (munmap (mapa, est.st_size) == -1) 
	{
        fprintf(stderr,"\n	ERROR: no se ha liberado la memoria"); 
    }
}

