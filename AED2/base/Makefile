MAT: testa_matriz
LIS: testa_lista

testa_matriz: grafo_matrizadj.o testa_grafo.o
	gcc -o testa_grafo_matriz.exe grafo_matrizadj.o testa_grafo.o

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc -c grafo_matrizadj.c

testa_lista: grafo_listaadj.o testa_grafo.o
	gcc -o testa_grafo_lista.exe grafo_listaadj.o testa_grafo.o

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

testa_grafo.o: testa_grafo.c grafo_matrizadj.h grafo_listaadj.h
	gcc -c testa_grafo.c

clean:
	del *.o *.exe


