#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NIL -1

void inicializaUnionFind(DSets* ds, int n) {
	ds->numElementos = n;
	ds->pais = (int*) malloc(sizeof(int[n]));
	ds->alturas = (int*) malloc(sizeof(int[n]));

	for (int i = 0; i < n; i++) {
		ds->pais[i] = NIL;
		ds->alturas[i] = NIL;
	}
}

// INITIALIZE(): Faz todos os elementos do mapa se tornarem conjuntos unitários raízes de si
void dsInitialize(DSets* ds) {
	int num = ds->numElementos;

	for (int i = 0; i < num; i++) {
		dsMakeSet(ds, i);
	}
}

// Make-Set(v):
// Cria um conjunto na estrutura com um único elemento raíz de si mesma
void dsMakeSet(DSets* ds, int vert) {
	int* pais = ds->pais;
	int* alturas = ds->alturas;

	// Garantque que vert não tem um chefe ainda
	assert(pais[vert] == -1);

	// O chefe do vértice é ele mesmo, indicando que ele é um diretor
	pais[vert] = vert;
	alturas[vert] = 0;
}

// Encontra o número do elemento raíz do elemento e.
// Sem executar nenhuma compressão de caminho.
int dsFindSetNoComp(DSets* ds, int vert) {
	int* pais = ds->pais;
	
	// Itera usando v até que ele seja seu próprio pai, indicando que é o elemento raíz
	// que estamos procurando
	int v = vert;
	while (pais[v] != v) {
		v = pais[v];
	}
	return v;
}

// Find-Set(v):
// Encontra o número do elemento raíz do elemento e. Implementa heurística de compressão de caminho.
int dsFindSet(DSets* ds, int v) {
	int* pais = ds->pais;
	
	if (pais[v] != v) {
		pais[v] = dsFindSet(ds, pais[v]);
	}

	return pais[v];
}

// Union(A, B):
// Faz a união dos dois conjuntos que contém v1 e v2. Se algum dos elementos passados
// não for a raíz de suas árvores, seu raíz será encontrada utilizando Find-Set e usada.
void dsUnion(DSets* ds, int v1, int v2) {
	// Encontra o diretor dos dois vértices. Union apenas lida com os vértices diretores
	int d1 = dsFindSet(ds, v1);
	int d2 = dsFindSet(ds, v2);

	// Faz efetivamente a união
	dsLink(ds, d1, d2);
}

// Link(R, S):
// Une os dois conjuntos representados pelas raízes r e s.
// R e S PRECISAM ser raízes.
// Utiliza a heurística de união por posto para nívelar alturas.
void dsLink(DSets* ds, int r, int s) {
	// Vetores
	int* pais = ds->pais;
	int* alturas = ds->alturas;

	// Se as duas raízes tem a mesma altura, prefira a da direita (R) pra ser chefe
	// Logo S ganhará 1 de altura
	if (alturas[r] == alturas[s]) {
		pais[r] = s;
		alturas[s]++;
	// Se R for a mais alta, ela sera chefe de S
	} else if (alturas[r] > alturas[s]) {
		pais[s] = r;
	// Se S for a mais alta, ela será chefe de R
	} else {
		pais[r] = s;
	}
}

void dsImprime(DSets* ds) {
	printf("------------------\n");
	for (int i = 0; i < ds->numElementos; i++) {
		// Se o vértice I não tem chefe ele não existe no mapa
		if (ds->pais[i] == -1) continue;

		int v = i;
		while (v != ds->pais[v]) {
			printf("%i -> ", v);
			v = ds->pais[v];
		}
		printf("[%i]\n", v);
	}
}

void dsImprimeLetras(DSets* ds) {
	printf("------------------\n");
	for (int i = 0; i < ds->numElementos; i++) {
		// Se o vértice I não tem chefe ele não existe no mapa
		if (ds->pais[i] == -1) continue;

		int v = i;
		while (v != ds->pais[v]) {
			printf("%c -> ", 'A' + v);
			v = ds->pais[v];
		}
		printf("[%c]\n", 'A' + v);
	}
}

int c(char c) {
	return c - 'A';
}

void testeUnionFind() {
	DSets dsets;
	DSets* ds = &dsets;
	inicializaUnionFind(ds, 10);

	dsMakeSet(ds, c('A'));
	dsMakeSet(ds, c('B'));
	dsMakeSet(ds, c('C'));
	dsMakeSet(ds, c('D'));
	dsMakeSet(ds, c('E'));
	dsMakeSet(ds, c('F'));
	dsMakeSet(ds, c('G'));
	dsMakeSet(ds, c('H'));

	dsImprimeLetras(ds);

}