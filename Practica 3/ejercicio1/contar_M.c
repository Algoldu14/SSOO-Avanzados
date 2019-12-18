#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int ContarCaracteres (int fd, char caracter)
	{
	//Empleamos stat para hallar el tamaño del archivo
	//porque requiere menos llamadas al sistema que LSEEK
	struct stat est;
	off_t i;
	char *mapa;
	int caracteres=0;
	
	//Empleo de fstat con el descriptor pasado
	if (fstat (fd, &est) == -1) //fstat devuelve informacion del fichero
		{
               fprintf(stderr,"\nERROR: no se ha realizado el stat");
        }
	//Se proyecta el archivo a memoria
	mapa = mmap (0, est.st_size, PROT_READ, MAP_SHARED, fd, 0);  //Proyecta un mapa en la memoria virtual del proceso actual donde se ejecute
	//En caso de que falle la proyeccion
	if (mapa==MAP_FAILED)
		{
		fprintf(stderr,"\nERROR: no se ha proyectado bien a memoria");
		}
	//Va contando los caracteres iguales en el archivo
	for (i = 0; i < est.st_size; i++)
        { 
		if (caracter==mapa[i]) //Cada vez que se encuentra el caracter que buscamos
			{
			caracteres++;
			}
		}
	//Liberamos la memoria que hemos ocupado
    if (munmap (mapa, est.st_size) == -1) //munmap elimina el mapeo de la posicion de memoria especificada
		{
       		fprintf(stderr,"\nERROR: no se ha liberado la memoria");
        }
		return caracteres;
	}
