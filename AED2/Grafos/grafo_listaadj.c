/**
 * Autor: André Morales
 * Criação: 02/04/2024
 * Modificação: 18/04/2024
 * 
 * Implementação das funções base para o grafo por listas de adjacência.
 **/
#define MORE_CHECKS 1
#include "grafo_listaadj.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#if GRAFO_DIRECIONADO
#define TIPO_GRAFO "DIR"
#else
#define TIPO_GRAFO "UND"
#endif


#define GRAFO_INICIALIZADO 0xBBC0FFEE

void extraAssert(bool check);

bool inicializaGrafo(Grafo* grafo, int nv) {
	// Garantindo que o grafo nao foi inicializado antes
	assert(grafo->inicializado != GRAFO_INICIALIZADO);

	if (grafo == NULL) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Grafo não pode ser nulo.\n");
		return false;
	}
	if (nv <= 0) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Vértices tem de ser positivos.\n");
		return false;
	}

	grafo->inicializado = GRAFO_INICIALIZADO;
	grafo->numArestas = 0;
	grafo->numVertices = nv;
	grafo->listaAdj = (Apontador*)calloc(nv, sizeof(Apontador));
	if (!grafo->listaAdj) {
		fprintf(stderr, "ERRO: inicializaGrafo() -- Alocação falhou.\n");
		return false;
	}
	for (int i = 0; i < nv; i++) {
		grafo->listaAdj[i] = NULL;	
	}
	return true;
}

void liberaGrafo(Grafo* g) {
	if (g->inicializado != GRAFO_INICIALIZADO) return;
	g->inicializado = 0;

	for (int v = 0; v < g->numVertices; v++) {
		// Libera toda a lista de adjacência do vértice
		Aresta* aresta = g->listaAdj[v];
		while (aresta) {
			Aresta* prox = aresta->prox;
			free(aresta);
			aresta = prox;
		}
	}

	// Libera o arranjo de todas as listas de adjacência	
	free(g->listaAdj);
}

void imprimeGrafo(Grafo* g) {
	int n = g->numVertices;
	printf("-------- [%i %s %i] --------\n", g->numVertices, TIPO_GRAFO, g->numArestas);
	
	for (int i = 0; i < n; i++) {
		printf("V%i: ", i);
		
		Apontador ap = primeiroListaAdj(g, i);
		while (apontadorValido(ap)) {
			int dest = ap->vdest;
			Peso peso = ap->peso;
			printf("[%i: %i]  ", dest, peso);
			ap = proxListaAdj(g, i, ap);
		}

		printf("\n");
	}
}

int obtemNrVertices(Grafo* grafo) {
	return grafo->numVertices;
}

int obtemNrArestas(Grafo* grafo) {
	return grafo->numArestas;
}

Apontador primeiroListaAdj(Grafo* g, int v) {
	assert(verificaVertice(g, v));

	return g->listaAdj[v];
}

Apontador proxListaAdj(Grafo*, int v, Apontador atual) {
	if (atual == NULL) {
		return VERTICE_INVALIDO;
	}
	
	return atual->prox;
}

bool listaAdjVazia(Grafo* gr, int v) {
	// Assegura a validade do vértice
	assert(verificaVertice(gr, v));

	Aresta* lista = gr->listaAdj[v];
	return !lista;
}

// Insere uma aresta direcionada de V1 para V2 sem verificações. Não incrementa o número de arestas.
void insereArestaImpl(Grafo* g, int v1, int v2, Peso p) {
	// Cria uma aresta de V1 para V2, inserindo a aresta no começo da lista de adjacência
	Aresta* aresta = (Aresta*)malloc(sizeof(Aresta));
	aresta->prox = g->listaAdj[v1];
	aresta->peso = p;
	aresta->vdest = v2;

	g->listaAdj[v1] = aresta;
}

// Obtém o peso de uma aresta direcionada sem realizar verificações
Peso obtemPesoArestaImpl(Grafo* g, int v1, int v2) {
	// Obtém a primeira aresta adjacente de v1
	Aresta* aresta = g->listaAdj[v1];

	// Iteramos todos os adjacentes de v1 para procurar v2
	while (aresta) {
		// Se encontramos a aresta para v2, obtemos o seu peso
		if (aresta->vdest == v2) {
			return aresta->peso;
		}

		// Avança para a próxima aresta
		aresta = aresta->prox;
	}

	// Se passamos todo o laço, não havia aresta entre v1 e v2
	return AN;
}


// Remove uma aresta direcionada de v1 para v2. Sem verificação e sem decréscimo no número de arestas.
// Retorna verdadeiro se a aresta existe, e grava opcionalmente seu peso.
bool removeArestaImpl(Grafo* g, int v1, int v2, Peso* peso) {
	// Busca a presença de V2 na lista de adjacência de V1,
	// vamos iterar a lista de adjacência de v1
	Aresta* ant = NULL;
	Aresta* aresta = g->listaAdj[v1];
	while (aresta) {
		// Se a aresta não aponta para v2, seguimos procurando
		if (aresta->vdest != v2) {
			ant = aresta;
			aresta = aresta->prox;
			continue;
		}

		// Encontramos uma aresta que aponta para v2, salvamos o peso da aresta primeiro
		if (peso) *peso = aresta->peso;
		
		// Se não há anterior, a aresta que vamos remover está no início da lista
		if (!ant) {
			g->listaAdj[v1] = aresta->prox;
		// Caso o contrário ela está no meio da lista mesmo
		} else {
			ant->prox = aresta->prox;
		}

		free(aresta);
		return true;
	}

	// Passamos todo o laço, então não existia aresta entre v1 e v2
	return false;
}

