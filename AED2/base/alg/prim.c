#include "prim.h"
#include "grafo.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	int vertices;
	int* chave;
	int* pi;
	bool* naArvore;
} Prim;

bool haVerticesFora(Prim* p) {
	for (int i = 0; i < p->vertices; i++) {
		if (!p->naArvore[i]) return true;
	}
	return false;
}

void printKeys(Prim* p) {
	printf("[");
	for (int i = 0; i < p->vertices; i++) {
		if (p->naArvore[i]) {
			printf("-, ");
		} else {
			printf("%i, ", p->chave[i]);
		}
	}
	printf("-]\n");
}

int extrairProxVertice(Prim* p) {
	int index = -1;

	
	for (int i = p->vertices - 1; i >= 0; i--) {
		if (p->naArvore[i]) continue;

		if (index == -1 || p->chave[i] < p->chave[index]) {
			index = i;
		}
	}

	return index;
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
	bool naArvore[numVertices];
	
	Prim prim;
	prim.vertices = numVertices;
	prim.chave = chave;
	prim.pi = pi;
	prim.naArvore = naArvore;

	// Todos os vértices começam fora da AGM, então não possuem arestas na fronteira
	for (int i = 0; i < numVertices; i++) {
		chave[i] = INFINITY;
		pi[i] = -1;
		naArvore[i] = false;
	}

	chave[0] = 0;

	while(haVerticesFora(&prim)) {
		// u = prox
		printKeys(&prim);
		int prox = extrairProxVertice(&prim);
		printf("+ Prox vértice: %i\n", prox);

		if (prox == -1) break;

		naArvore[prox] = true;
		//int ponta = pi[prox];
		//printf("     Aresta: F %i -> %i D\n", prox, ponta);

		Apontador ap = primeiroListaAdj(g, prox);
		for (; apontadorValido(ap); ap = proxListaAdj(g, prox, ap)) {

			// v = adjacente
			int adjacente = verticeDestino(ap);
			
			// Se o adjacente está dentro da agm, deve ser ignorado
			if (naArvore[adjacente]) continue;

			int peso = obtemPesoAresta(g, prox, adjacente);

			//printf("  chk %i w: %i\n", adjacente, peso);

			if (peso < chave[adjacente]) {
				pi[adjacente] = prox;
				chave[adjacente] = peso;
			}

			printf("    key %i: %i\n", adjacente, chave[adjacente]);
		}

		int ant = pi[prox];
		if (ant != -1) {
			int w = obtemPesoAresta(g, prox, pi[prox]);
			printf("  !ADD %i > %i, w: %i\n", prox, pi[prox], w);
		}
	}

	for (int i = 0; i < numVertices; i++) {
		printf("%i: [pi: %i, k: %i]\n", i, chave[i], pi[i]);
	}
}