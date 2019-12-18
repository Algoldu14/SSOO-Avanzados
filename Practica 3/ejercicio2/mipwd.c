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
void mipwd(orden *O)
{
	//Obtenemos el valor maximo de PATH del sistema
	char buf[PATH_MAX];
	//Imprimimos el PATH
	if (getcwd(buf,sizeof(buf))!=NULL)  //getcwd devuelve una cadena string que contiene la ruta absoluta desde donde se llama    
	{                                
		printf("%s\n",buf);
	}

	else { fprintf(stderr,"ERROR No se ha podido obtener el directorio actual"); }
		
}
