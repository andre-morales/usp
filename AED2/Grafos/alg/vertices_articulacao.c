#include "vertices_articulacao.h"
#include "componentes_conexos.h"
#include "grafo.h"
#include "estr/vetor.h"
#include <stdio.h>
#include <stdlib.h>

int verticesArticulacao(Grafo* g, Vetor* vet) {
	int numComponentes = componentesConexos(g, NULL);
	//printf("INITIAL_COMPS: %i\n", numComponentes);

	int numArticuladores = 0;

	int numVerts = obtemNrVertices(g);
	for (int i = 0; i < numVerts; i++) {
		//printf(":: Vert %i\n", i);
		Grafo* clone = clonarGrafo(g);

		limparVertice(clone, i);

		// Subtrai-se 1 pois agora isolado é considerado componentes
		int comps = componentesConexos(clone, NULL) - 1;
		if (comps > numComponentes) {
			//printf("## ARTI %i: [%i -> %i]\n", i, numComponentes, comps);

			numArticuladores++;
			if (vet) {
				vetorInserir(vet, i);
			}
		}
		
		liberaGrafo(clone);
		free(clone);
	}

	return numArticuladores;
}