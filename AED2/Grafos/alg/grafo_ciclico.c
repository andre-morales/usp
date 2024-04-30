/**
 * Autor: André Morales
 * Criação: 19/04/2024
 * Modificação: 23/04/2024
 * 
 * Implementa um algoritmo de identificação e reconhecimento de ciclos em grafos.
 **/
#include "grafo_ciclico.h"
#include "busca_profundidade.h"
#include "busca.h"
#include "../grafo.h"
#include <stdio.h>

// Objeto de busca
typedef struct {
	// Se parar for verdadeiro, o algoritmo irá identificar o primeiro ciclo (se existente) e
	// parar imediatamente. Caso contrário, identificará todos os ciclos do grafo
	bool parar;

	// Será verdadeiro se o grafo foi identificado como cíclico
	bool ciclico;
} BuscaCiclico;

// Acesso de aresta do algoritmo de busca em profundidade
bool arestaDescoberta(Busca* busca, BuscaAresta tipoAresta, int vert, int dest) {
	// O ponteiro de objeto da busca aponta para a estrutura BuscaCiclico que configuramos no
	// começo do teste
	BuscaCiclico* obj = (BuscaCiclico*)busca->objeto;

	// Se o grafo já foi dado como cíclico e configuramos para parar na primeira descoberta,
	// não precisamos seguir mais nenhuma aresta
	if (obj->ciclico && obj->parar) return false;

	// Qualquer aresta que não é de retorno pode ser processada e não nos interessa
	if (tipoAresta != ARESTA_RETORNO) return true;

	// Se encontramos uma aresta de retorno, o grafo só pode ser cíclico
	obj->ciclico = true;

	// Imprime a ponta de destino dessa aresta de retorno
	printf("\n\n(LOOP) [%i: < ", dest);
	
	// Vamos seguir iterando todos os antecessores do vértice fonte dessa aresta, eventualmente
	// encontraremos o vértice destino dessa aresta
	int p = vert;
	while (p != dest) {
		printf("%i < ", p);
		p = busca->antecessor[p];
	}

	printf(":%i]\n", dest);

	return true;
}

bool ehGrafoCiclico(Grafo* g, bool todos) {
	Busca busca;
	buscaInicializar(&busca, g);

	// Acessos do algoritmo. Estamos interessados no momento de investigação de uma aresta.
	busca.acessos.aresta =  &arestaDescoberta;

	// Inicialização do objeto de busca.
	BuscaCiclico objeto;
	objeto.parar = !todos; 
	objeto.ciclico = false;
	busca.objeto = &objeto;

	buscaProfundidade(&busca);

	buscaLiberar(&busca);

	return objeto.ciclico;
}
