#include <stdio.h>
#include <stdlib.h>

typedef enum {
	NO_COLOR = 0, WHITE = 1, BLACK = 2
} Cor;

void initMatrix(FILE* file);
Cor getSquareColor(int x, int y, int size, int depth);
void _printResult();
int strToInt(char* str);
void _printMatrix();
void _printSizeTable();

char matrix[1024][1024];
int matrixSize;
int whiteSquares[10];
int blackSquares[10];

void main(int argc, char* argv[]) {
	// Teste de sanidade
	if (argc <= 2) {
		printf("ERRO: Poucos argumentos :(");
		return;
	}

	// Argumentos
	char* matrixSizeStr = argv[1];
	char* fileName = argv[2];
	matrixSize = strtol(matrixSizeStr, NULL, 10);

	// Leitura do arquivo
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("ERRO: Arquivo [%s] nao existe.\n", fileName);
		return;
	}

	initMatrix(file);
	
	Cor cor = getSquareColor(0, 0, matrixSize, 0);
	if (cor == WHITE) {
		whiteSquares[0]++;
	}
	if (cor == BLACK) {
		blackSquares[0]++;
	}

	_printResult();
}

void initMatrix(FILE* file) {
	char buffer[1030];

	for (int y = 0; y < matrixSize; y++) {
		fgets(buffer, 1030, file);

		for (int x = 0; x < matrixSize; x++) {
			matrix[y][x] = buffer[x];
		}
	}
}

Cor getSquareColor(int x, int y, int size, int depth) {
	if (size == 1) {
		char c = matrix[y][x];
		if (c == '0') return BLACK;
		if (c == '1') return WHITE;
	}

	int half = size / 2;
	depth++;

	// topo esquerda
	Cor te = getSquareColor(x,        y,        half, depth);

	// baixo esquerda
	Cor be = getSquareColor(x,        y + half, half, depth);

	// baixo direita
	Cor bd = getSquareColor(x + half, y + half, half, depth);

	// topo direita
	Cor td = getSquareColor(x + half, y,        half, depth);

	// se todos os quadrados sao da mesma cor
	if (te == be && te == bd && te == td) {
		return te;
	}

	if (te == WHITE) {	whiteSquares[depth]++; }
	if (be == WHITE) {	whiteSquares[depth]++; }
	if (bd == WHITE) {	whiteSquares[depth]++; }
	if (td == WHITE) {	whiteSquares[depth]++; }

	if (te == BLACK) {	blackSquares[depth]++; }
	if (be == BLACK) {	blackSquares[depth]++; }
	if (bd == BLACK) {	blackSquares[depth]++; }
	if (td == BLACK) {	blackSquares[depth]++; }

	return NO_COLOR;
}

void _printResult() {
	int t = matrixSize;
	int i = 0;

	while (t >= 1) {
		int b = whiteSquares[i];
		int p = blackSquares[i];

		printf("%ix%i %i %i\n", t, t, b, p);

		i++;
		t /= 2;
	}
}


void _printMatrix() {
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < matrixSize; x++) {
			printf("%c ", matrix[y][x]);
		}

		printf("\n");
	}
}

void _printSizeTable() {
	int t = matrixSize;
	int i = 0;

	printf("-- Quadrados Brancos -- \n");
	while (t >= 1) {
		int q = whiteSquares[i];
		printf("  %ix%i: %i\n", t, t, q);

		i++;
		t /= 2;
	}

	t = matrixSize;
	i = 0;

	printf("-- Quadrados Pretos -- \n");
	while (t >= 1) {
		int q = blackSquares[i];
		printf("  %ix%i: %i\n", t, t, q);

		i++;
		t /= 2;
	}
}

