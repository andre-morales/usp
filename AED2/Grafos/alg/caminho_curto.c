#include "ordenacao_topologica.h"
#include "busca_largura.h"
#include "../grafo.h"
#include "busca.h"
#include <stdio.h>
#include <stdlib.h>

int* caminhoCurto(Grafo* grafo, int origem, int destino) {
	// Inicializa estrutura de busca
	Busca busca;
	buscaInicializar(&busca, grafo);

	// Configura a busca para iniciar no vértice de origem
	busca.inicio = origem;

	// Executa a busca em largura
	buscaLargura(&busca);

	// Se o vértice destino não foi descoberto, não há caminho entre os dois
	if (busca.tempoDesc[destino] == 0) return NULL;

	// Aloca espaço suficiente para qualquer caminho
	int caminho[obtemNrVertices(grafo)];

	// Começamos no vértice destino e iteramos de antecessor a antecessor até encontrarmos
	// o vértice origem.
	int tamanho = 0;
	int cur = destino;
	while(true) {
		// Anotamos o antecessor e verificamos se o caminho chegou na origem
		caminho[tamanho++] = cur;
		if (cur == origem) break;

		// Avança para o próximo antecessor
		cur = busca.antecessor[cur];
	}

	// Alocamos espaço para o caminho e o invertemos
	int* caminhoVert = (int*)malloc(sizeof(int[tamanho + 1]));
	for (int i = 0; i < tamanho; i++) {
		caminhoVert[i] = caminho[tamanho - i - 1];
	}
	caminhoVert[tamanho] = -1;
	return caminhoVert;
}