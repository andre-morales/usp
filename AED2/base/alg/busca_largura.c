/**
 * Autor: André Morales
 * Criação: 21/04/2024
 * Modificação: 21/04/2024
 * 
 * Implementação de um algoritmo para busca em largura em um grafo genérico. Direcionado ou não.
 **/
#include "busca_largura.h"
#include "../grafo.h"
#include "busca.h"
#include "fila.h"
#include <stdio.h>

// Passo da busca
void visitaBL(Grafo*, Busca*, int);

// Executa uma busca em profundidade no grafo
void buscaLargura(Busca* busca) {
	Grafo* g = busca->grafo;
	int numVertices = obtemNrVertices(g);

	// Evento de início de busca
	if (busca->acessos.inicio) {
		busca->acessos.inicio(busca);
	}

	if (busca->inicio != -1) {
		visitaBL(g, busca, busca->inicio);
	} else {
		for (int i = 0; i < numVertices; i++) {
			visitaBL(g, busca, i);
		}
	}

	// Evento de fim de busca
	if (busca->acessos.fim) {
		busca->acessos.fim(busca);
	}
}

// Visita um vértice em busca de largura. Essa função não é recursiva como a busca em profundidade.
// Ela visitará todos os vértices alcançáveis pela raiz.
//
// grafo: O grafo o qual se deseja fazer a busca
// b: Estrutura global de busca
// raiz: O vértice a visitar
void visitaBL(Grafo* grafo, Busca* b, int raiz) {
	// Se o vértice já foi descoberto, não faz nada
	if (b->cor[raiz] != BUSCA_BRANCO) return;

	Fila fila;
	inicializaFila(&fila);

	// EVENTO DESCOBERTA (Raíz): O vértice se torna cinza no momento em que é enfileirado
	b->cor[raiz] = BUSCA_CINZA;
	b->tempoDesc[raiz] = ++b->tempo;
	b->distancia[raiz] = 0;
	insereFila(&fila, raiz);

	printf("%i: [+] ROOT. t: %i\n", raiz, b->tempoDesc[raiz]);

	while (fila.tamanho > 0) {
		// Próximo vértice a ser analizado
		int vert = retiraFila(&fila);

		// Distância desse vértice até a raiz
		int distancia = b->distancia[vert];

		// Vamos iterar todos os adjacentes ainda brancos do vértice
		Apontador ap = primeiroListaAdj(grafo, vert);
		for (; apontadorValido(ap); ap = proxListaAdj(grafo, vert, ap)) {
			// Obtém o índice do adjacente, e se o vértice já foi descoberto, pule-o
			int adjacente = verticeDestino(ap);
			if (b->cor[adjacente] != BUSCA_BRANCO) continue;

			// EVENTO DESCOBERTA: O vértice passa a ser cinza assim que for
			// enfileirado.
			b->cor[adjacente] = BUSCA_CINZA;
			b->antecessor[adjacente] = vert;
			b->tempoDesc[adjacente] = ++b->tempo;
			b->distancia[adjacente] = distancia + 1;
			insereFila(&fila, adjacente);

			printf("%i: [+] Ini. t: %i\n", adjacente, b->tempoDesc[adjacente]);
		}

		// EVENTO FECHAMENTO: O vértice se torna preto assim que todos os seus adjacentes foram
		// enfileirados
		b->cor[vert] = BUSCA_PRETO;
		b->tempoTerm[vert] = ++b->tempo;

		printf("%i: [-] Fim. t: %i\n", vert, b->tempoTerm[vert]);
	}

	liberaFila(&fila);
}
