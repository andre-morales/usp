#include <stdbool.h>

typedef int Peso;

typedef struct aresta {
	int vdest;
	Peso peso;
	struct aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
	Aresta** listaAdj;
	int numVertices;
	int numArestas;
} Grafo;

bool inicializaGrafo(Grafo*, int);

void imprimeGrafo(Grafo*);

bool listaAdjVazia(Grafo*, int);

Apontador proxListaAdj(Grafo*, int v, Apontador atual);