#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_TREE_DEG 2

typedef struct TreeNodeT {
	int keys[2 * MIN_TREE_DEG - 1];
	struct TreeNodeT* children[2 * MIN_TREE_DEG];
	int keyCount;
	bool isLeaf;
} TreeNode;

typedef struct {
	TreeNode* root;
} Tree;

int main(int argc, char* argv[]) {
	// Verifica a validade da invocaçao do programa
	if (argc <= 2) {
		printf("%s, %s", argv[1], argv[2]);
		fprintf(stderr, "Argumentos insuficientes. Utilize ./ep <entrada> <saida>.\n");
		return -1;
	}

	// Inicializa a árvore B+
	Tree tree;
	treeInit(&tree);

	char* inputPath = argv[1];
	char* outputPath = argv[2];

	FILE* input = fopen(inputPath, "r");
	while(true) {
		// Lê a instrução atual
		char instrBuffer[16];
		fscanf(input, "%s", instrBuffer);
		char instr = instrBuffer[0];

		// Lê a chave como argumento da instrução, se a instrução pede
		int key = -1;
		if (instr == 'i' || instr == 'r') {
			fscanf(input, "%i", &key);
		}

		printf("I: %s, C: %i\n" , instrBuffer, key);

		if (instr == 'f') break;
	}

	return 0;
}

void treeInit(Tree* tree) {
	TreeNode* root = (TreeNode*) (sizeof(TreeNode));
	root->isLeaf = false;
	root->keyCount = 0;
	tree->root = root;
}

void treePrintNode(TreeNode* node) {
	int c = 0;
	printf("(");
	for (; c < node->keyCount; c++) {
		treePrintNode(node->children[c]);
		printf("%i ", node->keys[c]);
	}
	treePrintNode(node->children[c]);
	printf(")\n");
}

void treePrintAll(Tree* tree) {
	treePrintNode(tree->root);
}
