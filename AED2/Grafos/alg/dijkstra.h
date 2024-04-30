/**
 * Autor: André Morales
 * Criação: 23/04/2024
 * Modificação: 23/04/2024
 * 
 * Algoritmo de Dijkstra para a geração da árvore de caminhos mínimos
 **/
#pragma once
#include <stdbool.h>

struct GrafoT;
typedef struct GrafoT Grafo;

// Definição de Árvore de Caminhos Mínimos
typedef struct {
	// Grafo em análise
	Grafo* grafo;

	// Vértice inicial a ser analisado
	int fonte;

	// Vetor de vértices ativos.
	// Um vértice ativo ainda será analisado pelo algoritmo e será eventualmente extraido por
	// Extract-Min(). Um vértice inativo já foi olhado pelo algoritmo
	bool* verticesAtivos;
	
	// Vetor de distâncias estimadas para cada vértice	
	int* distancia;  // d

	// Antecessor de cada vértice. Seguindo os antecessores recursivamente qualquer vértice
	// levará a fonte
	int* antecessor; // pi
} ACM;

// Inicializa a estrutura para a ACM
void inicializaACM(ACM* acm, Grafo* grafo);

// Executa o algoritmo de Dijkstra
void diCaminhos(ACM* acm, int inicio);

// Imprime o estado da árvore de caminhos mínimos
void diImprime(ACM* acm);
