#pragma once
#include "../grafo_fwd.h"

// Cores possíveis de um vértice durante uma busca.
// BRANCO: Vértice ainda não foi descoberto
// CINZA: Vértice já foi descoberto mas seus adjacentes ainda estão sendo investigados
// PRETO: Vértice já foi investigado e todos seus adjacentes foram explorados
typedef enum {
	BUSCA_BRANCO, BUSCA_CINZA, BUSCA_PRETO
} BuscaCor;

typedef enum {
	ARESTA_ARVORE, ARESTA_RETORNO, ARESTA_AVANCO, ARESTA_CRUZAMENTO
} BuscaAresta;

typedef struct {
	int* tempo;
	BuscaCor* cor;
	int* tempoDesc;
	int* tempoTerm;
	int* antecessor;
	struct CallbacksType* calls;
} Busca;

typedef void(*DescobertaFn)(Busca* busca, int vert);
typedef bool(*ArestaFn)(Busca* busca, BuscaAresta tipoAresta, int vert, int adjacente);
typedef void(*FechamentoFn)(Busca* busca, int vert);

typedef struct CallbacksType {
	DescobertaFn descoberta;
	ArestaFn aresta;
	FechamentoFn fechamento;
} Callbacks;

void buscaProfundidade(Grafo* grafo, Callbacks calls);

BuscaAresta tipoAresta(Busca* busca, int vert, int adjacente);