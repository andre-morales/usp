MAT: testa_matriz
LIS: testa_lista

testa_matriz: grafo_matrizadj.o testa_grafo.o
	gcc -o testa_grafo_matriz.exe grafo_matrizadj.o testa_grafo.o

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc -c grafo_matrizadj.c

testa_grafo.o: testa_grafo.c grafo_matrizadj.h
	gcc -c testa_grafo.c

clean:
	del *.o *.exe


