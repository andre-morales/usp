/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Arquivo de testes para as funções de grafo.
 **/
#include "grafo.h"
#include "alg/busca_profundidade.h"
#include "alg/le_grafo.h"
#include "alg/ciclico.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void printAdjacentes(Grafo*, int);
void pause();

int main() {
	Grafo grafo;
	Grafo* g = &grafo;
	leGrafo(g, "gr3.txt");

	imprimeGrafo(g);

	bool ci = ehGrafoCiclico(g);
	if (ci) {
		printf("ciclico");
	} else {
		printf("nao ciclico");
	}

	liberaGrafo(g);
}

void printAdjacentes(Grafo* g, int V) {
	printf("Adjacentes de V: %i\n", V);

	Apontador aresta = primeiroListaAdj(g, V);
	while(true) {
		if (aresta == VERTICE_INVALIDO) break;
		
		printf("%i ", verticeDestino(aresta));
		aresta = proxListaAdj(g, V, aresta);
	}
	printf("\n");
}

void pause() {
	getchar();
}