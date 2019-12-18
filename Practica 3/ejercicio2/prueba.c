/*
    prueba.c
*/

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
#include "mimkdir.h"
#include "mirmdir.h"
#include "micd.h"
#include "mirm.h"
#include "mils.h"
#include "milsl.h"
#include "mipwd.h"
#include "micat.h"
#include "micp.h"

void mostrar_orden (orden * O);

int main ()
{
    orden O;
    int r;

    printf ("Introduzca órdenes (pulse Ctrl-D para terminar)\n");

    do// Leer órdenes y mostrarlas
    {
        inicializar_orden (&O);

        printf ("MicroShell> ");
        r = leer_orden (&O, stdin);

        if (r < 0)
            fprintf (stderr, "\nError %d: %s\n",
                             -r, mensajes_err[-r]);
        else
            
	if(O.argc > 0)
	{
		mostrar_orden (&O);
	}

        liberar_orden (&O);
    }
    while (r==0);   // Repetir hasta error o EOF

    return 0;
}

void mostrar_orden (orden * O)
{
    int i;
    printf ("\tOrden cruda: \"%s\"\n", O->orden_cruda);
    printf ("\tNúmero de argumentos: %d\n", O->argc);

    for (i=0; i<=O->argc; i++){
        if (O->argv[i] != NULL)
            printf ("\t\targv[%d]: \"%s\"\n", i, O->argv[i]);
        else
            printf ("\t\targv[%d]: NULL\n", i);
	
		
	if (strcmp(O->argv[0],"mipwd")==0)
		{
		mipwd(O);
		}
	if (strcmp(O->argv[0],"mils")==0)
		{
		//En caso de que se quiera la opcion -l
		if ((O->argv[1])&&(strcmp(O->argv[1],"-l")==0))
			milsl(O);
		else mils(O);
		}
	if (strcmp(O->argv[0],"mimkdir")==0)
		{	
		mimkdir(O);
		}
	if (strcmp(O->argv[0],"mirmdir")==0)
		{	
		mirmdir(O);
		}
	if (strcmp(O->argv[0],"micd")==0)
		{	
		micd(O);
		}
	if (strcmp(O->argv[0],"micat")==0)
		{	
		micat(O);
		}
	if (strcmp(O->argv[0],"micp")==0)
		{	
		micp(O);
		}
	if (strcmp(O->argv[0],"mirm")==0)
		{	
		mirm(O);
		}
	//Cierra el programa
	if (strcmp(O->argv[0],"exit")==0 || strcmp(O->argv[0],"quit")==0)
		{	
		exit(1);
		}
	

    if (O->entrada)
        printf ("\tEntrada: \"%s\"\n", O->entrada);

    if (O->salida)
        printf ("\tSalida: \"%s\"\n", O->salida);

    if (O->salida_err)
        printf ("\tSalida de err.: \"%s\"\n", O->salida_err);

    printf ("\tEjecutar en segundo plano: %s\n",
            O->segundo_plano ? "Sí" : "No");
	}
}





