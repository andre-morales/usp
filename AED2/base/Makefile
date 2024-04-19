CFLAGS = -Wall -std=c99 -DGRAFO_DIRECIONADO=1

MAT: testa_matriz
LIS: testa_lista

testa_matriz: CFLAGS += -DGRAFO_MATRIZ=1
testa_lista: CFLAGS += -DGRAFO_LISTA=1	

ALG_OBJECTS = obj/le_grafo.o obj/busca_profundidade.o obj/ciclico.o

testa_matriz: obj/grafo_matrizadj.o obj/testa_grafo.o $(ALG_OBJECTS)
	gcc $(CFLAGS) -o prog_matriz.exe obj/grafo_matrizadj.o obj/testa_grafo.o $(ALG_OBJECTS)

testa_lista: obj/grafo_listaadj.o obj/testa_grafo.o $(ALG_OBJECTS)
	gcc $(CFLAGS) -o prog_lista.exe obj/grafo_listaadj.o obj/testa_grafo.o $(ALG_OBJECTS)

obj/grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc $(CFLAGS) -o obj/grafo_matrizadj.o -c grafo_matrizadj.c

obj/grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc $(CFLAGS) -o obj/grafo_listaadj.o -c grafo_listaadj.c

obj/le_grafo.o: alg/le_grafo.c alg/le_grafo.h
	gcc $(CFLAGS) -o obj/le_grafo.o -c alg/le_grafo.c

obj/busca_profundidade.o: alg/busca_profundidade.c alg/busca_profundidade.h
	gcc $(CFLAGS) -o obj/busca_profundidade.o -c alg/busca_profundidade.c

obj/ciclico.o: alg/ciclico.c alg/ciclico.h
	gcc $(CFLAGS) -o obj/ciclico.o -c alg/ciclico.c

obj/testa_grafo.o: testa_grafo.c grafo_matrizadj.h grafo_listaadj.h
	gcc $(CFLAGS) -o obj/testa_grafo.o -c testa_grafo.c

clean:
	del *.o *.exe
	del obj\*.o

