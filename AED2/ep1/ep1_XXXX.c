#ifdef MATRIZ
#include <stdlib.h>
#include <stdio.h>
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif

void lerGrafo(Grafo* grafo, char* arquivo);

int main(int argc, char** argv) {
	if (argc <= 2) {
		fprintf(stderr, "ERR main() -- Argumentos insuficientes.\n");
		return -1;
	}

	char* entrada = argv[1];
	char* saida = argv[2];

	Grafo grafo;
	lerGrafo(&grafo, entrada);

	return 0;
}

void lerGrafo(Grafo* grafo, char* caminho) {
	FILE* arquivo = fopen(caminho, "r");
	if (!arquivo) {
		fprintf(stderr, "ERR lerGrafo() -- Arquivo '%s' não encontrado.\n", caminho);
		exit(-1);	
	}

	// Inicializa o grafo
	int vertices, arestas;
	fscanf(arquivo, "%i %i", &vertices, &arestas);
	inicializaGrafo(grafo, vertices);

	printf("Vértices: %i, Arestas: %i\n", vertices, arestas);

	// Lê as arestas
	for (int i = 0; i < arestas; i++) {
		int origem;
		int destino;
		int peso;
		fscanf(arquivo, "%i %i %i", &origem, &destino, &peso);

		insereAresta(grafo, origem, destino, peso);
	}

	imprimeGrafo(grafo);

	fclose(arquivo);
}