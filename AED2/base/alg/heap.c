#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void heapMake(Heap*);
void heapSiftDown(Heap*, int);
void heapSiftUp(Heap*, int);
int extrairHeap(Heap*);
void heapInsert(Heap*, int);
int heapPeek(Heap*);
bool heapCompare(Heap*, int, int);
int heapLeft(int v);
int heapRight(int v);
int heapParent(int v);

void heapInit(Heap* h, int* pesos, int tamanho) {
	h->vetor = (int*) malloc(sizeof(int[tamanho]));
	h->tamanho = tamanho;
	h->tamanhoMax = tamanho;
	h->pesos = pesos;
	for (int i = 0; i < tamanho; i++) {
		h->vetor[i] = i;
	}

	heapMake(h);
}

// Constrói um heap mínimo de um vetor de updates inteiramente desordenado
void heapMake(Heap* h) {
	int n = h->tamanho;
	int t = n / 2;
	for (int i = t - 1; i >= 0; i--) {
		printf("(%i)\n", i);
		heapSiftDown(h, i);
	}
}

// Observa a raíz do heap
int heapPeek(Heap* heap) {
	assert(heap->tamanho != 0);

	return heap->vetor[0];
}

// Extrai a raíz do heap. O heap é automaticamente consertado.
int heapExtrair(Heap* h) {
	assert(h->tamanho != 0);

	int* heap = h->vetor;
	int n = h->tamanho;

	// Tira a raíz do heap (elemento de maior param.)
	int ext = heap[0];

	// A nova raíz passa a ser a última folha
	heap[0] = heap[n - 1];

	h->tamanho--;

	// Conserta a raíz do heap
	heapSiftDown(h, 0);

	return ext;
}

// Inclui um novo elemento no heap. O heap é consertado.
void heapInsert(Heap* h, int elem) {
	assert(h->tamanho < h->tamanhoMax);

	// Inclui o novo elemento
	h->vetor[h->tamanho] = elem;
	h->tamanho++;

	// Flui o novo elemento para a posição correta
	heapSiftUp(h, h->tamanho - 1);
}

// Conserta um nó de índice I. Comparando-o com o parâmetro de seus dois filhos.
// Se necessário, conserta os filhos recursivamente.
void heapSiftDown(Heap* h, int i) {
	int* heap = h->vetor;
	int heapSize = h->tamanho;

	int left = heapLeft(i);
	int right = heapRight(i);

	int smallest = i;

	// Se o filho esquerdo existe e for menor do que o nó atual
	if (left < heapSize && heapCompare(h, smallest, left)) {
		smallest = left;
	}

	// Se o filho direito existe e for menor do que o nó atual
	if (right < heapSize && heapCompare(h, smallest, right)) {
		smallest = right;
	}

	// Se realmente houver uma inconsistência, faz a troca entre o pai o filho errado
	if (smallest != i) {
		int x = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = x;

		// O filho pode ainda estar errado, conserte-o
		heapSiftDown(h, smallest);
	}
}

// Conserta um nó de índice I. Comparando-o com seu pai. Se necessário, conserta
// todos os ancestrais necessários.
void heapSiftUp(Heap* h, int i) {
	if (i == 0) return;

	int parent = heapParent(i);
	if (!heapCompare(h, parent, i)) return;

	// Troca o nó I e seu pai
	int x = h->vetor[i];
	h->vetor[i] = h->vetor[parent];
	h->vetor[parent] = x;

	// O pai pode ainda estar errado, conserte-o
	heapSiftUp(h, parent);
}

// Compara dois nós pai e filho do heap garantidamente existentes,
// retorna verdadeiro se deveriam ser trocados de acordo com 
// a regra de ordenação.
bool heapCompare(Heap* h, int parent, int child) {
	int p = h->vetor[parent];
	int c = h->vetor[child];

	if (h->pesos[c] < h->pesos[p]) return true;
	if (h->pesos[c] > h->pesos[p]) return false;

	return false;
}

void heapPrint(Heap* heap) {
	printf("{");
	int n = heap->tamanho;
	for (int i = 0; i < n; i++) {
		int v = heap->vetor[i];
		int p = heap->pesos[v];
		printf("%i: %i", v, p);

		if (i < n - 1) {
			printf(" | ");
		}
	}
	printf("}\n");
}

int heapLeft(int v) { return v * 2 + 1; }

int heapRight(int v) { return v * 2 + 2; }

int heapParent(int v) { return (v - 1) / 2; }