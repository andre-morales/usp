#include <stdio.h>

int calculaMDC(int x, int y) {
	// Menor número entre os dois
	int menor = (x < y) ? x : y;
	
	// Iteramos até o 1, se não encontrarmos num divisor até lá,
	// o 1 certamente será um divisor comum dos dois.
	for (int d = menor; d >= 1; d--) {
		// Se X é divisível por D ao mesmo tempo que Y é divisível por D
		if (x % d == 0 && y % d == 0) {
			return d;
		}
		
	}
	return 0;
}

int main() {
	int a, b, mdc;
	printf("Entre com dois valores separados por espaço, enter ou tab:\n");
	scanf("%d %d", &a, &b);

	mdc = calculaMDC(a,b);
	printf("O MDC entre %d e %d é: %d\n", a, b, mdc);

	return 0;
}