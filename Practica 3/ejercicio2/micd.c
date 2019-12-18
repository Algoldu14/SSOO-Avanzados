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
void micd(orden *O)
	{
	//Se comprueba que escriba la ruta sino se pone la actual
	if (O->argv[1]==NULL)
		{ 
		O->argv[1]=".";
		}
	//Usamos la llamada para cambiar de directorio chdir
	if (chdir(O->argv[1])==-1)
		{
		fprintf(stderr,"ERROR No se ha podido cambiar de directorio");
		}
	}
