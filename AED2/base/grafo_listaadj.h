/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Cabeçalho para a implementação do grafo por listas de adjacência.
 **/
#if GRAFO_MATRIZ
#error ERRO! Incluindo header de grafo por lista mas compilando utilizando grafo por matriz
#endif

#ifdef GRAFO_IMPL
#error Header de grafo ja incluso
#else
#define GRAFO_IMPL 1
#endif

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

typedef struct GrafoType {
	Apontador* listaAdj;
	int numVertices;
	int numArestas;
	int inicializado;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int numVertices);

void liberaGrafo(Grafo* grafo);

int obtemNrVertices(Grafo* grafo);

int obtemNrArestas(Grafo* grafo);

void imprimeGrafo(Grafo* grafo);

// Obtém um apontador para o primeiro vértice adjacente ao dado, se houver.
Apontador primeiroListaAdj(Grafo* grafo, int vertice);

// Retorna o próximo vértice adjacente ao dado, utilizando um apontador previamente válido.
// Para começar a interação, utilize primeiroListaAdj().
Apontador proxListaAdj(Grafo* grafo, int vertice, Apontador atual);

bool listaAdjVazia(Grafo* grafo, int vertice);

// Verifica se um vértice está dentro dos limites possíveis do grafo.
bool verificaVertice(Grafo* grafo, int vertice);

// Extrai o índice do vértice apontado
int verticeDestino(Apontador ap);

// Verifica se um apontador é válido
bool apontadorValido(Apontador ap);

// Insere uma aresta entre v1 e v2 com peso p. Não verifica se a aresta já existe.
void insereAresta(Grafo* grafo, int v1, int v2, Peso p);

// Obtém o peso de uma aresta entre v1 e v2.
// Se a aresta não existir, retorna o peso sentinela AN.
Peso obtemPesoAresta(Grafo* grafo, int v1, int v2);

// Verifica a existência de uma entre v1 e v2
bool existeAresta(Grafo* grafo, int v1, int v2);

// Remove uma aresta opcionalmente obtendo o seu peso.
// Retorna verdadeiro se a aresta existe, falso c.c
bool removeAresta(Grafo* grafo, int v1, int v2, Peso* p);

// Cria uma cópia profunda desse grafo
Grafo* clonarGrafo(Grafo* g);

// Inverte a direção de todas as arestas no grafo
void transporGrafo(Grafo* g);

// Retorna verdadeiro se a implementação atual está usando grafos direcionados
bool ehGrafoDirecionado(Grafo* g);

// Remove todas as arestas envolvendo o vértice dado
void limparVertice(Grafo* g, int vert);

