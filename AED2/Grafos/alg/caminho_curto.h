#pragma once
#include "../grafo_fwd.h"

// Busca o caminho mais curto entre origem e destino, passando pelo menor número de arestas
// possível. Se nenhum caminho existe, retorna NULL.
// O vetor é alocado pelo algoritmo e a liberação da alocação fica a critério do usuário.
// O vetor possui tamanho estritamente necessário para conter os vértices necessários, mais 
// um sentinela -1 para indicar o fim do caminho.
int* caminhoCurto(Grafo* grafo, int origem, int destino);