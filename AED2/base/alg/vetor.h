#pragma once

struct VetorT;
typedef VetorT Vetor;

typedef struct VetorT {
	int* dados;
	int tamanho;
} Vetor;

void vetorInicializar(Vetor* vet);
void vetorLiberar(Vetor* vet);
void vetorInserir(Vetor* vet, int n);
void vetorLimpar(Vetor* vet);