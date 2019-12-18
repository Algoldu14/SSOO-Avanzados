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
void mimkdir(orden *O)
	{
	//Se usa la llamada mkdir y se asignan permisos USUARIO: rwx | GRUPO: rwx | OTROS: r--
	if (mkdir(O->argv[1],S_IRWXU|S_IRWXG|S_IROTH)==-1) 
		{
		fprintf(stderr,"ERROR No se ha podido crear el directorio");
		}
	}
