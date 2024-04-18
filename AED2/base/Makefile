CFLAGS = -Wall -std=c99 -DGRAFO_DIRECIONADO=1

MAT: testa_matriz
LIS: testa_lista

testa_matriz: CFLAGS += -DGRAFO_MATRIZ=1
testa_lista: CFLAGS += -DGRAFO_LISTA=1	

testa_matriz: obj/grafo_matrizadj.o obj/testa_grafo.o
	gcc $(CFLAGS) -o prog_matriz.exe obj/grafo_matrizadj.o obj/testa_grafo.o 

obj/grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc $(CFLAGS) -o obj/grafo_matrizadj.o -c grafo_matrizadj.c



testa_lista: obj/grafo_listaadj.o obj/testa_grafo.o
	gcc $(CFLAGS) -o prog_lista.exe obj/grafo_listaadj.o obj/testa_grafo.o


obj/grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc $(CFLAGS) -o obj/grafo_listaadj.o -c grafo_listaadj.c



obj/testa_grafo.o: testa_grafo.c grafo_matrizadj.h grafo_listaadj.h
	gcc $(CFLAGS) -o obj/testa_grafo.o -c testa_grafo.c

clean:
	del *.o *.exe
	del obj\*.o

