#include "grafo_matrizadj.h"
#include <stdio.h>

bool inicializaGrafo(Grafo* g, int v) {
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

	g->numVertices = v;
	g->numArestas = 0;

	for (int y = 0; y < v; y++) {
		for (int x = 0; x < v; x++) {
			g->mat[y][x] = AN;
		}
	}

	return true;
}

void imprimeGrafo(Grafo* g) {
	// Print header
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

bool verificaValidadeVertice(Grafo* g, int v) {
	if (v < 0 || v >= g->numVertices) {
		fprintf(stderr, "Vértice [%i] ilegal: 0 <= v < %i\n", v, g->numVertices);
		return false;
	}
	return true;
}

void insereAresta(Grafo* g, int v1, int v2, Peso w) {
	if (!verificaValidadeVertice(g, v1) || !verificaValidadeVertice(g, v2)) return;

	g->mat[v1][v2] = w;
	g->numArestas++;
}

Peso obtemPesoAresta(Grafo* g, int v1, int v2) {
	if (!verificaValidadeVertice(g, v1) || !verificaValidadeVertice(g, v2)) return AN;

	return g->mat[v1][v2];
}

bool existeAresta(Grafo* g, int v1, int v2) {
	int w = obtemPesoAresta(g, v1, v2);
	return w != AN;
}

bool removeAresta(Grafo* g, int v1, int v2, Peso* outWeight) {
	if (!verificaValidadeVertice(g, v1) || !verificaValidadeVertice(g, v2)) return false;

	Peso w = g->mat[v1][v2];

	// Aresta inexistente
	if (w == AN) return false;

	if (outWeight) *outWeight = w;

	g->mat[v1][v2] = AN;
	g->numArestas--;
	return true;
}

bool listaAdjVazia(Grafo* g, int v) {
	if (!verificaValidadeVertice(g, v)) return false;

	for (int i = 0; i < g->numVertices; i++) {
		if (g->mat[v][i] != AN) return false;
	}

	return false;
}

Apontador primeiroListaAdj(Grafo* g, int v) {
	if (!verificaValidadeVertice(g, v)) return VERTICE_INVALIDO;

	return proxListaAdj(g, v, -1);
}

Apontador proxListaAdj(Grafo* g, int v, Apontador atual) {
	if (!verificaValidadeVertice(g, v)) {
		return VERTICE_INVALIDO;
	}

	/* -- Código original não faz parada na última aresta
	atual++;
	while(atual < g->numVertices && g->mat[v][atual] == AN) {
		atual++;
		if (atual == g->numVertices) {
			return VERTICE_INVALIDO;
		}
	}
	return atual;
	*/

	atual++;
	for(; atual < g->numVertices; atual++) {
		// Enquanto estivermos passando por arestas nulas, apenas continue
		if (g->mat[v][atual] == AN) continue;
		
		return atual;
	}
	return VERTICE_INVALIDO;
}

void liberaGrafo(Grafo* g) {}