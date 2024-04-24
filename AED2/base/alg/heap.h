#pragma once
#include <stdbool.h>

typedef struct {
	int* vetor;
	int* pesos;
	int tamanho;
	int tamanhoMax;
} Heap;

void heapInit(Heap* heap, int* pesos, int tamanho);

int heapExtrair(Heap* heap);

void heapPrint(Heap* heap);