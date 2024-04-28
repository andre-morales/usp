/**
 * Autor: André Morales
 * Criação: 23/04/2024
 * Modificação: 23/04/2024
 * 
 * Algoritmo de Dijkstra para a geração da árvore de caminhos mínimos
 **/
#include "dijkstra.h"
#include "grafo.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

void diCaminhos(ACM* acm, int fonte);
void diInit(ACM* acm, int fonte);
void diRelax(ACM* acm, int a, int b);
int diExtrair(ACM* acm);

void inicializaACM(ACM* acm, Grafo* grafo) {
	int numVerts = grafo->numVertices;

	acm->grafo = grafo;
	acm->distancia = (int*) malloc(sizeof(int[numVerts]));
	acm->antecessor = (int*) malloc(sizeof(int[numVerts]));
	acm->verticesAtivos = (bool*) malloc(sizeof(bool[numVerts]));
}

// DIJKSTRA():
// Executa o algoritmo de Dijkstra a partir de fonte
void diCaminhos(ACM* acm, int fonte) {
	Grafo* g = acm->grafo;

	// Inicializa a estrutura
	diInit(acm, fonte);

	// Vamos iterar por todos os vértices do grafo
	while (true) {
		// Pega o índice do vértice de menor distância estimada até agora
		int u = diExtrair(acm);

		// Se acabaram todos os vértices, sai do loop
		if (u == -1) break;

		// Itera por todos os adjacentes V do vértice U
		Apontador ap = primeiroListaAdj(g, u);
		for (; apontadorValido(ap); ap = proxListaAdj(g, u, ap)) {
			int v = verticeDestino(ap);

			// Relaxa a aresta U-V. Ou seja, analise ela e veja se ela melhora o caminho até V
			diRelax(acm, u, v);
		}
	}
}

// INITIALIZE-SINGLE-SOURCE():
// Prepara a ACM para executar o algoritmo de Dijkstra a partir do vértice fonte
void diInit(ACM* acm, int fonte) {
	int numVerts = acm->grafo->numVertices;

	// for each vertex... 
	for (int v = 0; v < numVerts; v++) {
		acm->distancia[v] = INT_MAX;
		acm->antecessor[v] = -1;
		acm->verticesAtivos[v] = true;
	}

	// d[s] = 0
	acm->distancia[fonte] = 0;
}

// RELAX(): Relaxa uma aresta de U a V
// Analisa a aresta U-V e verifica se ela contribui com um caminho mais rápido até V.
// Se ela não contribuir, mantém o caminho que V já tinha
void diRelax(ACM* acm, int u, int v) {
	Grafo* grafo = acm->grafo;
	int* dist = acm->distancia; // d
	int* ant = acm->antecessor; // pi

	// Peso dessa aresta U-V
	int peso = obtemPesoAresta(grafo, u, v); // w

	// Se a distância desse vértice U + o peso da aresta em análise trazem uma distância menor
	// para o vértice V
	if (dist[u] + peso < dist[v]) {
		// Vértice V agora terá um caminho que passa por U
		dist[v] = dist[u] + peso;
		ant[v] = u;
	}
}

// EXTRACT-MIN():
// Procura o vértice de menor distância estimada e retorna o seu índice para ser o próximo alvo
// do algoritmo.
int diExtrair(ACM* acm) {
	// Atualmente não usa os heaps eficientes. Por simplificação, apenas itera por todos os
	// vértices, encontra o de menor distância e retorna o seu índice.
	
	int numVertices = acm->grafo->numVertices;
	bool* ativos = acm->verticesAtivos;
	int* dist = acm->distancia;

	// Índice do vértice de menor encontrado
	int min = -1;
	for (int i = 0; i < numVertices; i++) {
		// Se o vértice não está ativo, não o considere
		if (!ativos[i]) continue;

		// Se não houver nenhum mínimo ou se ele for o menor até agora
		if (min == -1 || dist[i] < dist[min]){
			min = i;
		}
	}

	// Se não há mais nenhum vértice ativo para ser o próximo alvo, retorna -1
	if (min == -1) return -1;

	// Desativa o vértice de menor distância para que ele não seja extraído na próxima iteração
	ativos[min] = false;
	return min;
}

static char c(int n) {
	if (n == 0) return 's';
	if (n == 1) return 't';
	if (n == 2) return 'x';
	if (n == 3) return 'y';
	if (n == 4) return 'z';
	return '@';
}

void diImprime(ACM* acm) {
	printf("--------- ACM: Dijkstra --------- \n");
	int numVerts = obtemNrVertices(acm->grafo);
	for (int i = 0; i < numVerts; i++) {
		int d = acm->distancia[i];
		int pi = acm->antecessor[i];

		printf("%i: [d: ", i);
		if (d == INT_MAX) {
			printf("+∞");
		} else {
			printf("%*i", 2, d);
		}
		printf(", π: %*i]\n", 2, pi);
	}	
}
