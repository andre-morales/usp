/**
 * Autor: André Morales
 * Criação: 26/04/2024
 * Modificação: 27/04/2024
 * 
 * Algoritmo para identificar os vértices articulação de um grafo. Isto é, os vértices que se
 * fossem removidos do grafo deixariam dois componentes separados.
 **/
#pragma once

struct GrafoT;
typedef struct GrafoT Grafo;
struct VetorT;
typedef struct VetorT Vetor;

// Encontra todos os vértices de articulação do grafo g e os salva no vetor dado.
// Se o vetor for nulo, apenas o número de articuladores é retornado.
int verticesArticulacao(Grafo* grafo, Vetor* vetor);