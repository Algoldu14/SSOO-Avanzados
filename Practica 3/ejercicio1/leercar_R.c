#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
char LeerCaracter (int fd, int posicion)
{
	//Solo vamos a necesitar un caracter
	char c;
	//Apuntamos a la primera posicion antes de leer covn la funcion lseek
	lseek (fd, posicion, SEEK_SET); // Devuelve la ubicación de desplazamiento resultante medida en bytes desde el comienzo del archivo
	//Se lee el caracter
	read (fd, &c, sizeof(char)); //Intenta leer el caracter del descriptor dado fd
	return c;
}
