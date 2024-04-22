/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Cabeçalho para a implementação do grafo por matrizes de adjacência.
 **/
#if GRAFO_LISTA
#error ERRO! Incluindo header de grafo por matriz mas compilando utilizando grafo por lista
#endif

#ifdef GRAFO_IMPL
#error Header de grafo ja incluso
#else
#define GRAFO_IMPL 1
#endif

#include <stdbool.h>
#define MAXNUMVERTICES 100
#define AN -1
#define VERTICE_INVALIDO -1

typedef int Peso;
typedef int Apontador;
typedef struct GrafoType {
	Peso mat[MAXNUMVERTICES][MAXNUMVERTICES];
	int numVertices;
	int numArestas;
} Grafo;

// Inicializa o grafo alocado com o numero de vértices determinado
// Todos os vertices serão inicializados para AN
// Retorna true se a inicialização foi bem sucedida
bool inicializaGrafo(Grafo* g, int nVertices);

// Libera toda a memória utilizada pelo grafo e suas arestas
// Na implementação por matrizes, é um NO-OP
void liberaGrafo(Grafo* g);

// Imprime a matriz de adjacência de um grafo
void imprimeGrafo(Grafo* g);

int obtemNrVertices(Grafo* grafo);

int obtemNrArestas(Grafo* grafo);

// Verifica se um vértice está dentro dos limites permitidos
bool verificaVertice(Grafo*, int v);

// Extrai o índice do vértice apontado
int verticeDestino(Apontador ap);

// Verifica se um apontador é válido
bool apontadorValido(Apontador ap);

// Retorna um apontador para o primeiro vértice adjacente a este
Apontador primeiroListaAdj(Grafo* g, int v);

// Utilizando um apontador já previamente válido, retorna o próximo vértice adjacente a V
Apontador proxListaAdj(Grafo* g, int v, Apontador atual);

// Retorna verdadeiro se o vértice indicado não possui adjacentes, falso c.c
bool listaAdjVazia(Grafo* g, int v);

// Insere uma aresta com um peso no grafo
void insereAresta(Grafo* g, int v1, int v2, Peso p);

// Verifica se existe uma aresta entre os vértices V1 e V2 no grafo
bool existeAresta(Grafo* g, int v1, int v2);

// Remove uma aresta entre os vértices V1 e V2, opcionalmente extraindo seu peso
// Retorna verdadeiro se a aresta existia, falso c.c
bool removeAresta(Grafo* g, int v1, int v2, Peso* p);

// Inverte a direção de todas as arestas no grafo
void transporGrafo(Grafo* g);