#include "busca_profundidade.h"
#include "busca.h"
#include "grafo.h"
#include <stdio.h>
#include <stdarg.h>

// Identifica o tipo de uma aresta
BuscaAresta tipoAresta(Busca* busca, int vert, int adjacente);

// Passo da busca
void visitaBP(Grafo*, Busca*, int, int);

static void dlog(const char* fmt, ...);

// Executa uma busca em profundidade no grafo
void buscaProfundidade(Busca* busca) {
	Grafo* g = busca->grafo;

	int numVertices = obtemNrVertices(g);

	dlog("----- Busca em Profundidade -----\n");

	// Se um início foi dado, visita apenas o início
	if (busca->inicio != -1) {
		dlog("root: \n");
		visitaBP(g, busca, busca->inicio, 1);
	// Visita cada vértice se ele não foi visitado ainda
	} else {
		for (int i = 0; i < numVertices; i++) {
			if (busca->cor[i] == BUSCA_BRANCO) {
				dlog("root: \n");
				visitaBP(g, busca, i, 1);	
			}
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

	dlog("|%*s", prof * 2, "");
	dlog("%i: [+] Ini. t: %i\n", vert, b->tempoDesc[vert]);
	if (b->acessos.descoberta) {
		b->acessos.descoberta(b, vert);
	}

	// Pega o primeiro vértice alcançável por V para iterar por todos os alcançáveis
	Apontador ap = primeiroListaAdj(grafo, vert);
	for (; apontadorValido(ap); ap = proxListaAdj(grafo, vert, ap)) {
		// Obtém o índice do vértice adjacente
		int adjacente = verticeDestino(ap);

		// Identifica o tipo de aresta de V -> A baseado no estado atual da busca
		BuscaAresta tAresta = tipoAresta(b, vert, adjacente);

		// -- EVENTO ARESTA: 
		// Imprime o tipo de aresta que foi encontrada
		switch (tAresta) {
		case ARESTA_ARVORE:
			dlog("|%*s", prof * 2, "");
			dlog("%i:  => %i ARV", vert, adjacente);
			break;
		case ARESTA_RETORNO:
			dlog("|%*s", prof * 2, "");
			dlog("%i:  => %i RET", vert, adjacente);
			break;
		case ARESTA_AVANCO:
			dlog("|%*s", prof * 2, "");
			dlog("%i:  => %i AVN", vert, adjacente);
			break;
		case ARESTA_CRUZAMENTO:
			dlog("|%*s", prof * 2, "");
			dlog("%i:  => %i CRZ", vert, adjacente);
			break;
		}

		// Notifica-se o acesso
		// Se ele determinar que não devemos seguir essa aresta, nós a pulamos
		if (b->acessos.aresta) {
			bool seguir = b->acessos.aresta(b, tAresta, vert, adjacente);
			if (!seguir) {
				dlog(" :: SKIP\n");
				continue;
			}
		}
		dlog("\n");

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

	dlog("|%*s", prof * 2, "");
	dlog("%i: [-] fim. t: %i\n", vert, b->tempoTerm[vert]);
	if (b->acessos.fechamento) {
		b->acessos.fechamento(b, vert);
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

static void dlog(const char* fmt, ...) {
	return;

	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
}