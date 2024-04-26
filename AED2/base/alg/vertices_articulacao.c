#include "vertices_articulacao.h"
#include "componentes_conexos.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

void verticesArticulacao(Grafo* g) {
	// Subtrai-se 1 pois o vértice 0 é considerado um componente
	int numComponentes = componentesConexos(g) - 1;
	printf("INITIAL_COMPS: %i\n", numComponentes);

	int numVerts = obtemNrVertices(g);
	for (int i = 0; i < numVerts; i++) {
		printf("----- VERT %i --------\n", i);

		Grafo* clone = clonarGrafo(g);
		
		limparVertice(clone, i);

		// Subtrai-se 2 pois o vértice 0 e o vértice isolado são considerados componentes
		int comps = componentesConexos(clone) - 2;
		if (comps != numComponentes) {
			printf("## comps: %i\n", comps);
		}
		
		liberaGrafo(clone);
		free(clone);
	}
}