#include "vetor.h"
#include <stdlib.h>
#include <stdio.h>

void _vetorExpandir(Vetor* vet);

void vetorInicializar(Vetor* vet) {
	vet->dados = NULL;
	vet->tamanho = 0;
	vet->capacidade = 0;
}

void vetorLiberar(Vetor* vet) {
	free(vet->dados);
}

void vetorInserir(Vetor* vet, int item) {
	if (vet->tamanho == vet->capacidade) {
		_vetorExpandir(vet);
	}

	vet->dados[vet->tamanho] = item;
	vet->tamanho++;
}

void vetorLimpar(Vetor* vet) {
	vet->tamanho = 0;
}

void vetorCompactar(Vetor* vet) {
	vet->capacidade = vet->tamanho;
	vet->dados = realloc(vet->dados, vet->capacidade * sizeof(int));
}

void _vetorExpandir(Vetor* vet) {
	if (!vet->dados) {
		vet->capacidade = 1;
	} else {
		vet->capacidade *= 2;		
	}

	int* dados = realloc(vet->dados, vet->capacidade * sizeof(int));
	vet->dados = dados;
}