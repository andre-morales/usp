#include "busca_profundidade.h"
#include "../grafo.h"
#include <stdio.h>

void visitaBP(Grafo*, int, Busca*, int);

// Executa uma busca em profundidade no grafo
void buscaProfundidade(Grafo* g) {
	int numVertices = obtemNrVertices(g);

	// Alocação e inicialização dos estados de cada vértice
	int tempo = 0;
	BuscaCor cor[numVertices];
	int tempoDesc[numVertices];
	int tempoTerm[numVertices];
	int antecessor[numVertices];

	for (int i = 0; i < numVertices; i++) {
		cor[i] = BUSCA_BRANCO;
		tempoDesc[i] = 0;
		tempoTerm[i] = 0;
		antecessor[i] = -1;
	}

	// Estrutura de busca global para o algoritmo
	Busca busca = {
		.tempo = &tempo,
		.cor = cor,
		.tempoDesc = tempoDesc,
		.tempoTerm = tempoTerm,
		.antecessor = antecessor
	};

	// Visita cada vértice
	for (int i = 0; i < numVertices; i++) {
		if (cor[i] == BUSCA_BRANCO) {
			printf("root: \n");
			visitaBP(g, i, &busca, 1);	
		}
	}
}

// Visita um vértice em busca de profundidade.
// grafo: O grafo o qual se deseja fazer a busca
// vert: O vértice a visitar
// b: Estrutura de busca
// prof: Profundidade da busca
void visitaBP(Grafo* grafo, int vert, Busca* b, int prof) {
	// Se o vértice já foi descoberto, não faz nada.
	if (b->cor[vert] != BUSCA_BRANCO) return;

	// Evento de descoberta: o vértice passa a ser cinza, incrementa o relógio global e
	// registra o tempo de descoberta
	b->cor[vert] = BUSCA_CINZA;
	b->tempoDesc[vert] = ++(*b->tempo);

	printf("%*s", prof * 2, "");
	printf("%i: [+] Ini. t: %i\n", vert, b->tempoDesc[vert]);

	// Pega o primeiro vértice alcançável por V para iterar por todos os alcançáveis
	Apontador ap = primeiroListaAdj(grafo, vert);
	while (apontadorValido(ap)) {
		// Obtém o índice do vértice adjacente
		int adjacente = verticeDestino(ap);

		switch (b->cor[adjacente]) {
		// Se o adjacente ainda é branco (não foi descoberto), passamos por uma aresta de árvore.
		// Salva-se o antecessor do adjacente e invoca o algoritmo recursivamente
		case BUSCA_BRANCO:
			printf("%*s", prof * 2, "");
			printf("%i:  => %i ARV\n", vert, adjacente);

			b->antecessor[adjacente] = vert;
			visitaBP(grafo, adjacente, b, prof + 1);
			break;
		// Se o adjacente é cinza, ele ainda está sendo explorado e a aresta de retorno nos leva de
		// volta a esse antecessor.
		case BUSCA_CINZA:
			printf("%*s", prof * 2, "");
			printf("%i:  => %i RET\n", vert, adjacente);
			break;
		// Se o adjacente é preto, ele já foi explorado e pode ser tanto aresta de avanço quanto de cruzamento
		case BUSCA_PRETO:
			// Se o vértice descobridor é mais velho que o descoberto, isso indica uma aresta
			// de avanço, e o vértice adjacente é um descendente
			if (b->tempoDesc[vert] < b->tempoDesc[adjacente]) {
				printf("%*s", prof * 2, "");
				printf("%i:  => %i AVN\n", vert, adjacente);
			// Caso contrário, o descobridor é mais novo que o descoberto e temos uma aresta
			// de cruzamento, onde os dois vértices não tem relação de ancestralidade.
			} else {
				printf("%*s", prof * 2, "");
				printf("%i:  => %i CRZ\n", vert, adjacente);
			}
			break;
		}

		// Avança para o próximo adjacente
		ap = proxListaAdj(grafo, vert, ap);
	}

	// Evento de término: troca a cor do vértice para preto e incrementa o relógio global
	b->cor[vert] = BUSCA_PRETO;
	b->tempoTerm[vert] = ++(*b->tempo);

	printf("%*s", prof * 2, "");
	printf("%i: [-] fim. t: %i\n", vert, b->tempoTerm[vert]);
}
