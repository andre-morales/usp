/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Arquivo de testes para as funções de grafo.
 **/
#include "grafo_matrizadj.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum {
	BUSCA_BRANCO, BUSCA_CINZA, BUSCA_PRETO
} BuscaCor;

typedef struct {
	int* tempo;
	BuscaCor* cor;
	int* tempoDesc;
	int* tempoTerm;
	int* antecessor;
} Busca;

void buscaProfundidade(Grafo* g);
void visitaBP(Grafo* g, int v, Busca busca);

void leGrafo(Grafo* g, char* arquivo);
void printAdjacentes(Grafo* g, int V);
void pause();

int main() {
	Grafo grafo;
	Grafo* g = &grafo;
	leGrafo(g, "gr1.txt");

	imprimeGrafo(g);

	buscaProfundidade(g);

	liberaGrafo(g);
}

void buscaProfundidade(Grafo* g) {
	int numVertices = obtemNrVertices(g);

	// Inicialização das estruturas básicas
	int tempo = 0;
	BuscaCor cor[numVertices];
	int tempoDesc[numVertices];
	int tempoTerm[numVertices];
	int antecessor[numVertices];

	Busca busca = {
		.tempo = &tempo,
		.cor = cor,
		.tempoDesc = tempoDesc,
		.tempoTerm = tempoTerm,
		.antecessor = antecessor
	};

	for (int i = 0; i < numVertices; i++) {
		cor[i] = BUSCA_BRANCO;
		tempoDesc[i] = 0;
		tempoTerm[i] = 0;
		antecessor[i] = -1;
	}

	// Visita cada vértice
	for (int i = 0; i < numVertices; i++) {
		visitaBP(g, i, busca);	
	}
}

// Visita um vértice em busca de profundidade.
// V: O vértice a visitar
// tempo: referência para o relógio geral do algoritmo, incrementado para cada evento de
//        descoberta ou término
// cor: referência para o arranjo de cores de todos os vértices
// tempoDesc: referência para o tempo de descoberta de todos os vértices
// tempoTerm: referência para o tempo de término de visita de todos os vértices
void visitaBP(Grafo* gr, int v, Busca b) {
	// Se o vértice já foi descoberto, não faz nada.
	if (b.cor[v] != BUSCA_BRANCO) return;

	// Evento de descoberta: o vértice passa a ser cinza, incrementa o relógio global e
	// registra o tempo de descoberta
	b.cor[v] = BUSCA_CINZA;
	b.tempoDesc[v] = ++(*b.tempo);

	printf("%i: INI %i\n", v, b.tempoDesc[v]);

	// Pega o primeiro vértice alcançável por V para iterar por todos os alcançáveis
	Apontador ap = primeiroListaAdj(gr, v);
	while (apontadorValido(ap)) {
		// Obtém o índice do vértice adjacente
		int adjacente = verticeDestino(ap);

		// Salva o antecessor do próximo vértice (adjacente) e invoca o algoritmo no adjacente
		b.antecessor[adjacente] = v;
		visitaBP(gr, adjacente, b);

		// Avança para o próximo adjacente
		ap = proxListaAdj(gr, v, ap);
	}

	// Evento de término: troca a cor do vértice para preto e incrementa o relógio global
	b.cor[v] = BUSCA_PRETO;
	b.tempoTerm[v] = ++(*b.tempo);

	printf("%i: FIM %i\n", v, b.tempoTerm[v]);
}

void leGrafo(Grafo* g, char* arquivo) {
	printf("Lendo grafo...\n");

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

		printf("Inserindo aresta %i:%i\n", v1, v2);
		insereAresta(g, v1, v2, peso);
	}

	// Verificações de sanidade
	assert(obtemNrVertices(g) == numVertices);
	assert(obtemNrArestas(g) == numArestas);

	fclose(str);
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