#include <stdio.h>
#include <stdbool.h>

typedef struct {
	/// Chave primária do registro
	int numUSP;
	int curso;
	int estado;
	int idade;

	/// Se o registro deve ser eliminado numa operação de limpeza
	bool valido;
} Registro;

typedef enum {
	LEITURA_OK,
	LEITURA_FIM_ARQUIVO,
	LEITURA_ERRO
} StatusLeitura;

StatusLeitura ler_registro(FILE*, Registro*);
void escrever_registro(FILE*, Registro*);
void imprimir_registro(Registro*);

void ex0_leitura_escrita(const char* caminho) {
	// Cria um registro exemplo
	Registro reg1;
	reg1.numUSP = 14558332;
	reg1.curso = 1;
	reg1.estado = 11;
	reg1.idade = 20;
	reg1.valido = true;

	// Escreve o registro no arquivo teste
	FILE* arq1 = fopen(caminho, "w");
	escrever_registro(arq1, &reg1);
	fclose(arq1);

	// Lê o registro 
	Registro reg2;
	FILE* arq2 = fopen(caminho, "r");
	ler_registro(arq2, &reg2);

	// Imprime os resultados
	imprimir_registro(&reg2);
}

void ex1_limpeza(const char* caminho1, const char* caminho2) {
	FILE* entrada = fopen(caminho1, "r");
	FILE* saida = fopen(caminho2, "w");

	while (true) {
		Registro reg;

		if (ler_registro(entrada, &reg) != LEITURA_OK)
			break;

		// Só escreve o registro no arquivo de saída se ele for válido
		// Limpando o arquivo de entrada.
		if (reg.valido) {
			escrever_registro(saida, &reg);
		}
	}

}

void main() {
	const char* const ARQUIVO1 = "teste0.txt";
	const char* const ARQUIVO2 = "teste2.txt";

	//ex0_leitura_escrita(ARQUIVO1);
	ex1_limpeza(ARQUIVO1, ARQUIVO2);
}

// -- Manipulação de Registros

void escrever_registro(FILE* arq, Registro* reg) {
	fprintf(arq, "%i|", reg->numUSP);
	fprintf(arq, "%i|", reg->curso);
	fprintf(arq, "%i|", reg->estado);
	fprintf(arq, "%i|", reg->idade);
	fprintf(arq, "%i|", (int)reg->valido);
}

StatusLeitura ler_registro(FILE* arq, Registro* reg) {
	int read = fscanf(arq, "%i|", &reg->numUSP);
	if (read == EOF) return LEITURA_FIM_ARQUIVO;
	if (read != 1) return LEITURA_ERRO;

	fscanf(arq, "%i|", &reg->curso);
	fscanf(arq, "%i|", &reg->estado);
	fscanf(arq, "%i|", &reg->idade);
	fscanf(arq, "%i|", &reg->valido);
	return LEITURA_OK;
}

void imprimir_registro(Registro* reg) {
	printf("Nro USP: %i\n", reg->numUSP);
	printf("Curso: %i\n", reg->curso);
	printf("Estado: %i\n", reg->estado);
	printf("Idade: %i\n", reg->idade);
	printf("Válido: %s\n", (reg->valido)?"Y":"N");
}