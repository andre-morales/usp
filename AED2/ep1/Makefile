CFLAGS = -Wall -std=c99

USP = ${usp}

ep1_matriz: grafo_matrizadj.o ep1_XXXX.o
	gcc $(CFLAGS) -o ep1_matriz.exe grafo_matrizadj.o ep1_XXXX.o

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc $(CFLAGS) -c grafo_matrizadj.c

clean:
	rm -f *.o *.exe



ep1_lista: grafo_listaadj.o ep1_XXXX.o
	gcc $(CFLAGS) -o ep1_lista.exe grafo_listaadj.o ep1_XXXX.o


grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc $(CFLAGS) -c  grafo_listaadj.c 

ep1_XXXX.o: ep1_XXXX.c grafo_matrizadj.h  grafo_listaadj.h
	gcc $(CFLAGS) -c  ep1_XXXX.c 
