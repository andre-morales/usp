#include "busca.h"
#include "grafo.h"
#include <stdlib.h>

void inicializaBusca(Busca* b, Grafo* g) {
	int numVertices = obtemNrVertices(g);

	Acessos acessos = { NULL };

	b->grafo = g;
	b->acessos = acessos;
	b->objeto = NULL;
	b->tempo = 0;
	b->inicio = 0;

	b->cor = (BuscaCor*)malloc(sizeof(BuscaCor[numVertices]));
	b->tempoDesc = (int*)malloc(sizeof(int[numVertices]));
	b->tempoTerm = (int*)malloc(sizeof(int[numVertices]));
	b->antecessor = (int*)malloc(sizeof(int[numVertices]));
	b->distancia = (int*)malloc(sizeof(int[numVertices]));

	for (int i = 0; i < numVertices; i++) {
		b->cor[i] = BUSCA_BRANCO;
		b->tempoDesc[i] = 0;
		b->tempoTerm[i] = 0;
		b->antecessor[i] = -1;
		b->distancia[i] = -1;
	}
}

void liberaBusca(Busca* b) {
	free(b->cor);
	free(b->tempoDesc); 
	free(b->tempoTerm); 
	free(b->antecessor);
	free(b->distancia); 
}