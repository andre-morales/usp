#include "componentes_conexos.h"
#include "grafo.h"
#include "busca_profundidade.h"
#include "busca.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define QUIET true

int componentesConexosDir(Grafo* g);
int componentesConexosUnd(Grafo* g);
int maiorTempo(int vec[], int n);

static void dlog(const char* fmt, ...);

int componentesConexos(Grafo* g) {
	if (ehGrafoDirecionado(g)) {
		return componentesConexosDir(g);
	} else {
		return componentesConexosUnd(g);
	}
}

// Encontra os componentes conexos de um grafo não direcionado
int componentesConexosUnd(Grafo* g) {
	const int numVertices = obtemNrVertices(g);

	// Objeto de busca que será utilizado para todas as buscas no grafo
	Busca busca;
	inicializaBusca(&busca, g);

	// Vetor de vértices sinalizando se foram explorados ou não
	bool explorados[numVertices];
	for (int i = 0; i < numVertices; i++) {
		explorados[i] = false;
	}

	// Inicializa uma busca em todos os vértices se não foram explorados ainda
	int numComponentes = 0;
	for (int i = 0; i < numVertices; i++) {
		if (explorados[i]) continue;

		// Reinicia a cor de todos os vértices para branco
		dlog("R: %i\n", i);
		limpaBusca(&busca);

		// Executa uma busca a partir de I
		busca.inicio = i;
		buscaProfundidade(&busca);

		// Marca todos os vértices pretos como sendo parte do mesmo componente e como explorados
		for (int k = 0; k < numVertices; k++) {
			if (busca.cor[k] != BUSCA_PRETO) continue;

			dlog("  v: %i\n", k);
			explorados[k] = true;
		}

		numComponentes++;
	}

	liberaBusca(&busca);
	return numComponentes;
}

// Encontra os componentes fortemente conectados de um grafo direcionado
// (( Teste ainda não funcional ))
int componentesConexosDir(Grafo* g) {
#if GRAFO_MATRIZ
	const int numVertices = obtemNrVertices(g);
	
	Busca busca;
	inicializaBusca(&busca, g);

	// Executa uma busca em profundidade inicial para descobrir os tempos de término de busca
	// para cada vértice
	buscaProfundidade(&busca);

	// Rouba o vetor de tempos e coloca um novo no lugar
	int* tempos = busca.tempoTerm;
	busca.tempoTerm = (int*) malloc(sizeof(int[numVertices]));

	// Inverte todas as arestas do grafo
	transporGrafo(g);
	imprimeGrafo(g);

	int componente = 1;

	while (true) {
		int vert = maiorTempo(tempos, numVertices);
		dlog("Tempos: ");
		for (int i = 0; i < numVertices; i++) {
			dlog("%i, ", tempos[i]);
		}
		dlog("\n");

		if (tempos[vert] == 0) break; 

		dlog("\nComponente %i:\n", componente++);

		// Reinicia o estado da busca para fazer uma nova usando o mesmo objeto
		limpaBusca(&busca);

		// Começa uma nova busca em profundidade a partir do vertice de maior tempo
		busca.inicio = vert;
		buscaProfundidade(&busca);

		// Todos os vértices que se tornaram pretos nessa busca fazem parte do mesmo componente
		// conexo.
		for (int i = 0; i < numVertices; i++) {
			// Se o vértice se tornou preto, zera o tempo do vértice para que ele não seja o
			// início da próxima busca
			if (busca.cor[i] == BUSCA_PRETO) {
				tempos[i] = 0;
				dlog("%c - ", i + 'a');
			}
		}
		dlog("\n");
	}

	free(tempos);
	liberaBusca(&busca);
#endif
	return -1;
}

int maiorTempo(int t[], int n) {
	int max = 0;
	for (int i = 1; i < n; i++) {
		if (t[i] > t[max]) {
			max = i;
		}
	}
	return max;
}

static void dlog(const char* fmt, ...) {
	if (QUIET) return;

	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
}