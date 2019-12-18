#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "leercar_R.h"
#include "contar_M.h"
#include "uso.h"

int main (int argc, char *argv[])
{
	int num=0;
	char caracter='0';
	int fd=0;
	int i=0;
	int tam=0;
	//Comprobamos que se introduzcan bien los argumentos
	if (argc !=4 && (*argv[1] =! 'H'))
		{
		fprintf(stderr,"\n ERROR: faltan o sobran parametros(modo, archivo, caracter)\n");
		exit(1);
		}
	else
	{
		//Realizamos el open al archivo
		if ((fd=open(argv[2],O_RDONLY,0640))==-1 && (*argv[1] =! 'H'))
			{
			fprintf(stderr,"\nERROR: no se puede abrir el archivo\n");
			exit(1);
			}
		else {
			//Elige el metodo para contar caracteres en el archivo
			if (toupper(*argv[1])=='R')
				{
				//Obtenemos el tamaño del descriptor dado usando lseek	
				tam = lseek(fd,0,SEEK_END)-1;
				//Se repite la lectura de caracteres hasta acabar con todos los caracteres
				while (tam>i)
					{
					caracter=LeerCaracter(fd,i);
					if (caracter==*argv[3])	//si el caracter que buscamos se sencuentra	
						num++;
					i++;
					}
				//Una vez acabado, cerramos el archivo
				if (close(fd)==-1)
					{	
					fprintf(stderr,"\n	ERROR: no se ha cerrado\n");
					exit(1);
					}
				printf("La letra %c aparece %d veces\n",*argv[3],num);
				}
			else if (toupper(*argv[1]) == 'M')
				{
				//La funcion ya devuelve el total de veces que se ha encontrado el caracter por lo que no hace falta mas
				num=ContarCaracteres(fd,*argv[3]);
				printf("La letra %c aparece %d veces\n",*argv[3],num);
				}
			else if (toupper(*argv[1]) == 'H')
				{
				//La funcion imprime el modo de uso
				imprimeUSO ();
				}
			else 
				{
				fprintf(stderr,"\nERROR: El modo esta mal introducido\n");
				exit(1);
				}
			}
		}
}
