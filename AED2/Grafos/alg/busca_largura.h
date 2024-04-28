/**
 * Autor: André Morales
 * Criação: 21/04/2024
 * Modificação: 21/04/2024
 * 
 * Implementação de um algoritmo para busca em largura em um grafo genérico. Direcionado ou não.
 **/
#pragma once

struct BuscaType;
typedef struct BuscaType Busca;

// Executa uma busca em profundidade no grafo dado.
void buscaLargura(Busca* busca);
