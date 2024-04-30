/**
 * Autor: André Morales
 * Criação: 19/04/2024
 * Modificação: 23/04/2024
 * 
 * Implementa um algoritmo de identificação e reconhecimento de ciclos em grafos.
 **/
#pragma once
#include <stdbool.h>

struct GrafoT;
typedef struct GrafoT Grafo;

// Verifica se um grafo é cíclio. Imprimindo os ciclos a medida que eles são encontrados.
// Se 'todos' for verdadeiro, todos os ciclos serão identificados. Caso contrário, o algoritmo
// será interrompido no primeiro ciclo.
// Retorna se o grafo é cíclico ou não.
bool ehGrafoCiclico(Grafo* grafo, bool todos);
