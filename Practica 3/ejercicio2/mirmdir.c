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
void mirmdir(orden *O)
{
	//Usamos la llamada al sistema para eliminar el directorio
	if (rmdir(O->argv[1])==-1)
	{
		fprintf(stderr,"ERROR No se ha podido eliminar el directorio");
	}
}
