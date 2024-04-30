/**
 * Autor: André Morales
 * Criação: 22/04/2024
 * Modificação: 28/04/2024
 * 
 * Implementa um algoritmo capaz de identificar cada componente conexo de um grafo.
 **/
#pragma once

struct GrafoT;
typedef struct GrafoT Grafo;

struct VetorT;
typedef struct VetorT Vetor;

// Identifica os componentes conexos de um grafo.
// O parâmetro compontesPtr, se for NULL indica o desinteresse de obter os vértices de cada componente.
// Se componentesPtr for != NULL, então precisa ser o endereço de um array de vetores
// suficientemente grande para guardar todos os diferentes componentes possíveis.
int componentesConexos(Grafo* grafo, Vetor** componentesPtr);