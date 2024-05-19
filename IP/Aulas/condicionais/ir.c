#include <stdio.h>

int main() {
	printf("Digite o seu salário: ");
	
	double s;
	scanf("%lf", &s);
	
	printf("A sua alíquota é: ");
	if (s <= 1903.98) {
		printf("[isento]");
	} else if (s <= 2826.65) {
		printf("7,5%%");
	} else if (s <= 3751.05) {
		printf("15%%");
	} else if (s <= 4664.68) {
		printf("22,5%%");
	} else {
		printf("27,5%%");
	}
	
	
}