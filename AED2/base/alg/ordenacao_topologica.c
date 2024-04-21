#include "ordenacao_topologica.h"
#include "busca_profundidade.h"
#include "../grafo.h"
#include <stdio.h>

typedef struct {
	int indice;
	int* vetor;
} BuscaTopl;

void fechamentoAresta(Busca* busca, int vert) {
	printf("VERT: %i\n", vert);
	BuscaTopl* topl = (BuscaTopl*)busca->objeto;
	topl->vetor[topl->indice++] = vert;
}

void ordenarTopologicamente(Grafo* grafo) {
	int numVertices = obtemNrVertices(grafo);
	int topologia[numVertices];

	// Estrutura para a ordenação topológica
	BuscaTopl topl = {
		.indice = 0,
		.vetor = topologia
	};

	// Acessos na busca, só estamos interessados no momento em que um vértice se torna preto
	Callbacks calls = {
		.descoberta = NULL,
		.aresta = NULL,
		.fechamento = fechamentoAresta
	};

	// Executa a busca em profundidade
	buscaProfundidade(grafo, calls, &topl);

	// Imprime o vetor de ordenação em ordem reversa
	int i = numVertices - 1;
	for (; i >= 1; i--) {
		printf("%i - ", topologia[i]);
	}
	printf("%i\n", topologia[i]);
}