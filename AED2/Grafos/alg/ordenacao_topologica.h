/**
 * Autor: André Morales
 * Criação: 20/04/2024
 * Modificação: 21/04/2024
 * 
 * Implementa um algoritmo para ordenar topologicamente um grafo utilizando busca em profundidade.
 **/
#pragma once

struct GrafoT;
typedef struct GrafoT Grafo;

// Imprime a ordenação topológica do grafo dado
void ordenarTopologicamente(Grafo* grafo);