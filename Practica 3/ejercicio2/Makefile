.PHONY: clean

microshell: prueba.o parser.o mipwd.o mils.o milsl.o micd.o mirm.o micp.o micat.o mimkdir.o mirmdir.o
	gcc -Wall -g -o microshell prueba.o parser.o mipwd.o mils.o milsl.o micd.o mirm.o micp.o micat.o mimkdir.o mirmdir.o

prueba.o: prueba.c
	gcc -Wall -c prueba.c

parser.o: parser.c parser.h
	gcc -Wall -c parser.c

mipwd.o:mipwd.c mipwd.h
	gcc -Wall -c mipwd.c

mils.o:mils.c mils.h
	gcc -Wall -c mils.c

milsl.o:milsl.c milsl.h
	gcc -Wall -c milsl.c

micd.o:micd.c micd.h
	gcc -Wall -c micd.c

mirm.o:mirm.c mirm.h
	gcc -Wall -c mirm.c

micp.o:micp.c micp.h
	gcc -Wall -c micp.c

micat.o:micat.c micat.h
	gcc -Wall -c micat.c

mimkdir.o: mimkdir.c mimkdir.h
	gcc -Wall -c mimkdir.c

mirmdir.o:mirmdir.c mirmdir.h
	gcc -Wall -c mirmdir.c

clean:
	rm -f *.o
	rm -f microshell
