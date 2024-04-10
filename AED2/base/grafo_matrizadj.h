#pragma once
#include <stdbool.h>

#define MAXNUMVERTICES 100
#define AN -1
#define VERTICE_INVALIDO -1

typedef int Peso;
typedef int Apontador;
typedef struct {
	Peso mat[MAXNUMVERTICES][MAXNUMVERTICES];
	int numVertices;
	int numArestas;
} Grafo;

// Inicializa o grafo alocado com o numero de vértices determinado
// Todos os vertices serão inicializados para AN
// Retorna true se a inicialização foi bem sucedida
bool inicializaGrafo(Grafo*, int);

// Imprime a matriz de adjacência de um grafo
void imprimeGrafo(Grafo*);

// Verifica se um vértice está dentro dos limites permitidos
bool verificaValidadeVertice(Grafo*, int);

// Insere uma aresta com um peso no grafo
void insereAresta(Grafo*, int, int, Peso);

bool existeAresta(Grafo*, int, int);

bool removeAresta(Grafo*, int, int, Peso*);

Apontador proxListaAdj(Grafo* g, int v, Apontador atual);

bool listaAdjVazia(Grafo*, int);

void liberaGrafo(Grafo*);