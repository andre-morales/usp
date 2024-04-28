#include "fila.h"
#include <assert.h>
#include <stdlib.h>

void inicializaFila(Fila* fila) {
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->tamanho = 0;
}

void liberaFila(Fila* fila) {
	NoFila* p = fila->inicio;
	while(p) {
		NoFila* prox = p->prox;
		free(p);
		p = prox;
	}
}

// Insere um item no fim da fila
void insereFila(Fila* fila, int item) {
	// Cria novo nó
	NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
	novo->item = item;
	novo->prox = NULL;

	if (fila->tamanho == 0) {
		// Caso especial de primeira inserção
		fila->inicio = novo;		
	} else {
		// Caso geral
		fila->fim->prox = novo;	
	}
	
	fila->fim = novo;
	fila->tamanho++;
}

// Retira um item do início da fila
int retiraFila(Fila* fila) {
	// Garante que há itens ainda na fila para serem retirados
	assert(fila->tamanho != 0);

	// Adquire o início da fila e o move para trás
	NoFila* no = fila->inicio;
	fila->inicio = no->prox;

	// Adquire o item do nó e o libera
	fila->tamanho--;
	int item = no->item;
	free(no);
	return item;
}
