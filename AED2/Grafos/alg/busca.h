/**
 * Autor: André Morales
 * Criação: 21/04/2024
 * Modificação: 21/04/2024
 * 
 * Define estruturas báscias para execução de buscas em largura ou profundidade em um grafo genérico
 **/
#pragma once
#include "../grafo_fwd.h"
#include <stdbool.h>

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

// Tipo de função acesso para fechamento. Chamado assim que todos os adjacentes de um vértice foram explorados.
typedef void(*FechamentoFn)(Busca* busca, int vert);

// Tipo de função acesso para aresta. Chamado para toda aresta entre o vértice o adjacente.
// Inclui o tipo de aresta que foi identificado.
typedef bool(*ArestaFn)(Busca* busca, BuscaAresta tipoAresta, int vert, int adjacente);

// Objeto container para as três funções de acesso, definidas pelo usuário
struct AcessosType {
	DescobertaFn descoberta;
	FechamentoFn fechamento;
	ArestaFn aresta;
};

// Estrutura global de busca. Individual para cada invocação de busca, mas viva durante toda a busca
struct BuscaType {
	// -- Parâmetros da busca --

	// Grafo alvo da busca
	Grafo* grafo;

	// Acessos da busca. Cada acesso permite observar o estado eventos durante a execução da busca
	// e opcionalmente alterar o seu rumo
	Acessos acessos;

	// Vértice início da busca. Por padrão possui valor -1, mas se configurado, a busca irá
	// explorar apenas o início
	int inicio;

	// Objeto do usuário. Não será alterado ou acessado pelo mecanismo de busca.
	void* objeto;
	
	// -- Estado da busca e resultados --

	// Relógio do algoritmo de busca
	int tempo;

	// Vetor de cores de todos os vértices do grafo
	BuscaCor* cor;

	// Vetor de tempo de descoberta dos vértices
	int* tempoDesc;

	// Vetor do tempo de término dos vértices
	int* tempoTerm;

	// Vetor de antecessores de cada vértice do grafo
	int* antecessor;

	// Vetor de distâncias de cada vértice em relação a raiz da árvore de busca
	int* distancia;
};

void inicializaBusca(Busca* busca, Grafo* grafo);
void limpaBusca(Busca* busca);
void liberaBusca(Busca* busca);