/** Autor: Andr� Morales
  * No USP: 14558332
  * Data: 28/04/2023
  *
  * # Exerc�cio 4 de Introdu��o a Programa��o #
  * Esse programa converte o n�mero 484 em bin�rio e imprime
  * ele na tela. O c�digo foi formatado para facilitar a
  * convers�o de outros n�meros
  */

#include <stdio.h>

void main() {
	// Imprime os 4 bits mais significantes do n�mero
	printf("%i", 484/2/2/2/2/2/2/2/2/2/2/2  	 % 2);
	printf("%i", 484/2/2/2/2/2/2/2/2/2/2		 % 2);
	printf("%i", 484/2/2/2/2/2/2/2/2/2			 % 2);
	printf("%i", 484/2/2/2/2/2/2/2/2			 % 2);

	// Imprime os 8 bits menos significantes do n�mero
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