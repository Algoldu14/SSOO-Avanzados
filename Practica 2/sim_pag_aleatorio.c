/*
    sim_pag_aleatorio.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sim_paginacion.h"

// Función que inicia las tablas

void iniciar_tablas (ssistema * S)
{
    int i;

    // Páginas a cero
    memset (S->tdp, 0, sizeof(spagina)*S->numpags);

    // Pila LRU vacía
    S->lru = -1;

    // Tiempo LRU(t) a cero
    S->reloj = 0;

    // Lista circular de marcos libres
    for (i=0; i<S->nummarcos-1; i++)
    {
        S->tdm[i].pagina = -1;
        S->tdm[i].sig = i+1;
    }

    S->tdm[i].pagina = -1;  // Ahora i == nummarcos-1
    S->tdm[i].sig = 0;      // Cerrar lista circular
    S->listalibres = i;     // Apuntar al último

    // Lista circular de marcos ocupados vacía
    S->listaocupados = -1;
}

// Funciones que simulan el hardware de la MMU

unsigned sim_mmu (ssistema * S, unsigned dir_virtual, char op)
{
    unsigned dir_fisica;
    int pagina, marco, desplazamiento;

    // TODO: Teclear código que simula el funcionamiento de la MMU
    //       (hardware) en respuesta a una operación de acceso a
    //       memoria
    pagina = dir_virtual / S->tampag; //Cociente
    desplazamiento = dir_virtual % S->tampag; //Resto
    if(pagina<0 || pagina>=S->numpags)//Comprueba que el acceso sea legal
    {
    	S->numrefsilegales++;
	return ~0U;	//Devolver dir.fisica FF...F
    }
    if(!S->tdp[pagina].presente)//la pagina no esta presente
	tratar_fallo_de_pagina(S,dir_virtual);
    //Ahora ya esta presente
    marco=S->tdp[pagina].marco;
    dir_fisica=marco*S->tampag+desplazamiento;
    referenciar_pagina(S, pagina, op);
    if(S->detallado)
	printf("\t %c %u == P %d(M %d)+ %d\n",op,dir_virtual,pagina,marco,desplazamiento);
    return dir_fisica;
}

void referenciar_pagina (ssistema * S, int pagina, char op)
{
    if (op=='L')                         // Si es una lectura,
        S->numrefslectura ++;            // contarla
    else if (op=='E')
    {                                    // Si es una escritura,
        S->tdp[pagina].modificada = 1;   // contarla y marcar la
        S->numrefsescritura ++;          // página como modificada
    }
}

// Funciones que simulan el sistema operativo

void tratar_fallo_de_pagina (ssistema * S, unsigned dir_virtual)
{
    int pagina, victima, marco, ult;

    // TODO: Teclear código que simula la respuesta del Sistema
    //       Operativo a un trap de fallo de página provocado
    S->numfallospag ++;
    pagina=dir_virtual/S->tampag;
    if(S->detallado)
	printf("@ !FALLO DE PÁGINA en P %d !\n",pagina);
    if(S->listalibres!=-1) //Si hay marcos libres:
    {
	ult=S->listalibres; //Ultimo de la lista
        marco=S->tdm[ult].sig; //Tomar el sig.(el primero)
        if (marco==ult)		//Si son el mismo es que solo quedaba uno libre
     	   S->listalibres=-1;
        else
	    S->tdm[ult].sig=S->tdm[marco].sig; //Si no puenteamos

        ocupar_marco_libre(S, marco, pagina);
    }
    else //Si no hay marcos libres:
    {
      victima=elegir_pagina_para_reemplazo(S);
      reemplazar_pagina(S,victima,pagina);
    }
}

static unsigned aleatorio (unsigned desde,       // <<--- aleatorio
                           unsigned tam)
{
    unsigned n;

    n = desde + (unsigned)(rand()/(RAND_MAX+1.0)*tam);

    if (n>desde+tam-1)      // Estas comprobaciones no
        n = desde+tam-1;    // deberían ser necesarias,
    else if (n<desde)       // pero es mejor no fiarse
        n = desde;          // mucho de las operaciones
                            // en coma flotante
    return n;
}

int elegir_pagina_para_reemplazo (ssistema * S)
{
    int marco, victima;

    marco = aleatorio (0, S->nummarcos);         // <<--- aleatorio

    victima = S->tdm[marco].pagina;

    if (S->detallado)
        printf ("@ Eligiendo (al azar) P%d de M%d para "
                "reemplazarla\n", victima, marco);

    return victima;
}

void reemplazar_pagina (ssistema * S, int victima, int nueva)
{
    int marco;

    marco = S->tdp[victima].marco;

    if (S->tdp[victima].modificada)
    {
        if (S->detallado)
            printf ("@ Volcando P%d modificada a disco para "
                    "reemplazarla\n", victima);

        S->numescrpag ++;
    }

    if (S->detallado)
        printf ("@ Reemplazando víctima P%d por P%d en M%d\n",
                victima, nueva, marco);

    S->tdp[victima].presente = 0;

    S->tdp[nueva].presente = 1;
    S->tdp[nueva].marco = marco;
    S->tdp[nueva].modificada = 0;

    S->tdm[marco].pagina = nueva;
}

void ocupar_marco_libre (ssistema * S, int marco, int pagina)
{
    if (S->detallado)
        printf ("@ Alojando P%d en M%d\n", pagina, marco);

    // TODO: Escribir el código que enlaza la página con el marco
    //       y viceversa, y pone los valores oportunos en los bits
    //       de estado de la página (presencia...)
    S->tdm[marco].pagina=pagina;
    S->tdp[pagina].marco=marco;
    S->tdp[pagina].presente=1;
    S->tdp[pagina].modificada=0;
    S->tdp[pagina].referenciada=1;
    
}

// Funciones que muestran resultados

void mostrar_tabla_de_paginas (ssistema * S)
{
    int p;

    printf ("%10s %10s %10s   %s\n",
            "PÁGINA", "Presente", "Marco", "Modificada");

    for (p=0; p<S->numpags; p++)
        if (S->tdp[p].presente)
            printf ("%8d   %6d     %8d   %6d\n", p,
                    S->tdp[p].presente, S->tdp[p].marco,
                    S->tdp[p].modificada);
        else
            printf ("%8d   %6d     %8s   %6s\n", p,
                    S->tdp[p].presente, "-", "-");
}

void mostrar_tabla_de_marcos (ssistema * S)
{
    int p, m;

    printf ("%10s %10s %10s   %s\n",
            "MARCO", "Página", "Presente", "Modificada");

    for (m=0; m<S->nummarcos; m++)
    {
        p = S->tdm[m].pagina;

        if (p==-1)
            printf ("%8d   %8s   %6s     %6s\n", m, "-", "-", "-");
        else if (S->tdp[p].presente)
            printf ("%8d   %8d   %6d     %6d\n", m, p,
                    S->tdp[p].presente, S->tdp[p].modificada);
        else
            printf ("%8d   %8d   %6d     %6s   ¡ERROR!\n", m, p,
                    S->tdp[p].presente, "-");
    }
}

void mostrar_informe_reemplazo (ssistema * S)
{
    printf ("Reemplazo aleatorio "
            "(no hay info. específica)\n");      // <<--- aleatorio
}


