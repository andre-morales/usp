/**
 * Autor: André Morales
 * Criação: 27/04/2024
 * Modificação: 27/04/2024
 * 
 * Estrutura para vetor de inteiros
 **/
#pragma once

struct VetorT;
typedef struct VetorT Vetor;

typedef struct VetorT {
	int* dados;
	int tamanho;
	int capacidade;
} Vetor;

void vetorInicializar(Vetor* vet);
void vetorLiberar(Vetor* vet);
void vetorInserir(Vetor* vet, int n);
void vetorLimpar(Vetor* vet);
void vetorImprimir(Vetor* vet);
void vetorCompactar(Vetor* vet);
