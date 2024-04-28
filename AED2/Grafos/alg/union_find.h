/**
 * Autor: André Morales
 * Criação: 23/04/2024
 * Modificação: 23/04/2024
 * 
 * Define a estrutura Union-Find para a manipulação de conjuntos disjuntos (disjoint sets).
 * Mais especificamente, auxilia a manipulação de componentes conexos de um grafo.
 * 
 * Especificação: https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/union-find.html
 **/
#pragma once

typedef struct DSetsType {
	// Número de elementos totais que essa estrutura consegue lidar
	int numElementos;

	// Vetor de pais de cada elemento
	int* pais;

	// Vetor de alturas de cada elemento
	int* alturas;
} DSets;

// Testa o algoritmo de union find
void testeUnionFind();

// Inicializa uma estrutura Union-Find capaz de lidar com n elementos totais.
void inicializaUnionFind(DSets* ds, int n);

// Cria um conjunto na estrutura com um único elemento raíz de si mesma
void dsMakeSet(DSets* ds, int elem);

// Encontra o número do elemento raíz do elemento e.
// Sem executar nenhuma compressão de caminho.
int dsFindSetNoComp(DSets* ds, int e);

// Encontra o número do elemento raíz do elemento e. Executa compressões de caminho.
int dsFindSet(DSets* ds, int e);

// Faz a união dos dois conjuntos que contém v1 e v2. Se algum dos elementos passados
// não for a raíz de suas árvores, seu raíz será encontrada utilizando Find-Set e usada.
void dsUnion(DSets* ds, int v1, int v2);

// Une os dois conjuntos representados pelas raízes d1 e d2.
// D1 e D2 PRECISAM ser raízes.
// Utiliza a heurística união por posto
void dsLink(DSets* ds, int d1, int d2);

// Imprime a sequência de cada elemento
void dsImprime(DSets* ds);