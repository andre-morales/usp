#include "busca_largura.h"
#include "../grafo.h"
#include "fila.h"
#include <stdio.h>

// Passo da busca
void visitaBL(Grafo*, Busca*, int);

// Executa uma busca em profundidade no grafo
void buscaLargura(Grafo* g, Acessos acessos, void* objeto) {
	int numVertices = obtemNrVertices(g);

	// Alocação e inicialização dos estados de cada vértice
	BuscaCor cor[numVertices];
	int tempoDesc[numVertices];
	int tempoTerm[numVertices];
	int antecessor[numVertices];
	int distancia[numVertices];

	for (int i = 0; i < numVertices; i++) {
		cor[i] = BUSCA_BRANCO;
		tempoDesc[i] = 0;
		tempoTerm[i] = 0;
		antecessor[i] = -1;
		distancia[i] = -1;
	}

	// Estrutura global de busca para o algoritmo
	Busca busca = {
		.acessos = &acessos,
		.objeto = objeto,
		.tempo = 0,
		.cor = cor,
		.tempoDesc = tempoDesc,
		.tempoTerm = tempoTerm,
		.antecessor = antecessor,
		.distancia = distancia
	};

	Fila fila;
	inicializaFila(&fila);

	/*insereFila(&fila, 4);
	insereFila(&fila, 5);
	insereFila(&fila, 6);
	insereFila(&fila, 7);

	printf("%i\n", retiraFila(&fila));
	printf("%i\n", retiraFila(&fila));
	printf("%i\n", retiraFila(&fila));
	printf("%i\n", retiraFila(&fila));

	insereFila(&fila, 8);
	insereFila(&fila, 9);
	printf("%i\n", retiraFila(&fila));
	printf("%i\n", retiraFila(&fila));
	insereFila(&fila, 10);
	insereFila(&fila, 11);
	printf("%i\n", retiraFila(&fila));
	printf("%i\n", retiraFila(&fila));*/

	// Visita cada vértice se ele não foi visitado ainda
	for (int i = 0; i < numVertices; i++) {
		// Se o vértice já foi descoberto, não faz nada
		if (cor[i] != BUSCA_BRANCO) continue;

		// Enquanto houver vértices na fila, visite eles
		printf("root: \n");
		visitaBL(g, &busca, i);
	}
}

// Visita um vértice em busca de largura. Essa função não é recursiva como a busca em profundidade.
// Ela visitará todos os vértices alcançáveis pela raiz.
//
// grafo: O grafo o qual se deseja fazer a busca
// b: Estrutura global de busca
// raiz: O vértice a visitar
void visitaBL(Grafo* grafo, Busca* b, int raiz) {
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
}
