test.exe: obj/main.o obj/grafo_matrizadj.o
	gcc obj/main.o obj/grafo_matrizadj.o -o test.exe
	
obj/grafo_matrizadj.o: grafo_matrizadj.h grafo_matrizadj.c
	gcc -c grafo_matrizadj.c -o obj/grafo_matrizadj.o

obj/main.o: main.c grafo_matrizadj.h
	gcc -c main.c -o obj/main.o
