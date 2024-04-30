#include "busca.h"
#include "grafo.h"
#include "estr/vetor.h"
#include <stdlib.h>

void buscaInicializar(Busca* b, Grafo* g) {
	int numVertices = obtemNrVertices(g);

	Acessos acessos = { NULL };

	b->grafo = g;
	b->acessos = acessos;
	b->objeto = NULL;
	b->inicio = -1;

	b->cor = (BuscaCor*)malloc(sizeof(BuscaCor[numVertices]));
	b->tempoDesc = (int*)malloc(sizeof(int[numVertices]));
	b->tempoTerm = (int*)malloc(sizeof(int[numVertices]));
	b->antecessor = (int*)malloc(sizeof(int[numVertices]));
	b->distancia = (int*)malloc(sizeof(int[numVertices]));

	buscaLimpar(b);
}

void buscaLiberar(Busca* b) {
	free(b->cor);
	free(b->tempoDesc); 
	free(b->tempoTerm); 
	free(b->antecessor);
	free(b->distancia); 
}

void buscaLimpar(Busca* b) {
	Grafo* g = b->grafo;
	int numVertices = obtemNrVertices(g);

	b->tempo = 0;

	for (int i = 0; i < numVertices; i++) {
		b->cor[i] = BUSCA_BRANCO;
		b->tempoDesc[i] = 0;
		b->tempoTerm[i] = 0;
		b->antecessor[i] = -1;
		b->distancia[i] = -1;
	}
}

int buscaObterCaminho(Busca* busca, int vert, Vetor* vetor) {
	int nv = obtemNrVertices(busca->grafo);

	int caminhoRev[nv];
	int tamanho = 0;
	int atual = vert;
	while (atual != -1) {
		caminhoRev[tamanho] = atual;
		atual = busca->antecessor[atual];
		tamanho++;
	}

	if (vetor) {
		for (int i = 0; i < tamanho; i++) {
			vetorInserir(vetor, caminhoRev[tamanho - i - 1]);
		}
	}

	return tamanho;
}
