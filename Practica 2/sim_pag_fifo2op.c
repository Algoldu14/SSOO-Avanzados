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
    if (op=='E')
    {                                    // Si es una escritura,
        S->tdp[pagina].modificada = 1;   // contarla y marcar la
        S->numrefsescritura ++;          // página como modificada
    }
   S->tdp[pagina].referenciada=1;	 //Bit de referencia a 1
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



int elegir_pagina_para_reemplazo (ssistema * S)
{
    int marco, victima,ultimo;
    int noEncontrado=-1;
     while(noEncontrado==-1)
	{
		ultimo=S->listaocupados;	//ultimo marco de la lista ocupados
		marco=S->tdm[ultimo].sig;	//Cogemos el primer marco
		victima=S->tdm[marco].pagina;	//Almacenamos la pagina de ese marco en la victima
		if(S->tdp[victima].referenciada==0)	//Si el bit de referencia es 0, sustituimos
		{
			noEncontrado=victima;
		}
		else
		{
		S->tdp[victima].referenciada=0;		//Si no, ponemos el bit de referencia a 0
		}
		
	S->listaocupados=marco;		//El primer marco pasa a ser el ultimo marco de la lista ocupados
	}
    if (S->detallado)
        printf ("@ Eligiendo (al azar) P%d de M%d para "
                "reemplazarla\n", victima, marco);

    return noEncontrado;
}

void reemplazar_pagina (ssistema * S, int victima, int nueva)
{
    int marco;

    marco = S->tdp[victima].marco;		//Marco de la victima, lo almacenamos en marco

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
    S->tdp[nueva].referenciada=1;
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

    int primero,ultimo;
    ultimo=S->listaocupados;//Lista ocupados nos da el ultimo marco de la listaocupados.
    primero=S->tdm[ultimo].sig;//Ultimo siempre apunta a primero, el siguiente de ultimo siempre es el primero, dibujo de la práctica.
    S->tdm[marco].sig=primero;//AL introducir el marco debemos hacer que apunte al primero.
    S->tdm[ultimo].sig=marco;//EL ultimo debe apuntar al nuevo marco introducido.
    S->listaocupados=marco;//El primer marco, pasa a ser el último marco de la lista ocupados.
}

// Funciones que muestran resultados

void mostrar_tabla_de_paginas (ssistema * S)
{
    int p;

    printf ("%10s %10s %10s  %10s  %s\n",
            "PÁGINA", "Presente", "Marco", "Modificada","Referenciada");

    for (p=0; p<S->numpags; p++)
        if (S->tdp[p].presente)
            printf ("%8d   %6d     %8d  %6d  %6d\n", p,
                    S->tdp[p].presente, S->tdp[p].marco,
                    S->tdp[p].modificada,S->tdp[p].referenciada);
        else
            printf ("%8d   %6d     %8s   %6s\n", p,
                    S->tdp[p].presente, "-", "-");
}

void mostrar_tabla_de_marcos (ssistema * S)
{
    int p, m;

    printf ("%10s %10s %10s  %10s %s\n",
            "MARCO", "Página", "Presente", "Modificada","Referenciada");

    for (m=0; m<S->nummarcos; m++)
    {
        p = S->tdm[m].pagina;

        if (p==-1)
            printf ("%8d   %8s   %6s     %6s\n", m, "-", "-", "-");
        else if (S->tdp[p].presente)
            printf ("%8d   %8d   %6d  %6d   %6d\n", m, p,
                    S->tdp[p].presente, S->tdp[p].modificada,S->tdp[p].referenciada);
        else
            printf ("%8d   %8d   %6d     %6s   ¡ERROR!\n", m, p,
                    S->tdp[p].presente, "-");
    }
}

void mostrar_informe_reemplazo (ssistema * S)
{
    int num=0,pagina;
    printf ("Reemplazo Fifo2op \n");
    printf("%6d", S->listaocupados);//Mostramos todas las paginas presentes en el marco con su bit de referencia.
    printf ("%10s %10s %10s  %10s  %s\n",
            "PÁGINA", "Presente", "Marco", "Modificada","Referenciada");
    for(num=0;num<S->nummarcos;num++)
	{
	pagina=S->tdm[num].pagina;
	if (S->tdp[pagina].presente)
            printf ("%8d   %6d     %8d  %6d  %6d\n", pagina,
                    S->tdp[pagina].presente, S->tdp[pagina].marco,
                    S->tdp[pagina].modificada,S->tdp[pagina].referenciada);
        else
            printf ("%8d   %6d     %8s   %6s\n", pagina,
                    S->tdp[pagina].presente, "-", "-");
	}
}


