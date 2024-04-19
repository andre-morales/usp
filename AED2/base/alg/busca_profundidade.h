#pragma once
#include "../grafo_fwd.h"

// Cores possíveis de um vértice durante uma busca.
// BRANCO: Vértice ainda não foi descoberto
// CINZA: Vértice já foi descoberto mas seus adjacentes ainda estão sendo investigados
// PRETO: Vértice já foi investigado e todos seus adjacentes foram explorados
typedef enum {
	BUSCA_BRANCO, BUSCA_CINZA, BUSCA_PRETO
} BuscaCor;

// Tipos possíveis de aresta
typedef enum {
	ARESTA_ARVORE, ARESTA_RETORNO, ARESTA_AVANCO, ARESTA_CRUZAMENTO
} BuscaAresta;

typedef struct {
	struct CallbacksType* calls;
	void* objeto;

	int* tempo;
	BuscaCor* cor;
	int* tempoDesc;
	int* tempoTerm;
	int* antecessor;
} Busca;

// Tipo de callback de descoberta. Chamado assim que um vértice branco for descoberto
typedef void(*DescobertaFn)(Busca* busca, int vert);

// Tipo de callback para aresta. Chamado para toda aresta entre o vértice o adjacente.
// Inclui o tipo de aresta que foi identificado.
typedef bool(*ArestaFn)(Busca* busca, BuscaAresta tipoAresta, int vert, int adjacente);

// Tipo de callback para fechamento. Chamado assim que todos os adjacentes de um vértice foram explorados.
typedef void(*FechamentoFn)(Busca* busca, int vert);

typedef struct CallbacksType {
	DescobertaFn descoberta;
	ArestaFn aresta;
	FechamentoFn fechamento;
} Callbacks;

// Executa uma busca em profundidade no grafo dado. Com callbacks opcionalmente configurados e um
// objeto arbitrário determinado pelo usuário.
void buscaProfundidade(Grafo* grafo, Callbacks calls, void* objeto);
