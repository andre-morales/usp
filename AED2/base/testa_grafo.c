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
//#include "alg/ciclico.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void printAdjacentes(Grafo*, int);
void pause();

void descoberta(Busca* b, int vert) {
	//printf("inic %i\n", vert);
}

bool aresta(Busca* b, BuscaAresta tipo, int vert, int dest) {
	//printf("ar %i:%i\n", vert, dest);
	return false;
}

void fechamento(Busca* b, int vert) {
	//printf("fech %i\n", vert);
}

int main() {
	Grafo grafo;
	Grafo* g = &grafo;
	leGrafo(g, "gr3.txt");

	imprimeGrafo(g);

	/*bool ci = ehGrafoCiclico(g);
	if (ci) {
		printf("cicli");
	} else {
		printf("nao cicli");
	}*/
	Callbacks calls = {
		.descoberta = &descoberta,
		.aresta = &aresta,
		.fechamento = &fechamento
	};
	buscaProfundidade(g, calls);

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