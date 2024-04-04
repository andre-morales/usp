typedef int Peso;

typedef struct aresta {
	int vdest;
	Peso peso;
	struct aresta* prox;
} Aresta;

typedef struct {
	Aresta** listaAdj;
	int numVertices;
	int numArestas;
} Grafo;

bool inicializaGrafo(Grafo*, int);

bool listaAdjVazia(int, Grafo*);