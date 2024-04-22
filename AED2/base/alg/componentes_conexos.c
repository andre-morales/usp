#include "componentes_conexos.h"
#include "grafo.h"
#include "busca_profundidade.h"
#include "busca.h"
#include <stdlib.h>
#include <stdio.h>

int maiorTempo(int vec[], int n);

void componentesConexos(Grafo* g) {
	const int numVertices = obtemNrVertices(g);

	Busca busca;
	inicializaBusca(&busca, g);

	// Executa uma busca em profundidade inicial para descobrir os tempos de término de busca
	// para cada vértice
	buscaProfundidade(&busca);

	// Rouba o vetor de tempos e coloca um novo no lugar
	int* tempos = busca.tempoTerm;
	busca.tempoTerm = (int*) malloc(sizeof(int[numVertices]));

	// Inverte todas as arestas do grafo
	transporGrafo(g);
	imprimeGrafo(g);

	int componente = 1;

	while (true) {
		int vert = maiorTempo(tempos, numVertices);
		printf("Tempos: ");
		for (int i = 0; i < numVertices; i++) {
			printf("%i, ", tempos[i]);
		}
		printf("\n");

		if (tempos[vert] == 0) break; 

		printf("\nComponente %i:\n", componente++);

		// Reinicia o estado da busca para fazer uma nova usando o mesmo objeto
		limpaBusca(&busca);

		// Começa uma nova busca em profundidade a partir do vertice de maior tempo
		busca.inicio = vert;
		buscaProfundidade(&busca);

		// Todos os vértices que se tornaram pretos nessa busca fazem parte do mesmo componente
		// conexo.
		for (int i = 0; i < numVertices; i++) {
			// Se o vértice se tornou preto, zera o tempo do vértice para que ele não seja o
			// início da próxima busca
			if (busca.cor[i] == BUSCA_PRETO) {
				tempos[i] = 0;
				printf("%c - ", i + 'a');
			}
		}
		printf("\n");
	}

	free(tempos);
	liberaBusca(&busca);
}

int maiorTempo(int t[], int n) {
	int max = 0;
	for (int i = 1; i < n; i++) {
		if (t[i] > t[max]) {
			max = i;
		}
	}
	return max;
}