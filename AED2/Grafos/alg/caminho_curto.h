/**
 * Autor: André Morales
 * Criação: 21/04/2024
 * Modificação: 28/04/2024
 * 
 * Implementa um algoritmo para extrair o caminho mais curto entre dois vértices (origem e destino)
 * em um grafo direcionado ou não direcionado. O caminho mais curto será o camihno que passa pelo
 * menor número de arestas possível.
 **/
#pragma once

struct GrafoT;
typedef struct GrafoT Grafo;

// Busca o caminho mais curto entre origem e destino, passando pelo menor número de arestas
// possível. Se nenhum caminho existe, retorna NULL.
// O vetor é alocado pelo algoritmo e a liberação da alocação fica a critério do usuário.
// O vetor possui tamanho estritamente necessário para conter os vértices necessários, mais 
// um sentinela -1 para indicar o fim do caminho.
int* caminhoCurto(Grafo* grafo, int origem, int destino);