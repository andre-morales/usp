/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 23/04/2024
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
#include "alg/dijkstra.h"
#include "alg/vertices_articulacao.h"
#include "estr/vetor.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void printAdjacentes(Grafo*, int);
void pause();

// Busca em profundidade
void teste1(Grafo*);

// Grafos cíclicos
void teste2(Grafo*);

// Ordenação topológica
void teste3(Grafo*);

// Componentes conexos
void teste4(Grafo*);

// Caminhos mais curtos
void teste5(Grafo*);

// Prim
void teste6(Grafo*);

// Árvore geradora mínima -- Dijkstra
void teste7(Grafo*);

// Vértices de articulação
void teste8(Grafo*);

void saidas();

int main(int, char**) {
	saidas();
	/*Grafo grafo;
	Grafo* g = &grafo;

	leGrafo(g, "grafos/10.txt");
	imprimeGrafo(g);

	teste8(g);

	liberaGrafo(g);*/
	printf("Fim.");
}

void teste8(Grafo* g) {
	Busca busca;
	inicializaBusca(&busca, g);
	buscaProfundidade(&busca);

	int ant = 4;
	while (ant != -1) {
		printf("%i ", ant);
		ant = busca.antecessor[ant];
	}
	printf("\n");

	// Vértices de articulação
	Vetor vet;
	vetorInicializar(&vet);
	int numArticuladores = verticesArticulacao(g, &vet);
	
	printf("Total de %i Vértices de Articulação: ", numArticuladores);
	vetorImprimir(&vet);
	printf("\n");

	vetorLiberar(&vet);
}

void teste7(Grafo* g){
	ACM acm;
	inicializaACM(&acm, g);

	diCaminhos(&acm, 5);
	diImprime(&acm);
}

void teste6(Grafo* g){
	prim(g);
}

// Testa encontrar caminhos mais curtos
void teste5(Grafo* g) {
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

void teste4(Grafo* g) {
	int num = componentesConexos(g, NULL);
	printf("Componentes conectados: %i\n", num);
}

// Testa ordenação topológica
void teste3(Grafo* g) {
	ordenarTopologicamente(g);
}

// Testa encontrar grafos cíclicos
void teste2(Grafo* g) {
	bool ci = ehGrafoCiclico(g, true);
	if (ci) {
		printf("Cíclico\n");
	} else {
		printf("Não cíclico\n");
	}
}

// Testa algoritmo de busca em profundidade
void teste1(Grafo* g) {
	Busca busca;
	inicializaBusca(&busca, g);

	buscaProfundidade(&busca);
}

void pause() {
	getchar();
}