#include "le_grafo.h"
#include "../grafo.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

void leGrafo(Grafo* g, char* arquivo) {
	printf("Lendo grafo...\n");

	// Abertura do arquivo
	FILE* str = fopen(arquivo, "r");
	if (!str) {
		fprintf(stderr, "Arquivo '%s' não encontrado.\n", arquivo);
		exit(-1);
		return;
	}

	// Avança todos os comentários no começo do arquivo
	while (true) {
		long pos = ftell(str);
		char ch = fgetc(str); 
		if (ch == '#') {
			char buffer[128];
			fgets(buffer, 128, str);
		} else {
			fseek(str, pos, SEEK_SET);
			break;
		}
	}

	// Lê o cabeçalho do arquivo e cria o grafo
	int numVertices, numArestas;
	fscanf(str, "%i %i", &numVertices, &numArestas);

	inicializaGrafo(g, numVertices);

	// Lê cada aresta
	for (int i = 0; i < numArestas; i++) {
		Peso peso;
		int v1, v2;
		int items = fscanf(str, "%i %i %i", &v1, &v2, &peso);
		if (items < 3) {
			fprintf(stderr, "Fim inesperado do arquivo.\n");
			exit(-1);
		}

		printf("Inserindo aresta %i:%i, peso: %i\n", v1, v2, peso);
		insereAresta(g, v1, v2, peso);
	}

	// Verificações de sanidade
	assert(obtemNrVertices(g) == numVertices);
	assert(obtemNrArestas(g) == numArestas);

	fclose(str);
}