#include "grafo_listaadj.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

// Verifica se existe uma aresta entre v1 e v2. Não faz checks.
bool existeAresta(Grafo* g, int v1, int v2) {
	return obtemPesoAresta(g, v1, v2) != AN;
}

// Obtém o peso de uma aresta sem realizar verificações
Peso obtemPesoArestaInseguro(Grafo* g, int v1, int v2) {
	// Obtém a primeira aresta adjacente de v1 para procurar v2
	Aresta* aresta = g->listaAdj[v1];

	while (aresta) {
		if (aresta->vdest == v2) {
			// Aresta encontrada, obtém seu peso
			return aresta->peso;
		}

		// Avança para a próxima aresta
		aresta = aresta->prox;
	}

	return AN;
}

Peso obtemPesoAresta(Grafo* grafo, int v1, int v2) {
	// Garante que os vértices são válidos
	assert(verificaVertice(grafo, v1));
	assert(verificaVertice(grafo, v2));

	// Obtém o peso da aresta
	Peso p = obtemPesoArestaInseguro(grafo, v1, v2);
	
	// Garante que o peso da aresta na outra direção é igual ao que encontramos nesta direção
	assert(obtemPesoArestaInseguro(grafo, v2, v1) == p);
}

void insereAresta(Grafo* grafo, int v1, int v2, Peso p) {
	// Garante a validade dos vértices
	assert(verificaVertice(grafo, v1));
	assert(verificaVertice(grafo, v2));

	// Cria uma aresta de V1 para V2, inserindo a aresta no começo da lista de adjacência
	Aresta* arestaA = (Aresta*)malloc(sizeof(Aresta));
	arestaA->prox = grafo->listaAdj[v1];
	arestaA->peso = p;
	arestaA->vdest = v2;

	grafo->listaAdj[v1] = arestaA;

	// Cria uma aresta de V2 para V1, inserindo a aresta no começo da lista de adjacência
	Aresta* arestaB = (Aresta*)malloc(sizeof(Aresta));
	arestaB->prox = grafo->listaAdj[v2];
	arestaB->peso = p;
	arestaB->vdest = v1;

	grafo->listaAdj[v2] = arestaB;	
}

Apontador primeiroListaAdj(Grafo* g, int v) {
	assert(verificaVertice(g, v));

	return g->listaAdj[v];
}

Apontador proxListaAdj(Grafo*, int v, Apontador atual) {
	if (atual == NULL) {
		return VERTICE_INVALIDO;
	}
	
	return atual->prox;
}

bool listaAdjVazia(Grafo* gr, int v) {
	// Assegura a validade do vértice
	assert(verificaVertice(gr, v));

	Aresta* lista = gr->listaAdj[v];
	return !lista;
}

bool verificaVertice(Grafo* g, int v) {
	if (v < 0 || v >= g->numVertices) {
		fprintf(stderr, "Vértice [%i] ilegal: 0 <= v < %i\n", v, g->numVertices);
		return false;
	}
	return true;
}