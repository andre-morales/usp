/**
 * Autor: André Morales
 * Criação: 19/04/2024
 * Modificação: 30/04/2024
 * 
 * Expõe o algoritmo para leitura de definição de grafos para arquivos
 **/
#pragma once

struct GrafoT;
typedef struct GrafoT Grafo;

// Lê do arquivo a definição de arestas de um grafo
void leGrafo(Grafo* g, char* arquivo);