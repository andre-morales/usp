#include "lista.h"
#include <stdlib.h>
#include <assert.h>

void inicializaLista(Lista* lista) {
	lista->tamanho = 0;
	lista->inicio = NULL;
}

void liberaLista(Lista* lista) {
	limpaLista(lista);
}

void insereLista(Lista* lista, int valor) {
	NoLista* no = (NoLista*) malloc(sizeof(NoLista));
	no->valor = valor;
	no->prox = lista->inicio;
	lista->inicio = no;
	lista->tamanho++;
}

int removeLista(Lista* lista) {
	assert(lista->tamanho > 0);

	NoLista* no = lista->inicio;
	lista->inicio = no->prox;
	lista->tamanho--;

	int valor = no->valor;
	free(no);
	return valor;
}

void limpaLista(Lista* lista) {
	NoLista* p = lista->inicio;
	while (p) {
		NoLista* np = p->prox;
		free(p);
		p = np;
	}

	lista->inicio = NULL;
	lista->tamanho = 0;
}

int tamanhoLista(Lista* lista) {
	return lista->tamanho;
}

int elementosLista(Lista* lista, int vetor[], int maxVetor) {
	int tamanho = lista->tamanho;
	int n = (tamanho < maxVetor) ? tamanho : maxVetor;
	
	NoLista* p = lista->inicio;
	for (int i = 0; i < n; i++) {
		assert(p);

		vetor[i] = p->valor;
		p = p->prox;
	}
	return n;
}