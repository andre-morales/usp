#include "grafo_listaadj.h"
#include <stdlib.h>
#include <stdio.h>

bool inicializaGrafo(Grafo* grafo, int nv) {
	if (g == NULL) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Grafo não pode ser nulo.\n");
		return false;
	}
	if (nv <= 0) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Vértices tem de ser positivos.\n");
		return false;
	}

	grafo->numArestas = 0;
	grafo->numVertices = nv;
	grafo->listaAdj = (Aresta**)calloc(nv, sizeof(Aresta*));
	if (!grafo->listaAdj) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Alocação falhou.\n");
		return false;
	}
	return true;
}

bool listaAdjVazia(int v, Grafo* gr) {
	if (v >= g->numVertices) {
		fprintf(stderr, "ERR: listaAdjVazia() -- Bad vertex.\n");
		return false;
	}

	Aresta* lista = g->listaAdj[v];
	return !lista;
}