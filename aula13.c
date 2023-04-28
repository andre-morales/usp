/** Autor: André Morales
  * No USP: 14558332
  * Data: 28/04/2023
  *
  * # Exercício da Aula 13 de Introdução a Programação #
  * Esse programa lê dois números digitados pelo usuário e 
  * diz se eles são pares ou ímpares.
  */

#include <stdio.h>

void parOuImpar(int);

int main() {
	int a, b;
	
	// Pega os dois números e os coloca em A e B respectivamente
	printf("Digite os números: ");
	scanf("%i %i", &a, &b);
	
	// Põe eles na tela
	printf("a = %i; b = %i\n", a, b);
	
	// Código para saber se os números são pares ou ímpares
	printf("A é "
	parOuImpar(a);
	printf(" e B é ");
	parOuImpar(b);
	printf("!");
}

/** Imprime na tela se um número é par ou se ele é ímpar. */
void parOuImpar(int n) {
	// Se o resto da divisão de um número por 2 for 0, ele certamente é par.
	if (n % 2 == 0) {
		printf("par");
	} else {
		printf("ímpar");
	}
}