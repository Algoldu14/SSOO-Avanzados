/*
    experimento_mem.c
*/

#include <stdio.h>         // Declaración de printf() (y más)
#include "mem_dinamica.h"  // Declaraciones de mem_dinamica.c

// Declaración de otras funciones:

void hola (void);    // No recibe nada y no devuelve nada
void cadenas (void); //  "
int tres (void);     // No recibe nada y devuelve un entero
int factorial (int); // Recibe un entero y devuelve otro

// Declaración (Y DEFINICIÓN) de otra función:

int triple (int x)
{
    printf ("Función triple(): %p\n"  // %p: puntero
            "\tValor de x: %d\n"      // %d: int (en decimal)
            "\tDirección de x: %p",   // %p: otro puntero
            &triple, x, &x);          // <--- Valores a mostrar

    return 3 * x;
}

// Declaración (y def.) de algunas variables globales:

int a=34;
int b;
int c=-5;

float d;  // d y D no tienen nada que ver
int D;    // (el lenguaje C es sensible a las mayúsculas)

// Función principal del programa:

int main (int argc, char * argv[])
{
    // Variables locales:
    int x=3, y;

    hola ();

    printf ("Función printf(): %p\n", &printf);
    printf ("\nFunción main(): %p\n", &main);

    printf ("\n\tVariables globales (dir., nombre, valor):\n");
    printf ("\t\t%p  a  %d\n", &a, a);
    printf ("\t\t%p  b  %d\n", &b, b);
    printf ("\t\t%p  c  %d\n", &c, c);
    printf ("\t\t%p  d  %f\n", &d, d);  // %f: float
    printf ("\t\t%p  D  %d\n", &D, D);
    printf ("\t\t%p  k  %d\n", &k, k);  // variable del otro .c

    printf ("\n\tVariables locales (dir., nombre, valor):\n");
    printf ("\t\t%p  x  %d\n", &x, x);
    printf ("\t\t%p  y  %d\n", &y, y);

    printf ("\n\tCalculando 3! ...\n");
    x = factorial (tres());
    printf ("\t3! == %d\n", x);

    mem_dinamica ();    // función del otro .c

    cadenas ();

    return 0;           // 0 == todo ha ido bien
}

// Definición de las funciones restantes:

void hola (void)
{
    printf ("¡Hola mundo!\n");
}

int tres (void)
{
    return 3;
}

int factorial (int n)
{
    int f;

    printf ("\tFunción factorial(%d): %p\n", n, &factorial);
    printf ("\t\tParámetro n (dir., valor): %p  %d\n", &n, n);
    printf ("\t\tVariable f (dir., valor):  %p  %d\n", &f, f);

    f = n<2 ? 1 : n*factorial(n-1);

    /*
        Por si no resulta obvio, la línea anterior equivale a:

            if (n<2)
                f = 1;
            else
                f = n * factorial (n-1);
    */

    printf ("\t\tfactorial(%d) devolviendo %d\n", n, f);

    return f;
}

void cadenas (void)
{
    // Estos dos arrays son igual de grandes y
    // contienen exactamente lo mismo:
    char a[] = "hola";
    char b[] = { 'h', 'o', 'l', 'a', '\0' };

    /*
        En Pascal, las cadenas contienen un entero que indica
        su longitud. En C, sin embargo, no se almacena el
        número de caracteres, sino que se señaliza el final de
        la cadena con un caracter especial: '\0', que es lo
        mismo que 0 (en binario: 00000000), y que no debe ser
        confundido con el '0' (en binario: 00110000)
    */

    // Esto no es un array, sino un puntero:
    char * c = "hasta luego";

    /*
        En este momento, el puntero c está apuntando a una
        cadena literal (constante, que se puede leer, pero
        no escribir). Una instrucción como *c='H' provocaría
        un error en tiempo de ejecución.
    */

    printf ("\n\tFunción cadenas(): %p\n", &cadenas);
    printf ("\t\ta: %p  \"%s\"\n", a, a);
    printf ("\t\tb: %p  \"%s\"\n", b, b);
    printf ("\t\tc: %p  \"%s\"\n", c, c);
    printf ("\t\t&c: %p\n", &c);

    printf ("\t\tJugando un poco con c...\n");

    c = a;     // Ahora c apuntará al comienzo del array a
    *c = 'H';  // Ya sí se puede modificar *c porque ahora c
               // apunta a una zona de memoria en la que se
               // puede escribir

    /*
        Nótese que no hemos necesitado escribir &a para
        obtener la dirección del array a. Esto se debe a una
        importante excepción en la sintaxis del lenguaje.
        Normalmente, el nombre de una variable, sin más,
        arroja el valor de la variable en la expresión en que
        se usa. Con los arrays, sin embargo, el nombre suelto
        da la dirección de comienzo del array.

        Muchos compiladores aceptan &a, pero la forma más
        correcta es simplemente a.

        Lo mismo ocurre con la dirección de las funciones. El
        nombre suelto, sin los paréntesis, da la dirección de
        comienzo. A lo largo de todo este programa se ha usado
        el &, pero no es necesario para obtener la dirección
        de una función.
    */

    printf ("\t\ta: %p  \"%s\"\n", a, a);
    printf ("\t\tb: %p  \"%s\"\n", b, b);
    printf ("\t\tc: %p  \"%s\"\n", c, c);
    printf ("\t\t&c: %p\n", &c);
}
