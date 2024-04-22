/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 22/04/2024
 * 
 * Arquivo de testes para as funções de grafo.
 **/
#include "grafo.h"
#include "alg/busca.h"
#include "alg/le_grafo.h"
#include "alg/busca_profundidade.h"
#include "alg/grafo_ciclico.h"
#include "alg/ordenacao_topologica.h"
#include "alg/busca_largura.h"
#include "alg/componentes_conexos.h"
#include "alg/caminho_curto.h"
#include "alg/prim.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void printAdjacentes(Grafo*, int);
void pause();
void teste2(Grafo*);
void teste3(Grafo*);
void teste4(Grafo*);
void teste5(Grafo*);
void teste6(Grafo*);
void teste7(Grafo*);

int main() {
	Grafo grafo;
	Grafo* g = &grafo;

	teste2(g);

	liberaGrafo(g);
}

void testa7(Grafo* g){
	leGrafo(g, "grafos/7.txt");
	imprimeGrafo(g);

	//prim(g);
}

// Testa encontrar caminhos mais curtos
void teste6(Grafo* g) {
	leGrafo(g, "grafos/6.txt");
	imprimeGrafo(g);

	const int origem = 0;
	const int destino = 2;

	int* caminho = caminhoCurto(g, origem, destino);
	if (!caminho) {
		printf("Não há caminho de %i para %i\n", origem, destino);
	} else {
		// Exibe o caminho descoberto
		printf("[Src: ");
		int v;
		int i = 0;
		while ((v = caminho[i++]) != destino) {
			printf("%i -> ", v);
		}
		printf("%i", destino);
		printf(" :Dst]\n");

		free(caminho);
	}
}

void teste5(Grafo* g) {
	leGrafo(g, "grafos/5.txt");
	imprimeGrafo(g);

	componentesConexos(g);
}

// Testa ordenação topológica
void teste4(Grafo* g) {
	leGrafo(g, "grafos/4.txt");
	imprimeGrafo(g);

	ordenarTopologicamente(g);
}

// Testa encontrar grafos cíclicos
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

// Testa algoritmo de busca em profundidade
void teste2(Grafo* g) {
	leGrafo(g, "grafos/3.txt");
	imprimeGrafo(g);

	Busca busca;
	inicializaBusca(&busca, g);

	buscaProfundidade(&busca);
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