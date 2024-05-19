
/**
 * Exercício-Programa 2. Para a matéria de Introdução a Análise de Algoritmos.
 * Aluno: André Morales de Oliveira Carneiro - xxxxxxxx
 * Data: 26/12/2023
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
	int id;
	int span;
} Update;

typedef struct {
	char type;
	int when;
	int id;
	int span;
} Change;

// -- Assinaturas --
void static_sol(int, char*);
void dynamic_sol(int, char*);
void modifySchedule(Change, Update[], int*);
void genOutput(char*, Update[], int);
void sort_updates(Update[], int);

void readUpdates(FILE*, Update[], int);
int readChanges(FILE*, Change[]);

void print_updates(Update[], int);
void print_changes(Change[], int);
void print_update(Update);
void panic(char*);

// -- Manipulação de Heaps Mínimos --
int heap_left(int);
int heap_right(int);
int heap_parent(int);

void heap_make(Update[], int);
void heap_sift_down(Update[], int, int);
void heap_sift_up(Update[], int, int);
Update heap_extract(Update[], int);
void heap_insert(Update, Update[], int);
void heap_modify_id(int, int, Update[], int);
Update* heap_peek(Update[], int);
bool heap_compare(Update[], int, int);

// Entrada principal do programa.
// O CLI aceita os parâmetros no formato <tempo> <caso> <arquivo>
void main(int argc, char* argv[]) {
	printf("Argumentos: %i\n", argc);

	// Verifica os argumentos
	if (argc != 4) {
		printf("Numero de argumentos incorreto!\n");
		printf("Use como ep <tempo> <caso> <arquivo>\n");
		return;
	}

	// Obtém cada argumento e os converte para inteiro
	char* durationStr = argv[1];
	char* caseStr = argv[2];
	char* file = argv[3];

	int duration = strtol(durationStr, NULL, 10);
	int caseN = strtol(caseStr, NULL, 10);

	// Qual caso a executar
	switch(caseN) {
	case 1:
		static_sol(duration, file);
		break;
	case 2:
		dynamic_sol(duration, file);
		break;
	default:
		panic("Numero de caso invalido!");
	}
}

// Caso estático do problema. Chamar com o tempo que se deseja particionar os updates e um arquivo
// que contenha a descrição dos updates.
void static_sol(int totalTime, char* filePath) {
	// Abre o arquivo
	FILE* file = fopen(filePath, "r");

	// Total de atualizações
	int totalUpdates;
	fscanf(file, "%i", &totalUpdates);

	// Aloca espaço de um heap para as atualizações
	Update updateHeap[200];

	// Lê as atualizações
	readUpdates(file, updateHeap, totalUpdates);
	fclose(file);

	printf("\nAtualizacoes em leitura: %i\n", totalUpdates);
	print_updates(updateHeap, totalUpdates);

	// Organiza os updates no vetor no formato de um heap
	int heapSize = totalUpdates;
	heap_make(updateHeap, heapSize);
	
	printf("\nAtualizacoes em heap: %i\n", totalUpdates);
	print_updates(updateHeap, totalUpdates);

	// Aloca espaço para o planejamento, que são as atualizações que serão feitas e na ordem que serão feitas
	Update plan[100];
	int planSize = 0;

	// Escolhe em sequência as atualizações enquanto houverem, checando sempre pra ver se cabem no tempo restante
	int remainingTime = totalTime;
	while (heapSize > 0) {
		// Observa a próxima atualização
		Update* next = heap_peek(updateHeap, heapSize);
	
		// Se ela não couber no planejamento, saia do loop
		if (next->span > remainingTime) break;

		// Extrai efetivamente o update
		Update up = heap_extract(updateHeap, heapSize);
		heapSize--;

		// Reduza o tempo restante e guarde a atualização no planejamento
		remainingTime -= up.span;
		plan[planSize] = up;
		planSize++;
	}

	// Imprime o resultado
	printf("\nAtualizacoes feitas: %i\n", planSize);
	printf("Tempo gasto: %i\n", totalTime - remainingTime);
	print_updates(plan, planSize);
	genOutput("saida1.txt", plan, planSize);
}

// Caso dinâmico do problema. Chamar com o tempo que se deseja particionar os updates e um arquivo
// que contenha a descrição dos updates.
void dynamic_sol(int totalTime, char* filePath) {
	FILE* file = fopen(filePath, "r");

	// Total de atualizações
	int totalUpdates;
	fscanf(file, "%i", &totalUpdates);

	// Lê as atualizações
	Update updateHeap[200];
	readUpdates(file, updateHeap, totalUpdates);
	
	printf("\nAtualizacoes em leitura: %i\n", totalUpdates);
	print_updates(updateHeap, totalUpdates);

	// Organiza os updates no vetor no formato de um heap
	int heapSize = totalUpdates;
	heap_make(updateHeap, heapSize);

	printf("\nAtualizacoes em heap: %i\n", totalUpdates);
	print_updates(updateHeap, totalUpdates);

	// Lê as mudanças	
	Change changes[100];
	int totalChanges = readChanges(file, changes);
	fclose(file);

	printf("\nMudancas: %i\n", totalChanges);
	print_changes(changes, totalChanges);

	// Aloca espaço para o planejamento, que são as atualizações que serão feitas e na ordem que serão feitas
	Update plan[200];
	int planSize = 0;
	int changeI = 0;

	// Escolhe em sequência as atualizações enquanto houverem, checando sempre pra ver se cabem no tempo restante
	int remainingTime = totalTime;
	int clock = 1;
	int i = 0;
	while (heapSize > 0 && remainingTime > 0) {
		printf("\n:: Volta %i\n", i++);
		printf("Heap: ");
		print_updates(updateHeap, totalUpdates);

		// Verifica se a próxima mudança de itinerário tem que ser feita no atual horário
		while (changeI < totalChanges && changes[changeI].when <= clock) {
			modifySchedule(changes[changeI], updateHeap, &heapSize);
			changeI++;

			printf("Heap! ");
			print_updates(updateHeap, totalUpdates);
		}

		// Observa a próxima atualização
		Update* next = heap_peek(updateHeap, heapSize);
	
		// Se ela não couber no planejamento, incremente o horário
		if (next->span > remainingTime) {
			printf("PASS\n");
			clock++;
			remainingTime--;
			continue;
		}

		// Extrai efetivamente o update
		Update up = heap_extract(updateHeap, heapSize);
		heapSize--;
		printf("Em: ");
		print_update(up);

		// Reduza o tempo restante, avance o relógio e guarde a atualização no planejamento
		remainingTime -= up.span;
		clock += up.span;
		plan[planSize] = up;
		planSize++;
	}

	// Imprime o resultado
	printf("\nAtualizacoes feitas: %i\n", planSize);
	printf("Tempo gasto: %i\n", totalTime - remainingTime);
	print_updates(plan, planSize);	
	genOutput("saida2.txt", plan, planSize);
}

// Executa alguma mudança no heap de atualizações
void modifySchedule(Change c, Update heap[], int* heapSize) {
	char t = c.type;
	
	printf("Mod '%c': When: %i Target: %i Span: %i\n", t, c.when, c.id, c.span);

	// Se vamos fazer a inclusão de uma atualização
	if (t == 'i') {
		Update u;
		u.id = c.id;
		u.span = c.span;

		heap_insert(u, heap, *heapSize);
		(*heapSize)++;
	} else if (t == 'c') {
		heap_modify_id(c.id, c.span, heap, *heapSize);
	} else {
		panic("Tipo de mudanca invalida!");
	}
}

// Gera o arquivo de saída
void genOutput(char* fileName, Update plan[], int n) {
	FILE* file = fopen(fileName, "w");
	fprintf(file, "%i ", n);

	if (n > 0) {
		for (int i = 0; i < n - 1; i++) {
			fprintf(file, "%i ", plan[i].id);
		}
		fprintf(file, "%i", plan[n - 1].id);
	}

	fprintf(file, "\n");
	fclose(file);
}

// Lê as atualizações do arquivo
void readUpdates(FILE* file, Update updates[], int n) {
	// Lê as atualizações
	for (int i = 0; i < n; i++) {
		int id = i + 1;
		int span;
		fscanf(file, "%i", &span);

		updates[i].id = id;
		updates[i].span = span;		
	}

	char line[2];
	fgets(line, 2, file);
}

// Lê o itinerário de mudanças do arquivo
int readChanges(FILE* file, Change changes[]) {
	int n = 0;
	char buffer[128];

	while(true) {
		buffer[0] = '\0';

		Change* c = &changes[n];
		c->span = 0;

		if (!fgets(buffer, 128, file)) break;

		sscanf(buffer, "%c %i %i %i", &c->type, &c->when, &c->id, &c->span);

		if (c->span == 0) break;

		n++;
	}

	return n;
}

// Constrói um heap mínimo de um vetor de updates inteiramente desordenado
void heap_make(Update arr[], int n) {
	int t = n / 2;
	for (int i = t - 1; i >= 0; i--) {
		heap_sift_down(arr, n, i);
	}
}

// Observa a raíz do heap
Update* heap_peek(Update heap[], int n) {
	if (n == 0) panic("Heap underflow!!!");

	return &heap[0];
}

// Extrai a raíz do heap. O heap é automaticamente consertado.
Update heap_extract(Update heap[], int n) {
	if (n == 0) panic("Heap underflow!!!");

	// Tira a raíz do heap (elemento de maior param.)
	Update ext = heap[0];

	// A nova raíz passa a ser a última folha
	heap[0] = heap[n - 1];

	// Conserta a raíz do heap
	heap_sift_down(heap, n - 1, 0);

	return ext;
}

// Inclui um novo elemento no heap. O heap é consertado.
void heap_insert(Update elem, Update heap[], int n) {
	// Inclui o novo elemento
	heap[n] = elem;
	n++;

	// Flui o novo elemento para a posição correta
	heap_sift_up(heap, n, n - 1);
}

// Modifica um nó de ID para ter uma nova duração. O heap é consertado automaticamente.
void heap_modify_id(int id, int newSpan, Update heap[], int heapSize) {
	// Encontra o nó por ID
	int index = -1;
	for (int i = 0; i < heapSize; i++) {
		if (heap[i].id == id) {
			index = i;
			break;	
		}
	}

	if (index == -1) return;

	// Salva a duraççao antiga e faz a modificação
	int oldSpan = heap[index].span;
	heap[index].span = newSpan;

	// Se a duração do nó aumentou, ele precisa fluir para baixo
	if (oldSpan < newSpan) {
		heap_sift_down(heap, heapSize, index);
	}

	// Se a duração do nó diminuiu, ele precisa fluir para cima
	if (oldSpan > newSpan) {
		heap_sift_up(heap, heapSize, index);
	}
}

// Conserta um nó de índice I. Comparando-o com o parâmetro de seus dois filhos.
// Se necessário, conserta os filhos recursivamente.
void heap_sift_down(Update heap[], int heapSize, int i) {
	int left = heap_left(i);
	int right = heap_right(i);
	int smallest = i;

	// Se o filho esquerdo existe e for menor do que o nó atual
	if (left < heapSize && heap_compare(heap, smallest, left)) {
		smallest = left;
	}

	// Se o filho direito existe e for menor do que o nó atual
	if (right < heapSize && heap_compare(heap, smallest, right)) {
		smallest = right;
	}

	// Se realmente houver uma inconsistência, faz a troca entre o pai o filho errado
	if (smallest != i) {
		Update x = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = x;

		// O filho pode ainda estar errado, conserte-o
		heap_sift_down(heap, heapSize, smallest);
	}
}

// Conserta um nó de índice I. Comparando-o com seu pai. Se necessário, conserta
// todos os ancestrais necessários.
void heap_sift_up(Update heap[], int heapSize, int i) {
	if (i == 0) return;

	int parent = heap_parent(i);
	if (!heap_compare(heap, parent, i)) return;

	Update x = heap[i];
	heap[i] = heap[parent];
	heap[parent] = x;

	// O pai pode ainda estar errado, conserte-o
	heap_sift_up(heap, heapSize, parent);
}

// Compara dois nós pai e filho do heap garantidamente existentes,
// retorna verdadeiro se deveriam ser trocados de acordo com 
// a regra de ordenação.
bool heap_compare(Update heap[], int parent, int child) {
	//printf("COMP: %i and %i\n", parent, child);

	Update p = heap[parent];
	Update c = heap[child];

	// A atualização de maior duração deve ir para baixo
	if (c.span < p.span) return true;
	if (c.span > p.span) return false;

	// Se as durações forem iguais, mova para baixo a de ID menor
	return false;
	//return c.id < p.id;
}

int heap_left(int v) { return v * 2 + 1; }

int heap_right(int v) { return v * 2 + 2; }

int heap_parent(int v) { return (v - 1) / 2; }

void print_updates(Update vec[], int n) {
	for (int i = 0; i < n; i++) {
		//printf("[%c: %i] ", 'A' + vec[i].id - 1, vec[i].tempo);
		printf("[#%i: (%i)] ", vec[i].id, vec[i].span);
	}
	printf("\n");
}

void print_changes(Change vec[], int n) {
	for (int i = 0; i < n; i++) {
		//printf("[%c: %i] ", 'A' + vec[i].id - 1, vec[i].tempo);
		printf("[%i@ W: %i, T: %i, S: %i] ", i, vec[i].when, vec[i].id, vec[i].span);
	}
	printf("\n");
}

void print_update(Update u) {
	printf("[ID: #%i, S: %i]\n", u.id, u.span);
}

void panic(char* msg) {
	printf("--- PANIC ---\n");
	printf(":: %s ::\n", msg);

	getchar();
	exit(1);
}

/* Orderna as atualizações em termos de duração, do menor para o maior.
 * Implementa um Selection Sort. 
void sort_updates(Update* vec, int n) {
	for (int t = 0; t < n - 1; t++) {
		int minU = t;

		// Encontra o minimo elemento no subarranjo do final
		for (int k = t + 1; k < n; k++) {
			if (vec[k].span < vec[minU].span) {
				minU = k;
			}
		}

		// Faz a troca
		Update tmp = vec[t];
		vec[t] = vec[minU];
		vec[minU] = tmp;
	}
}*/

// Ordena um heap correto de tamanho N, o próprio vetor do heap é usado como saída da ordenação
/*void heap_sort(Update* heap, int n) {
	for (int i = 0; i < n - 2; i++) {
		int last = n - i - 1;

		// Troca a raíz (maior elemento) com o último elemento do heap
		// O elemento de maior parâmetro vai pro final do vetor e o final
		// do vetor passa a ser ordenado.
		Update x = heap[0];
		heap[0] = heap[last];
		heap[last] = x;

		//Mas a nova raíz em 0 tem que ser consertada.
		heap_fixNode(heap, n - i - 1, 0);
	}
}*/


