CFLAGS = -Wall -std=c99 -DGRAFO_DIRECIONADO=0 -I.

ALG_OBJECTS = obj/alg/vertices_articulacao.o obj/alg/le_grafo.o obj/alg/lista.o obj/alg/heap.o obj/alg/prim.o obj/alg/dijkstra.o obj/alg/union_find.o obj/alg/componentes_conexos.o obj/alg/busca.o obj/alg/busca_profundidade.o obj/alg/grafo_ciclico.o obj/alg/ordenacao_topologica.o obj/alg/fila.o obj/alg/busca_largura.o obj/alg/caminho_curto.o

MAT: testa_matriz
LIS: testa_lista

testa_matriz: CFLAGS += -DGRAFO_MATRIZ=1
testa_lista: CFLAGS += -DGRAFO_LISTA=1

testa_matriz: obj/grafo_matrizadj.o obj/testa_grafo.o $(ALG_OBJECTS)
	gcc $(CFLAGS) -o prog_matriz.exe obj/grafo_matrizadj.o obj/testa_grafo.o $(ALG_OBJECTS)

testa_lista: obj/grafo_listaadj.o obj/testa_grafo.o $(ALG_OBJECTS)
	gcc $(CFLAGS) -o prog_lista.exe obj/grafo_listaadj.o obj/testa_grafo.o $(ALG_OBJECTS)

obj/grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc $(CFLAGS) -o obj/grafo_matrizadj.o -c grafo_matrizadj.c

obj/grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc $(CFLAGS) -o obj/grafo_listaadj.o -c grafo_listaadj.c

obj/testa_grafo.o: testa_grafo.c grafo_matrizadj.h grafo_listaadj.h
	gcc $(CFLAGS) -o obj/testa_grafo.o -c testa_grafo.c

obj/alg/%.o: alg/%.c alg/%.h
	gcc $(CFLAGS) -o $@ -c $<

clean:
	del *.o *.exe
	del obj\*.o
	del obj\alg\*.o

