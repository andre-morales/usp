/** Autor: André Morales
  * No USP: 14558332
  * Data: 28/04/2023
  *
  * # Exercício 4 de Introdução a Programação #
  * Esse programa converte o número 484 em binário e imprime
  * ele na tela. O código foi formatado para facilitar a
  * conversão de outros números
  */

#include <stdio.h>

void main() {
	// Imprime os 4 bits mais significantes do número
	printf("%i", 484/2/2/2/2/2/2/2/2/2/2/2  	 % 2);
	printf("%i", 484/2/2/2/2/2/2/2/2/2/2		 % 2);
	printf("%i", 484/2/2/2/2/2/2/2/2/2			 % 2);
	printf("%i", 484/2/2/2/2/2/2/2/2			 % 2);

	// Imprime os 8 bits menos significantes do número
	printf(" ");
	printf("%i", 484/2/2/2/2/2/2/2				 % 2);
	printf("%i", 484/2/2/2/2/2/2				 % 2);
	printf("%i", 484/2/2/2/2/2					 % 2);
	printf("%i", 484/2/2/2/2					 % 2);
	printf("%i", 484/2/2/2					     % 2);
	printf("%i", 484/2/2					     % 2);
	printf("%i", 484/2						     % 2);
	printf("%i", 484						     % 2);
}