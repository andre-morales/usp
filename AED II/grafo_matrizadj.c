#include "grafo_matrizadj.h"
#include <stdio.h>

bool inicializaGrafo(Grafo* g, int v) {
	// Teste de sanidade
	if (v <= 0 || v > MAXNUMVERTICES) {
		fprintf(stderr, "Inicialização do Grafo falhou:\n");
		fprintf(stderr, "  O número de vértices especificado [%i] está fora do limite permitido. 0 < v < %i\n", v, MAXNUMVERTICES);
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

void imprimeGrafo(Grafo* g) {
	for (int y = 0; y < g->numVertices; y++) {
		for (int x = 0; x < g->numVertices; x++) {
			printf("%*i ", 2, g->mat[y][x]);
		}	
		printf("\n");
	}
}

bool verificaValidadeVertice(int v, Grafo* g) {
	if (v < 0 || v >= g->numVertices) {
		fprintf(stderr, "Vértice [%i] ilegal: 0 <= v < %i\n", v, g->numVertices);
		return false;
	}
	return true;
}

void insereAresta(int v1, int v2, Peso w, Grafo* g) {
	if (!verificaValidadeVertice(v1, g) || !verificaValidadeVertice(v2, g)) return;

	g->mat[v1][v2] = w;
	g->numArestas++;
}

Peso obtemPesoAresta(int v1, int v2, Grafo* g) {
	if (!verificaValidadeVertice(v1, g) || !verificaValidadeVertice(v2, g)) return AN;

	return g->mat[v1][v2];
}

bool existeAresta(int v1, int v2, Grafo* g) {
	int w = obtemPesoAresta(v1, v2, g);
	return w != AN;
}

bool removeAresta(int v1, int v2, Peso* outWeight, Grafo* g) {
	if (!verificaValidadeVertice(v1, g) || !verificaValidadeVertice(v2, g)) return false;

	Peso w = g->mat[v1][v2];

	// Aresta inexistente
	if (w == AN) return false;

	if (outWeight) *outWeight = w;

	g->mat[v1][v2] = AN;
	g->numArestas--;
	return true;
}

bool listaAdjVazia(int v, Grafo* g) {
	if (!verificaValidadeVertice(v, g)) return false;

	for (int i = 0; i < g->numVertices; i++) {
		if (g->mat[v][i] != AN) return false;
	}

	return false;
}

void liberaGrafo(Grafo* g) {}