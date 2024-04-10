#include "grafo_listaadj.h"
#include <stdlib.h>
#include <stdio.h>

bool inicializaGrafo(Grafo* grafo, int nv) {
	if (grafo == NULL) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Grafo não pode ser nulo.\n");
		return false;
	}
	if (nv <= 0) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Vértices tem de ser positivos.\n");
		return false;
	}

	grafo->numArestas = 0;
	grafo->numVertices = nv;
	grafo->listaAdj = (Apontador*)calloc(nv, sizeof(Apontador));
	if (!grafo->listaAdj) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Alocação falhou.\n");
		return false;
	}
	return true;
}

void imprimeGrafo(Grafo* g) {
	
}

bool listaAdjVazia(Grafo* gr, int v) {
	if (v >= gr->numVertices) {
		fprintf(stderr, "ERR: listaAdjVazia() -- Bad vertex.\n");
		return false;
	}

	Aresta* lista = gr->listaAdj[v];
	return !lista;
}

Apontador proxListaAdj(Grafo*, int v, Apontador atual) {
	if (atual == NULL) {
		return VERTICE_INVALIDO;
	}
	
	return atual->prox;
}