#include "grafo_ciclico.h"
#include "busca_profundidade.h"
#include "busca.h"
#include "../grafo.h"
#include <stddef.h>

// Acesso de aresta do algoritmo de busca em profundidade
bool arestaDescoberta(Busca* busca, BuscaAresta tipoAresta, int vert, int dest) {
	// O ponteiro de objeto da busca aponta para a flag que indica se o grafo for descoberto
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

	Busca busca;
	inicializaBusca(&busca, g);

	// Acessos do algoritmo. Estamos interessados no momento de investigação de uma aresta.
	Acessos acessos = {
		.descoberta = NULL,
		.aresta = &arestaDescoberta,
		.fechamento = NULL
	};
	busca.acessos = acessos;
	busca.objeto = &ciclico;
	buscaProfundidade(&busca);

	return ciclico;
}
