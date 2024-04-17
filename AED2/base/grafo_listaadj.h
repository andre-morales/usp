#include <stdbool.h>

#define VERTICE_INVALIDO NULL
#define AN -1

typedef int Peso;

typedef struct aresta {
	int vdest;
	Peso peso;
	struct aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
	Apontador* listaAdj;
	int numVertices;
	int numArestas;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int numVertices);

void imprimeGrafo(Grafo* grafo);

bool verificaVertice(Grafo* grafo, int vertice);

// Insere uma aresta entre v1 e v2 com peso p. Não verifica se a aresta já existe.
void insereAresta(Grafo* grafo, int v1, int v2, Peso p);

bool existeAresta(Grafo* grafo, int v1, int v2);

// Remove uma aresta opcionalmente obtendo o seu peso.
// Retorna verdadeiro se a aresta existe, falso c.c
bool removeAresta(Grafo* grafo, int v1, int v2, Peso* p);

Peso obtemPesoAresta(Grafo* grafo, int v1, int v2);

// Extrai o índice do vértice apontado
int apontadorVertice(Apontador ap);

// Verifica se um apontador é válido
bool apontadorValido(Apontador ap);

Apontador primeiroListaAdj(Grafo* grafo, int vertice);

Apontador proxListaAdj(Grafo* grafo, int vertice, Apontador atual);

bool listaAdjVazia(Grafo* grafo, int vertice);

