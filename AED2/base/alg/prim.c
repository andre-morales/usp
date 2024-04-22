#include "prim.h"
#include <stdbool.h>

typedef struct {
	int vertices;
	int* chave;
	int* pi;
	bool* fora;
} Prim;

bool haVerticesFora(Prim* p) {
	for (int i = 0; i < p->vertices; i++) {
		if (p->fora[i]) return true;
	}
	return false;
}

int extrairProxVertice(Prim* p) {
	int key;
	for (int i = 0; i < p->vertices; i++) {
		if (p->fora[i]) {
			key = i;
			break;
		}
	}

	for (int i = 0; i < p->vertices; i++) {
		if (!p->fora[i]) continue;

		if (p->chave[i] < p->chave[key]) {
			key = i;
		}
	}
}

void prim(Grafo* g) {
	const int INFINITY = 1000;

	int numVertices = obtemNrVertices(g);

	// Atualizado apenas para os vértices fora da AGM.
	// Para qualquer vértice de fora (da AGM), será o menor peso possível de alguma aresta entre
	// esse vértice de fora e um vértice de dentro.
	// Em outros termos, para os vértices de fora, será o peso da aresta de menor peso da fronteira
	// a qual esse vértice participa
	int chave[numVertices];
	
	// Para todos os vértices de fora da AGM
	// Será o índice de um vértice de dentro da AGM, indicando que existe uma aresta na fronteira
	int pi[numVertices];
	
	// Para qualquer índice I nesse vetor, se o valor for verdadeiro indicia que o vértice
	// de índice I ainda está fora da AGM
	bool fora[numVertices];
	
	Prim prim;
	prim.vertices = numVertices;
	prim.chave = &chave;
	prim.pi = &pi;
	prim.fora = &fora;


	// Todos os vértices começam fora da AGM, então não possuem arestas na fronteira
	for (int i = 0; i < numVertices; i++) {
		chave[i] = INFINITY;
		pi[i] = -1;
		fora[i] = true;
	}

	chave[0] = 0;

	while(haVerticesFora(&prim)) {
		int prox = extrairProxVertice(&prim);
		printf("Prox vértice: %i\n", prox);

		fora[prox] = false;
		int ponta = pi[prox];
		printf("Aresta: F %i -> %i D\n", prox, ponta);

		Apontador ap = primeiroListaAdj(g, vert);
		for (; apontadorValido(ap); ap = proxListaAdj(g, vert, ap)) {
			int adjacente = verticeDestino(ap);
			if (fora[adjacente]) continue;
		}
	}
}