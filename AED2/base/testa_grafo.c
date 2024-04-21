/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Arquivo de testes para as funções de grafo.
 **/
#include "grafo.h"
#include "alg/le_grafo.h"
#include "alg/busca_profundidade.h"
#include "alg/grafo_ciclico.h"
#include "alg/ordenacao_topologica.h"
#include "alg/busca_largura.h"
#include "alg/caminho_curto.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void printAdjacentes(Grafo*, int);
void pause();
void teste2(Grafo*);
void teste3(Grafo*);
void teste4(Grafo*);
void teste5(Grafo*);

int main() {
	Grafo grafo;
	Grafo* g = &grafo;

	teste5(g);

	liberaGrafo(g);
}

void teste5(Grafo* g) {
	leGrafo(g, "grafos/5.txt");
	imprimeGrafo(g);

	caminhoCurto(g, 0, 2);

	liberaGrafo(g);
}

void teste4(Grafo* g) {
	leGrafo(g, "grafos/4.txt");
	imprimeGrafo(g);

	ordenarTopologicamente(g);
}

void teste3(Grafo* g) {
	leGrafo(g, "grafos/3.txt");
	imprimeGrafo(g);

	bool ci = ehGrafoCiclico(g);
	if (ci) {
		printf("Cíclico\n");
	} else {
		printf("Não cíclico\n");
	}
}

void teste2(Grafo* g) {
	leGrafo(g, "grafos/2.txt");
	imprimeGrafo(g);

	Acessos acessos = { NULL };

	buscaProfundidade(g, acessos, NULL);
}

void exIterarAdjacentes(Grafo* g) {
	// Itera todos os adjacentes do vértice 4 por exemplo
	int vert = 4;

	// Primeiro adjacente
	Apontador ap = primeiroListaAdj(g, vert);

	while(apontadorValido(ap)) {
		// Índice do vértice adjacente
		int adjacente = verticeDestino(ap);

		printf("Adjacente de %i é %i\n", vert, adjacente);

		// Avança para o próximo adjacente
		ap = proxListaAdj(g, vert, ap);
	}
}

void pause() {
	getchar();
}