/**
 * Autor: André Morales
 * Criação: 21/04/2024
 * Modificação: 21/04/2024
 * 
 * Define uma estrutura de Fila de inteiros
 **/
#pragma once

typedef struct self {
	int item;
	struct self* prox;
} NoFila;

typedef struct {
	NoFila* inicio;
	NoFila* fim;
	int tamanho;
} Fila;

void inicializaFila(Fila* fila);

void liberaFila(Fila* fila);

// Insere um item no fim da fila
void insereFila(Fila* fila, int item);

// Retira um item do início da fila
int retiraFila(Fila* fila);
