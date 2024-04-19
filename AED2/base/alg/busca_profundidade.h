#pragma once
struct GrafoType;
typedef struct GrafoType Grafo;

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

void buscaProfundidade(Grafo* grafo);
