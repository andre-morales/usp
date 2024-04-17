#include <stdio.h>
#include "grafo_listaadj.h"

void pause();

void main() {
	Grafo g;
	inicializaGrafo(&g, 10);

	insereAresta(&g, 1, 2, 1);
	insereAresta(&g, 1, 3, 1);
	insereAresta(&g, 1, 7, 1);
	insereAresta(&g, 1, 9, 1);

	printf("Adjacentes de V: ");
	int V = 1;

	/*
	Apontador vert = VERTICE_INVALIDO;
	while(true) {
		vert = proxListaAdj(&g, V, vert);
		if (vert == VERTICE_INVALIDO) break;
		
		printf("%i ", vert);
		//pause();
	}
	printf("\n");	*/

	Apontador aresta = primeiroListaAdj(&g, V);
	while(true) {
		if (aresta == VERTICE_INVALIDO) break;
		
		printf("%i ", aresta->vdest);
		aresta = proxListaAdj(&g, V, aresta);
		
		//pause();
	}
	printf("\n");

	imprimeGrafo(&g);
}

void pause() {
	getchar();
}