// Se o grafo for direcionado
#if GRAFO_DIRECIONADO
	void insereAresta(Grafo* grafo, int v1, int v2, Peso p) {
		// Garante a validade dos vértices
		assert(verificaVertice(grafo, v1));
		assert(verificaVertice(grafo, v2));

		// Cria uma aresta de V1 para V2
		insereArestaImpl(grafo, v1, v2, p);

		grafo->numArestas++;

		// Verifica se a aresta realmente foi inserida
		extraAssert(existeAresta(grafo, v1, v2));
	}

	Peso obtemPesoAresta(Grafo* grafo, int v1, int v2) {
		// Garante que os vértices são válidos
		assert(verificaVertice(grafo, v1));
		assert(verificaVertice(grafo, v2));

		// Obtém o peso da aresta
		return obtemPesoArestaImpl(grafo, v1, v2);
	}

	bool removeAresta(Grafo* g, int v1, int v2, Peso* p) {
		// Verifica a validade dos vértices
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		// Remove a aresta V1 -> V2
		bool existe = removeArestaImpl(g, v1, v2, p);
		g->numArestas--;
		return existe;
	}
// Se o grafo for não direcionado
#else
	void insereAresta(Grafo* grafo, int v1, int v2, Peso p) {
		// Garante a validade dos vértices
		assert(verificaVertice(grafo, v1));
		assert(verificaVertice(grafo, v2));

		// Cria uma aresta de V1 para V2, e de V2 para V1
		insereArestaImpl(grafo, v1, v2, p);
		insereArestaImpl(grafo, v2, v1, p);

		grafo->numArestas++;

		// Verifica se a aresta realmente foi inserida
		extraAssert(existeAresta(grafo, v1, v2));
	}

	Peso obtemPesoAresta(Grafo* grafo, int v1, int v2) {
		// Garante que os vértices são válidos
		assert(verificaVertice(grafo, v1));
		assert(verificaVertice(grafo, v2));

		// Obtém o peso da aresta
		Peso p = obtemPesoArestaImpl(grafo, v1, v2);
		
		// Garante que o peso da aresta na outra direção é igual ao que encontramos nesta direção
		assert(obtemPesoArestaImpl(grafo, v2, v1) == p);
		return p;
	}

	bool removeAresta(Grafo* g, int v1, int v2, Peso* p) {
		// Verifica a validade dos vértices
		assert(verificaVertice(g, v1));
		assert(verificaVertice(g, v2));

		// Remove a aresta V1 -> V2
		Peso p1 = AN;
		bool existia1 = removeArestaImpl(g, v1, v2, &p1);

		// Remove a aresta V2 -> V1
		Peso p2 = AN;
		bool existia2 = removeArestaImpl(g, v2, v1, &p2);

		// Garanta a integridade do grafo: os pesos e a existência das arestas direcionais devem ser os mesmos
		assert(p1 == p2);
		assert(existia1 == existia2);

		g->numArestas--;

		if (p) *p = p1;
		return existia1;
	}
#endif

// Verifica se existe uma aresta entre v1 e v2. Não faz checks.
bool existeAresta(Grafo* g, int v1, int v2) {
	return obtemPesoAresta(g, v1, v2) != AN;
}

void limparVertice(Grafo* g, int vert) {
	// Limpa a lista de adjacência de vert
	int numAdjacentes = 0;
	int numVizinhos = 0;
	Aresta* ap = g->listaAdj[vert];
	while(ap) {
		Aresta* sv = ap;
		ap = ap->prox;
		free(sv);
		numAdjacentes++;
	}
	g->listaAdj[vert] = NULL;

	// Percorre a lista de adjacência de todos os vértices e verifica se algum deles aponta
	// para vert
	for (int i = 0; i < g->numVertices; i++) {
		Aresta* ant = NULL;
		Aresta* viz = g->listaAdj[i];
		while (viz) {
			Aresta* prox = viz->prox;

			if (viz->vdest == vert) {
				if (ant) {
					ant->prox = viz->prox;
				} else {
					g->listaAdj[i] = viz->prox;
				}

				free(viz);
				numVizinhos++;
			}

			ant = viz;
			viz = prox;
		}
	}

	#if GRAFO_DIRECIONADO
		g->numArestas -= numVizinhos;
		g->numArestas -= numAdjacentes;
	#else
		assert(numVizinhos == numAdjacentes);
		g->numArestas -= numAdjacentes;
	#endif
}

// Cria uma cópia profunda desse grafo
Grafo* clonarGrafo(Grafo* g) {
	Grafo* novo = (Grafo*)malloc(sizeof(Grafo));
	inicializaGrafo(novo, g->numVertices);

	for (int i = 0; i < g->numVertices; i++) {
		Aresta* ar = g->listaAdj[i];
		while (ar) {
			insereArestaImpl(novo, i, ar->vdest, ar->peso);

			ar = ar->prox;
		}
	}

	return novo;
}

bool verificaVertice(Grafo* g, int v) {
	if (v < 0 || v >= g->numVertices) {
		fprintf(stderr, "Vértice [%i] ilegal fora de 0 <= v <= %i\n", v, g->numVertices - 1);
		return false;
	}
	return true;
}

// Extrai o índice do vértice apontado
int verticeDestino(Apontador ap) {
	return ap->vdest;
}

bool apontadorValido(Apontador ap) {
	return ap != NULL;
}

// Realiza uma asserção de condições geralmente raras. Pode ser desabilitado configurando a flag MORE_CHECKS
void extraAssert(bool check) {
	#if MORE_CHECKS
	assert(check);
	#endif
}

bool ehGrafoDirecionado(Grafo* g) {
	#if GRAFO_DIRECIONADO
	return true;
	#else
	return false;
	#endif
}