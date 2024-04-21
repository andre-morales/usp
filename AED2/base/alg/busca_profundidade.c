#include "busca_profundidade.h"
#include "../grafo.h"
#include <stdio.h>

// Identifica o tipo de uma aresta
BuscaAresta tipoAresta(Busca* busca, int vert, int adjacente);

// Passo da busca
void visitaBP(Grafo*, Busca*, int, int);

// Executa uma busca em profundidade no grafo
void buscaProfundidade(Grafo* g, Acessos acessos, void* objeto) {
	int numVertices = obtemNrVertices(g);

	// Alocação e inicialização dos estados de cada vértice
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

	// Estrutura global de busca para o algoritmo
	Busca busca = {
		.acessos = &acessos,
		.objeto = objeto,
		.tempo = 0,
		.cor = cor,
		.tempoDesc = tempoDesc,
		.tempoTerm = tempoTerm,
		.antecessor = antecessor
	};

	// Visita cada vértice se ele não foi visitado ainda
	for (int i = 0; i < numVertices; i++) {
		if (cor[i] == BUSCA_BRANCO) {
			printf("root: \n");
			visitaBP(g, &busca, i, 1);	
		}
	}
}

// Visita um vértice em busca de profundidade.
// grafo: O grafo o qual se deseja fazer a busca
// b: Estrutura global de busca
// vert: O vértice a visitar
// prof: Profundidade da busca
void visitaBP(Grafo* grafo, Busca* b, int vert, int prof) {
	// Se o vértice já foi descoberto, não faz nada.
	if (b->cor[vert] != BUSCA_BRANCO) return;

	// -- EVENTO DESCOBERTA: O vértice passa a ser cinza, incrementa o relógio global e
	// registra o tempo de descoberta
	b->cor[vert] = BUSCA_CINZA;
	b->tempoDesc[vert] = ++b->tempo;

	printf("%*s", prof * 2, "");
	printf("%i: [+] Ini. t: %i\n", vert, b->tempoDesc[vert]);
	if (b->acessos->descoberta) {
		b->acessos->descoberta(b, vert);
	}

	// Pega o primeiro vértice alcançável por V para iterar por todos os alcançáveis
	Apontador ap = primeiroListaAdj(grafo, vert);
	for (; apontadorValido(ap); ap = proxListaAdj(grafo, vert, ap)) {
		// Obtém o índice do vértice adjacente
		int adjacente = verticeDestino(ap);

		// Identifica o tipo de aresta de V -> A baseado no estado atual da busca
		BuscaAresta tAresta = tipoAresta(b, vert, adjacente);

		// -- EVENTO ARESTA: Notifica-se o acesso.
		// Se ele determinar que não devemos seguir essa aresta, nós a pulamos
		if (b->acessos->aresta) {
			bool seguir = b->acessos->aresta(b, tAresta, vert, adjacente);
			if (!seguir) continue;
		}

		switch (tAresta) {
		case ARESTA_ARVORE:
			printf("%*s", prof * 2, "");
			printf("%i:  => %i ARV\n", vert, adjacente);
			break;
		case ARESTA_RETORNO:
			printf("%*s", prof * 2, "");
			printf("%i:  => %i RET\n", vert, adjacente);
			break;
		case ARESTA_AVANCO:
			printf("%*s", prof * 2, "");
			printf("%i:  => %i AVN\n", vert, adjacente);
			break;
		case ARESTA_CRUZAMENTO:
			printf("%*s", prof * 2, "");
			printf("%i:  => %i CRZ\n", vert, adjacente);
			break;
		}

		// Se o vértice ainda não foi descoberto, salva-se o antecessor do adjacente e invoca
		// o algoritmo recursivamente
		if (b->cor[adjacente] == BUSCA_BRANCO) {
			b->antecessor[adjacente] = vert;
			visitaBP(grafo, b, adjacente, prof + 1);
		}
	}

	// -- EVENTO FECHAMENTO: Troca a cor do vértice para preto e incrementa o relógio global
	b->cor[vert] = BUSCA_PRETO;
	b->tempoTerm[vert] = ++b->tempo;

	printf("%*s", prof * 2, "");
	printf("%i: [-] fim. t: %i\n", vert, b->tempoTerm[vert]);
	if (b->acessos->fechamento) {
		b->acessos->fechamento(b, vert);
	}
}

BuscaAresta tipoAresta(Busca* busca, int vert, int adjacente) {
	BuscaCor cor = busca->cor[adjacente];

	// Se o adjacente ainda é branco (não foi descoberto), passamos por uma aresta de árvore.
	if (cor == BUSCA_BRANCO) return ARESTA_ARVORE;

	// Se o adjacente é cinza, ele ainda está sendo explorado e a aresta de retorno nos leva de
	// volta a esse antecessor.
	if (cor == BUSCA_CINZA) return ARESTA_RETORNO;
	
	// Se o adjacente é preto, ele já foi explorado e pode ser tanto aresta de avanço quanto de cruzamento
	// Se o vértice descobridor é mais velho que o descoberto, isso indica uma aresta
	// de avanço, e o vértice adjacente é um descendente
	if (busca->tempoDesc[vert] < busca->tempoDesc[adjacente]) {
		return ARESTA_AVANCO;
	}

	// Caso contrário, o descobridor é mais novo que o descoberto e temos uma aresta
	// de cruzamento, onde os dois vértices não tem relação de ancestralidade.
	return ARESTA_CRUZAMENTO;
}