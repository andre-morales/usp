/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Arquivo de testes para as funções de grafo.
 **/
#include "grafo_listaadj.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void leGrafo(Grafo* g, char* arquivo);
void printAdjacentes(Grafo* g, int V);
void pause();

void main() {
	Grafo grafo;
	Grafo* g = &grafo;
	leGrafo(g, "teste1.txt");

	imprimeGrafo(g);

	removeAresta(g, 1, 3, NULL);

	imprimeGrafo(g);

	liberaGrafo(g);
}

void leGrafo(Grafo* g, char* arquivo) {
	// Abertura do arquivo
	FILE* str = fopen(arquivo, "r");
	if (!str) {
		fprintf(stderr, "Arquivo '%s' não encontrado.\n", arquivo);
		exit(-1);
		return;
	}

	// Le o cabeçalho do arquivo e cria o grafo
	int numVertices, numArestas;
	fscanf(str, "%i %i", &numVertices, &numArestas);
	inicializaGrafo(g, numVertices);

	// Lê cada aresta
	for (int i = 0; i < numArestas; i++) {
		Peso peso;
		int v1, v2;
		fscanf(str, "%i %i %i", &v1, &v2, &peso);

		insereAresta(g, v1, v2, peso);
	}

	// Verificações de sanidade
	assert(obtemNrVertices(g) == numVertices);
	assert(obtemNrArestas(g) == numArestas);

	fclose(str);
}

void printAdjacentes(Grafo* g, int V) {
	printf("Adjacentes de V: \n", V);

	Apontador aresta = primeiroListaAdj(g, V);
	while(true) {
		if (aresta == VERTICE_INVALIDO) break;
		
		printf("%i ", apontadorVertice(aresta));
		aresta = proxListaAdj(g, V, aresta);
	}
	printf("\n");
}

void pause() {
	getchar();
}