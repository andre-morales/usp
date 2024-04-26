#pragma once

typedef struct NoListaT {
	int valor;
	struct NoListaT* prox;
} NoLista;

typedef struct ListaT {
	NoLista* inicio;
	int tamanho;
} Lista;

void inicializaLista(Lista* lista);
void liberaLista(Lista* lista);
void insereLista(Lista* lista, int valor);
int removeLista(Lista* lista);
void limpaLista(Lista* lista);
int elementosLista(Lista* lista, int vetor[], int maxVetor);
int tamanhoLista(Lista* lista);
