#pragma once
#include "../grafo_fwd.h"

struct AcessosType;
typedef struct AcessosType Acessos;

struct BuscaType;
typedef struct BuscaType Busca;

// Cores possíveis de um vértice durante uma busca.
// BRANCO: Vértice ainda não foi descoberto
// CINZA: Vértice já foi descoberto mas seus adjacentes ainda estão sendo investigados
// PRETO: Vértice já foi investigado e todos seus adjacentes foram explorados
typedef enum {
	BUSCA_BRANCO, BUSCA_CINZA, BUSCA_PRETO
} BuscaCor;

// Tipos possíveis de aresta
// ARVORE: Primeira aresta que levou ao descobrimento de um vértice
// RETORNO: Conecta um vértice mais novo a algum vértice ancestral na árvore de busca
// AVANÇO: Conecta um vértice mais velho a algum descendente na árvore de busca
// CRUZAMENTO: Conecta dois vértices sem ancestralidade
typedef enum {
	ARESTA_ARVORE, ARESTA_RETORNO, ARESTA_AVANCO, ARESTA_CRUZAMENTO
} BuscaAresta;

// Tipo de função acesso de descoberta. Chamado assim que um vértice branco for descoberto
typedef void(*DescobertaFn)(Busca* busca, int vert);

// Tipo de função acesso para aresta. Chamado para toda aresta entre o vértice o adjacente.
// Inclui o tipo de aresta que foi identificado.
typedef bool(*ArestaFn)(Busca* busca, BuscaAresta tipoAresta, int vert, int adjacente);

// Tipo de função acesso para fechamento. Chamado assim que todos os adjacentes de um vértice foram explorados.
typedef void(*FechamentoFn)(Busca* busca, int vert);

// Objeto container para as três funções de acesso, definidas pelo usuário
struct AcessosType {
	DescobertaFn descoberta;
	ArestaFn aresta;
	FechamentoFn fechamento;
};

// Estrutura global de busca. Individual para cada invocação de busca, mas viva durante toda a busca
struct BuscaType {
	Acessos* acessos;
	
	int* tempo;
	BuscaCor* cor;
	int* tempoDesc;
	int* tempoTerm;
	int* antecessor;

	void* objeto;
};

// Executa uma busca em profundidade no grafo dado.
// grafo: Grafo alvo da busca
// acessos: Estrutura de configuração de acessos
// objeto: Um ponteiro opcional acessível durante a busca
void buscaProfundidade(Grafo* grafo, Acessos acessos, void* objeto);
