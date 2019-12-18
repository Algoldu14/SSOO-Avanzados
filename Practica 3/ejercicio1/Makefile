.PHONY: clean

all: libcontar.a contar

libcontar.a: leercar_R.o contar_M.o uso.o
	ar rcs -l libcontar.a contar_M.o leercar_R.o uso.o -o 

contar: principal.o 
	gcc -Wall -g principal.o libcontar.a -o contar

principal.o: principal.c
	gcc -c -Wall -o principal.o principal.c

leercar_R.o: leercar_R.c leercar_R.h
	gcc -c -Wall -o leercar_R.o leercar_R.c 

contar_M.o: contar_M.c contar_M.h
	gcc -c -Wall -o contar_M.o contar_M.c

uso.o: uso.h uso.c
	gcc -c -Wall -o uso.o uso.c

clean:
	rm -f *.o
	rm -f contar
	rm -f libcontar.a
