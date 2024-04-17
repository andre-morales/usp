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
	int n = g->numVertices;
	for (int i = 0; i < n; i++) {
		printf("V%i: ", i);
		
		Apontador ap = primeiroListaAdj(g, i);
		while (apontadorValido(ap)) {
			int dest = ap->vdest;
			Peso peso = ap->peso;
			printf("[%i: %i]  ", dest, peso);
			ap = proxListaAdj(g, i, ap);
		}

		printf("\n");
	}
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

// Extrai o índice do vértice apontado
int apontadorVertice(Apontador ap) {
	return ap->vdest;
}

bool apontadorValido(Apontador ap) {
	return ap != NULL;
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

// Remove uma aresta de v1 para v2. Sem verificação.
// Retornando verdadeiro se a aresta existia e gravando opcionalmente seu peso.
bool removeArestaSingular(Grafo* g, int v1, int v2, Peso* peso) {
	// Busca a presença de V2 na lista de adjacência de V1,
	// vamos iterar a lista de adjacência de v1
	Aresta* ant = NULL;
	Aresta* aresta = g->listaAdj[v1];
	while (aresta) {
		// Se a aresta não aponta para v2, seguimos procurando
		if (aresta->vdest != v2) {
			ant = aresta;
			aresta = aresta->prox;
			continue;
		}

		// Encontramos uma aresta que aponta para v2, salvamos o peso da aresta primeiro
		if (peso) *peso = aresta->peso;
		
		// Se não há anterior, a aresta que vamos remover está no início da lista
		if (!ant) {
			g->listaAdj[v1] = aresta->prox;
		} else {
			ant->prox = aresta->prox;
		}

		free(aresta);
		return true;
	}

	// Não existia aresta entre v1 e v2
	return false;
}

bool removeAresta(Grafo* g, int v1, int v2, Peso* p) {
	// Verifica a validade dos vértices
	assert(verificaVertice(g, v1));
	assert(verificaVertice(g, v2));

	// Remove a aresta V1 -> V2
	Peso p1 = AN;
	bool existia1 = removeArestaSingular(g, v1, v2, &p1);

	// Remove a aresta V2 -> V1
	Peso p2 = AN;
	bool existia2 = removeArestaSingular(g, v2, v1, &p2);

	// Garanta a integridade do grafo: os pesos e a existência das arestas direcionais devem ser os mesmos
	assert(p1 == p2);
	assert(existia1 == existia2);

	if (p) *p = p1;
	return existia1;
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