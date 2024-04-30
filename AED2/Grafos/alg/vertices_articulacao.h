#pragma once

struct GrafoType;
typedef struct GrafoType Grafo;

struct VetorT;
typedef struct VetorT Vetor;

// Encontra todos os vértices de articulação do grafo g e os salva no vetor dado.
// Se o vetor for nulo, apenas o número de articuladores é retornado.
int verticesArticulacao(Grafo* g, Vetor* vet);