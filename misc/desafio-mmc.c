#include <stdio.h>

int calculaMMC(int x, int y) {
	// Acumulamos os fatores nessa variável
	int fator = 1;
	printf("1");
	
	// Enquanto os dois numeros forem maiores que 1, continuamos fatorando.
	while (x > 1 || y > 1) {
		
		// Procurando um divisor que divida pelo menos um dos numeros
		for (int d = 2; ; d++) {
			if (x % d == 0 || y % d == 0) {
				
				// Se o divisor divide X, divida o X pelo divisor
				if (x % d == 0) x /= d;
				
				// Se o divisor divide Y, divida o Y pelo divisor
				if (y % d == 0) y /= d;
				
				// Acumule a variável fator com o divisor que encontramos
				fator *= d;
				printf(" * %d", d);
				
				// Volte para o laço while da fatoração	
				break;
			}
			
			
		}
	}
	
	printf(" = %d\n", fator);
	return fator;
}

int main() {
	int a, b, mmc;
	printf("Entre com dois valores separados por espaço, enter ou tab:\n");
	scanf("%d %d", &a, &b);

	mmc = calculaMMC(a,b);
	printf("O MMC entre %d e %d é: %d\n", a, b, mmc);

	return 0;
}
