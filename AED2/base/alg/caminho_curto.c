#include "ordenacao_topologica.h"
#include "busca_largura.h"
#include "../grafo.h"
#include "busca.h"
#include <stdio.h>
#include <stdlib.h>

int* caminhoCurto(Grafo* grafo, int origem, int destino) {
	// Inicializa estrutura de busca
	Busca busca;
	inicializaBusca(&busca, grafo);

	// Configura a busca para iniciar no vértice de origem
	busca.inicio = origem;

	// Executa a busca em largura
	buscaLargura(&busca);

	// Aloca espaço suficiente para qualquer caminho
	int caminho[obtemNrVertices(grafo)];

	// Começamos no vértice destino e iteramos de antecessor a antecessor até encontrarmos
	// o vértice origem.
	int tamanho = 0;
	int cur;
	cur = destino;
	while(true) {
		// Se o antecessor do vértice é inválido. Não há caminho da origem para o destino
		if (cur == -1) {
			printf("Não há caminho de %i para %i\n", origem, destino);
			return NULL;
		}

		// Anotamos o antecessor e verificamos se o caminho chegou na origem
		caminho[tamanho++] = cur;
		if (cur == origem) break;

		// Avança para o próximo antecessor
		cur = busca.antecessor[cur];
	}

	// Alocamos espaço para o caminho e o invertemos
	int* caminhoVert = (int*)malloc(sizeof(int[tamanho]));
	for (int i = 0; i < tamanho; i++) {
		caminhoVert[i] = caminho[tamanho - i - 1];
	}

	// Exibe o caminho descoberto
	printf("[Src: ");
	int i;
	for (i = 0; i < tamanho - 1; i++) {
		printf("%i -> ", caminhoVert[i]);
	}
	printf("%i", caminhoVert[i]);
	printf(" :Dst]\n");

	return caminhoVert;
}