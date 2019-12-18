
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include "parser.h"

//PARTE OPCIONAL mils -l
void milsl(orden *O)
{
	DIR *dir;
	struct passwd *usuario;
	struct group *grupo;
	struct dirent *ent;
	struct stat est;

	if ((O->argv[1] == NULL)||((dir = opendir (O->argv[1]))==NULL)) { //Igual que en ls 
 		
		dir = opendir (".");
  	} 
	if (stat (".", &est) == -1) 
	{
        	fprintf(stderr,"\nERROR: no se ha realizado el stat");
        }
	if ((usuario=getpwuid(est.st_uid))==NULL)
	{
               fprintf(stderr,"\nERROR: no se ha encontrado usuario");
        }
	if ((grupo=getgrgid(est.st_gid))==NULL)
	{
               fprintf(stderr,"\nERROR: no se ha encontrado grupo");
        }
	while ((ent = readdir (dir)) != NULL)
	{
		if (stat (ent->d_name, &est) == -1) 
		{
               fprintf(stderr,"\nERROR: no se ha realizado el stat");
        }
    	printf ("%14s\t%s\t%s \t%ld\t", ent->d_name,usuario->pw_name,grupo->gr_name,est.st_size);

        switch (est.st_mode & S_IFMT) 
	{
        case S_IFBLK:   printf("dispositivo modo bloque ");      break;
        case S_IFCHR:   printf("dispositivo modo caracter ");    break;
        case S_IFDIR:   printf("directorio ");               	 break;
        case S_IFIFO:   printf("tuberia ");                      break;
        case S_IFLNK:   printf("enlace simbolico ");             break;
        case S_IFREG:   printf("archivo regular ");              break;
        case S_IFSOCK:  printf("socket ");                       break;
        default:        printf("desconocido ");                  break;
	}

	//Dependiendo de los privilegios de USUARIO , GRUPO , OTROS
        printf( (S_ISDIR(est.st_mode)) ? "d" : "-");
    	printf( (est.st_mode & S_IRUSR) ? "r" : "-"); 
    	printf( (est.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (est.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (est.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (est.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (est.st_mode & S_IXGRP) ? "x" : "-");
    	printf( (est.st_mode & S_IROTH) ? "r" : "-");
    	printf( (est.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (est.st_mode & S_IXOTH) ? "x" : "-");
        printf("\t%s\n",ctime(&est.st_mtime));
 	}
  	closedir (dir);
}

