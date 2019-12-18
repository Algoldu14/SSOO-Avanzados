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
void mirm(orden *O)
{
	//Usamos la llamada al sistema para "eliminar" el archivo con unlink
	if (unlink(O->argv[1])==-1)
	{
		fprintf(stderr,"ERROR No se ha podido eliminar");
	}
}
