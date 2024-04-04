#include <stdio.h>
#include "grafo_matrizadj.h"

void main() {
	Grafo g;
	inicializaGrafo(&g, 10);

	insereAresta(1, 2, 4, &g);

	imprimeGrafo(&g);
}