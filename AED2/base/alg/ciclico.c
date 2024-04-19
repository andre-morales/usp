#include "ciclico.h"
#include "busca_profundidade.h"
#include "../grafo.h"
#include <stdio.h>

bool arestaDescoberta(Busca* busca, BuscaAresta tipoAresta, int vert, int dest) {
	// O ponteiro de objeto da busca aponta para a flag que indica se o grafo por descoberto
	// como cíclico
	bool* ciclico = (bool*)busca->objeto;

	// Se o grafo for dado como cíclico, não precisamos seguir mais nenhuma aresta
	if (*ciclico) return false;

	// Se encontramos uma aresta de retorno, o grafo deve ser cíclico
	if (tipoAresta == ARESTA_RETORNO) {
		*ciclico = true;
		return false;
	}

	// Deixamos a aresta ser seguida
	return true;
}

bool ehGrafoCiclico(Grafo* g) {
	bool ciclico = false;

	Callbacks calls = {
		.descoberta = NULL,
		.aresta = &arestaDescoberta,
		.fechamento = NULL
	};
	buscaProfundidade(g, calls, &ciclico);

	return ciclico;
}
