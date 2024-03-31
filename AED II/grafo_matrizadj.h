#pragma once
#include <stdbool.h>

#define MAXNUMVERTICES 100
#define AN -1

typedef int Peso;
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
bool verificaValidadeVertice(int, Grafo*);

// Insere uma aresta com um peso no grafo
void insereAresta(int, int, Peso, Grafo*);

bool existeAresta(int, int, Grafo*);

bool removeAresta(int, int, Peso*, Grafo*);

bool listaAdjVazia(int, Grafo*);

void liberaGrafo(Grafo*);