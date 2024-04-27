#include "vertices_articulacao.h"
#include "componentes_conexos.h"
#include "grafo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void verticesArticulacao(Grafo* g) {
	int numComponentes = componentesConexos(g, NULL);
	printf("INITIAL_COMPS: %i\n", numComponentes);

	int numVerts = obtemNrVertices(g);
	for (int i = 0; i < numVerts; i++) {
		printf(":: Vert %i\n", i);
		Grafo* clone = clonarGrafo(g);

		limparVertice(clone, i);

		// Subtrai-se 1 pois agora isolado é considerado componentes
		int comps = componentesConexos(clone, NULL) - 1;
		if (comps != numComponentes) {
			printf("## ARTI %i: [%i -> %i]\n", i, numComponentes, comps);
		}
		
		liberaGrafo(clone);
		free(clone);
	}
}