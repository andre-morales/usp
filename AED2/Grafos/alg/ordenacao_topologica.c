#include "ordenacao_topologica.h"
#include "busca_profundidade.h"
#include "busca.h"
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
	Acessos acessos = {
		.descoberta = NULL,
		.aresta = NULL,
		.fechamento = fechamentoAresta
	};

	Busca busca;
	inicializaBusca(&busca, grafo);

	busca.acessos = acessos;
	busca.objeto = &topl;

	// Executa a busca em profundidade
	buscaProfundidade(&busca);

	// Imprime o vetor de ordenação em ordem reversa
	int i = numVertices - 1;
	for (; i >= 1; i--) {
		printf("%i - ", topologia[i]);
	}
	printf("%i\n", topologia[i]);
}