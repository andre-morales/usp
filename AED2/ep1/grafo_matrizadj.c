#include "grafo_matrizadj.h"
#include <stdio.h>

bool inicializaGrafo(Grafo* g, int v) {
	// Testes de sanidade
	if (g == NULL) {
		fprintf(stderr, "ERR inicializaGrafo() -- Grafo não pode ser nulo.\n");
		return false;
	}
	if (v <= 0 || v > MAXNUMVERTICES) {
		fprintf(stderr, "ERR inicializaGrafo()\n");
		fprintf(stderr, "-- O número de vértices especificado [%i] está fora do limite permitido. 0 < v < %i\n", v, MAXNUMVERTICES);
		return false;
	}

	g->numVertices = v;
	g->numArestas = 0;

	for (int y = 0; y < v; y++) {
		for (int x = 0; x < v; x++) {
			g->mat[y][x] = AN;
		}
	}

	return true;
}

bool verificaValidadeVertice(Grafo* g, int v) {
	if (v < 0 || v >= g->numVertices) {
		fprintf(stderr, "Vértice [%i] ilegal: 0 <= v < %i\n", v, g->numVertices);
		return false;
	}
	return true;
}

void insereAresta(Grafo* g, int v1, int v2, Peso w) {
	if (!verificaValidadeVertice(g, v1) || !verificaValidadeVertice(g, v2)) return;

	printf("A: %i, B: %i, W: %i\n", v1, v2, w);

	g->mat[v1][v2] = w;
	g->mat[v2][v1] = w;
	g->numArestas++;
}

void imprimeGrafo(Grafo* g) {
	// Print header
	printf("    ");
	for (int x = 0; x < g->numVertices; x++) {
		printf("%i ", x);
	}
	printf("\n");

	for (int y = 0; y < g->numVertices; y++) {
		printf("%i | ", y);
		for (int x = 0; x < g->numVertices; x++) {
			int a = g->mat[y][x];
			if (a == AN) {
				printf(". ");
			} else {
				printf("%*i ", 1, a);
			}
		}	
		printf("\n");
	}
}