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

typedef enum {
	BUSCA_BRANCO, BUSCA_CINZA, BUSCA_PRETO
} BuscaCor;

void buscaProfundidade(Grafo* g);
void visitaBP(Grafo* g, int v, int* tempo, BuscaCor cor[], int tempoDesc[], int tempoTerm[]);

void leGrafo(Grafo* g, char* arquivo);
void printAdjacentes(Grafo* g, int V);
void pause();

void main() {
	Grafo grafo;
	Grafo* g = &grafo;
	leGrafo(g, "teste1.txt");

	imprimeGrafo(g);

	buscaProfundidade(g);

	liberaGrafo(g);
}

void buscaProfundidade(Grafo* g) {
	int numVertices = obtemNrVertices(g);

	// Inicialização das estruturas básicas
	int tempo = 0;
	BuscaCor cores[numVertices];
	int tempoDesc[numVertices];
	int tempoTerm[numVertices];

	for (int i = 0; i < numVertices; i++) {
		cores[i] = BUSCA_BRANCO;
		tempoDesc[i] = 0;
		tempoTerm[i] = 0;
	}

	// Visita o vértice inicial
	int inicio = 0;
	visitaBP(g, inicio, &tempo, cores, tempoDesc, tempoTerm);
}

// Visita um vértice em busca de profundidade.
// V: O vértice a visitar
// tempo: referência para o relógio geral do algoritmo, incrementado para cada evento de
//        descoberta ou término
// cor: referência para o arranjo de cores de todos os vértices
// tempoDesc: referência para o tempo de descoberta de todos os vértices
// tempoTerm: referência para o tempo de término de visita de todos os vértices
void visitaBP(Grafo* g, int v, int* tempo, BuscaCor cor[], int tempoDesc[], int tempoTerm[]) {
	// Se o vértice já foi descoberto, não faz nada.
	if (cor[v] != BUSCA_BRANCO) return;

	// Evento de descoberta: o vértice passa a ser cinza, incrementa o relógio global e
	// registra o tempo de descoberta
	cor[v] = BUSCA_CINZA;
	tempoDesc[v] = ++(*tempo);

	printf("%i: INI %i\n", v, tempoDesc[v]);

	// Pega o primeiro vértice alcançável por V para iterar por todos os alcançáveis
	Apontador ap = primeiroListaAdj(g, v);
	while (ap) {
		// Obtém o índice do vértice adjacente e invoca o algoritmo no adjacente
		int adjacente = apontadorVertice(ap);
		visitaBP(g, adjacente, tempo, cor, tempoDesc, tempoTerm);

		// Avança para o próximo adjacente
		ap = proxListaAdj(g, v, ap);
	}

	// Evento de término: troca a cor do vértice para preto e incrementa o relógio global
	cor[v] = BUSCA_PRETO;
	tempoTerm[v] = ++(*tempo);

	printf("%i: FIM %i\n", v, tempoTerm[v]);
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