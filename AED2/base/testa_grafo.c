#include <stdio.h>
#include "grafo_listaadj.h"

void pause();

void printAdjacentes(Grafo* g, int V);

void main() {
	Grafo g;
	inicializaGrafo(&g, 10);

	insereAresta(&g, 1, 2, 0);
	insereAresta(&g, 1, 3, 0);
	insereAresta(&g, 1, 7, 0);
	insereAresta(&g, 1, 9, 0);

	//printAdjacentes(&g, 1);

	imprimeGrafo(&g);

	removeAresta(&g, 1, 3, NULL);

	imprimeGrafo(&g);

	liberaGrafo(&g);
}

void printAdjacentes(Grafo* g, int V) {
	printf("Adjacentes de V: ");

	Apontador aresta = primeiroListaAdj(g, V);
	while(true) {
		if (aresta == VERTICE_INVALIDO) break;
		
		printf("%i ", apontadorVertice(aresta));
		aresta = proxListaAdj(g, V, aresta);
	}
	printf("\n");
}

void pause() {
	getchar();
}