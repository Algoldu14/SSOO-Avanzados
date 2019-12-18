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
void micp(orden *O)
{
	//Necesitamos dos descriptores en este caso
	int fd1,fd2;
	int tam;
	//Abrimos el primero
	if ((fd1 = open(O->argv[1],O_RDONLY))==-1)
	{
		fprintf(stderr,"\n	ERROR: no se ha podido abrir el archivo");
	}
	//Hallamos su tamaño con lseek
	if ((tam = lseek (fd1,0,SEEK_END))==-1)
	{
		fprintf(stderr,"\n	ERROR: no se ha podido saber el tamaño");
	}
	//Creamos el buffer con el tamaño del archivo1 (Esta era la unica forma para evitar warnings)
	char *buf[tam];
	//Abrimos el segundo archivo
	if ((fd2 = open(O->argv[2],O_WRONLY))==-1)
	{
		fprintf(stderr,"\n	ERROR: no se ha podido abrir el archivo");
	}
	//Comenzamos a leer el archivo posicionando lseek al principio y usando read
	lseek (fd1,0,SEEK_SET);
	read (fd1, &buf, tam);
	//Escribimos los datos en el otro archivo
	write(fd2 , &buf, tam);
	//Finalmente cerramos ambos
	close(fd1);
	close(fd2);
	
}
