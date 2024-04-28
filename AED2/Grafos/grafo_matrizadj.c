/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Implementação das funções base para o grafo por matrizes de adjacência.
 **/
#include "grafo_matrizadj.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#if GRAFO_DIRECIONADO
#define TIPO_GRAFO "DIR"
#else
#define TIPO_GRAFO "UND"
#endif

#define GRAFO_INICIALIZADO 0xAAC0FFEE

bool inicializaGrafo(Grafo* g, int v) {
	// Garantindo que o grafo nao foi inicializado antes
	assert(g->inicializado != GRAFO_INICIALIZADO);

	// Testes de sanidade
	if (g == NULL) {
		fprintf(stderr, "ERRO: inicializaGrafo()\n");
		fprintf(stderr, "  Grafo não pode ser nulo.");
		return false;
	}
	if (v <= 0 || v > MAXNUMVERTICES) {
		fprintf(stderr, "ERRO: inicializaGrafo()\n");
		fprintf(stderr, "  O número de vértices especificado [%i] está fora do limite permitido. 0 < v < %i\n", v, MAXNUMVERTICES);
		return false;
	}

	g->inicializado = GRAFO_INICIALIZADO;
	g->numVertices = v;
	g->numArestas = 0;

	for (int y = 0; y < v; y++) {
		for (int x = 0; x < v; x++) {
			g->mat[y][x] = AN;
		}
	}

	return true;
}

void liberaGrafo(Grafo* g) {
	if (g->inicializado != GRAFO_INICIALIZADO) return;
	g->inicializado = 0;
}

void imprimeGrafo(Grafo* g) {
	// Print header
	printf("-------- [%i %s %i] --------\n", g->numVertices, TIPO_GRAFO, g->numArestas);
	printf("    ");
	for (int x = 0; x < g->numVertices; x++) {
		printf("%i ", x);
	}
	printf("\n");

	for (int y = 0; y < g->numVertices; y++) {
		printf("%i | ", y);
		for (int x = 0; x < g->numVertices; x++) {
			int a = g->mat[y][x];
			if (a == AN) {
				printf(". ");
			} else {
				printf("%*i ", 1, a);
			}
		}	
		printf("\n");
	}
}

bool verificaVertice(Grafo* g, int v) {
	if (v < 0 || v >= g->numVertices) {
		fprintf(stderr, "Vértice [%i] ilegal: 0 <= v < %i\n", v, g->numVertices);
		return false;
	}
	return true;
}

#if GRAFO_DIRECIONADO
	void insereAresta(Grafo* g, int v1, int v2, Peso w) {
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		g->mat[v1][v2] = w;
		g->numArestas++;
	}

	Peso obtemPesoAresta(Grafo* g, int v1, int v2) {
		// Garante que os vértices são válidos
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		return g->mat[v1][v2];
	}

	bool existeAresta(Grafo* g, int v1, int v2) {
		int w = obtemPesoAresta(g, v1, v2);
		return w != AN;
	}

	bool removeAresta(Grafo* g, int v1, int v2, Peso* outWeight) {
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		Peso w = g->mat[v1][v2];

		// Aresta inexistente
		if (w == AN) return false;

		if (outWeight) *outWeight = w;

		g->mat[v1][v2] = AN;
		g->numArestas--;
		return true;
	}
// Grafos não direcionados
#else
	void insereAresta(Grafo* g, int v1, int v2, Peso w) {
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		g->mat[v1][v2] = w;
		g->mat[v2][v1] = w;
		g->numArestas++;
	}

	Peso obtemPesoAresta(Grafo* g, int v1, int v2) {
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		// Assegura que a outra aresta simétrica tem mesmo peso
		assert(g->mat[v1][v2] == g->mat[v2][v1]);

		return g->mat[v1][v2];
	}

	bool existeAresta(Grafo* g, int v1, int v2) {
		Peso p = obtemPesoAresta(g, v1, v2);
		return p != AN;
	}

	bool removeAresta(Grafo* g, int v1, int v2, Peso* peso) {
		// Obtém o peso e verifica se a aresta realmente existe
		Peso p = obtemPesoAresta(g, v1, v2);	
		if (p == AN) return false;

		// Salva o peso se o usuário deseja
		if (peso) *peso = p;

		g->mat[v1][v2] = AN;
		g->mat[v2][v1] = AN;
		g->numArestas--;
		return true;
	}
#endif

bool listaAdjVazia(Grafo* g, int v) {
	if (!verificaVertice(g, v)) return false;

	for (int i = 0; i < g->numVertices; i++) {
		if (g->mat[v][i] != AN) return false;
	}

	return false;
}

Apontador primeiroListaAdj(Grafo* g, int v) {
	if (!verificaVertice(g, v)) return VERTICE_INVALIDO;

	return proxListaAdj(g, v, -1);
}

Apontador proxListaAdj(Grafo* g, int v, Apontador atual) {
	if (!verificaVertice(g, v)) {
		return VERTICE_INVALIDO;
	}

	atual++;
	for(; atual < g->numVertices; atual++) {
		// Enquanto estivermos passando por arestas nulas, apenas continue
		if (g->mat[v][atual] == AN) continue;
		
		return atual;
	}
	return VERTICE_INVALIDO;
}

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void transporGrafo(Grafo* g) {
	printf("inverting\n");
	// Troca todas as arestas de X -> Y para Y -> X
	for (int y = 0; y < g->numVertices; y++) {
		for (int x = 0; x < y; x++) {
			//Peso tmp = g->mat[y][x];
			//g->mat[y][x] = g->mat[x][y];
			//g->mat[x][y] = tmp;
			swap(&g->mat[x][y], &g->mat[y][x]);
		}
	}
}

Grafo* clonarGrafo(Grafo* g) {
	int numVerts = g->numVertices;

	Grafo* novo = (Grafo*) malloc(sizeof(Grafo));
	inicializaGrafo(novo, numVerts);

	for (int x = 0; x < numVerts; x++) {
		for (int y = 0; y < numVerts; y++) {
			novo->mat[x][y] = g->mat[x][y];
		}
	}
	return novo;
}

void limparVertice(Grafo* g, int vert) {
	int nv = g->numVertices;
	for (int i = 0; i < nv; i++) {
		g->mat[i][vert] = AN;
		g->mat[vert][i] = AN;
	}
}

int obtemNrVertices(Grafo* grafo) {
	return grafo->numVertices;
}

int obtemNrArestas(Grafo* grafo) {
	return grafo->numArestas;
}

int verticeDestino(Apontador ap) {
	return ap;
}

bool apontadorValido(Apontador ap) {
	return ap != VERTICE_INVALIDO;
}

bool ehGrafoDirecionado(Grafo* g) {
	#if GRAFO_DIRECIONADO
	return true;
	#else
	return false;
	#endif
}