/*********************************************************************/
/**   ACH2001 - Introducao a Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2022                          **/
/**   Turma 02 - Prof. Marcos Lordello Chaim                        **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <André Morales>             			  <->   		        **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

void printData(int d, int m, int a);
int diasDoMes(int mes, int ano);
int vertificaAnoBissexto(int ano);
int verificaDataValida(int d, int m, int a);
void somaDias(int dias, int* d, int* m, int* a);
void normalizaData(int* d, int* m, int* a);

// Os esportes se encontrarão no mesmo dia só de 60 em 60 dias.
// Esse 60 vem do MMC (mínimo múltiplo comum) das frequências dos
// esportes.
// MMC(2, 3, 4, 5, 6) = 60.
const int intervalo = 60;

//				              JAN FEV MAR ABR MAI JUN JUL AGO SET OCT NOV DEZ
const int diasDosMeses[]   = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int diasDosMesesBi[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
	int dia, mes, ano;

	printf("Entre com a data de inicio do ano letivo:\n");
	printf("Entre com o dia: ");
	scanf("%d", &dia);
	printf("Entre com o mes: ");
	scanf("%d", &mes);
	printf("Entre com o ano: ");
	scanf("%d", &ano);

	if (!verificaDataValida(dia, mes, ano)) {
		printf("Dados incorretos\n");
		
		exit(1); // Esta função aborta a execução do programa.
	}

	int anoInicial = ano;

	while (1) {
		somaDias(intervalo, &dia, &mes, &ano);

		// Assim que a nossa função que soma datas fizer o ano virar, podemos parar
		if (ano != anoInicial) break;

		printf("%i/%i/%i\n", dia, mes, ano);
	}

}

void printData(int d, int m, int a) {
	#ifdef DEBUG
	printf("D: [%i/%i/%i\n", d, m, a);
	#else
	printf("%i/%i/%i\n", d, m, a);
	#endif
}

/** Normaliza uma data virtual como 36/01/2023 para uma data física como 05/02/2023.
  * Essa função leva em consideração anos bissextos. */
void normalizaData(int* d, int* m, int* a) {
	while (1) {
		int diasDesseMes = diasDoMes(*m, *a);

		// Se o número do dia já estiver normal, pare
		if (*d <= diasDesseMes) return;

		// Subtraia o número de dias e incremente o mes
		*d -= diasDesseMes;
		*m += 1;

		// Se o número de meses passar de 12, incremente o ano
		if (*m > 12) {
			*m = 1;
			*a += 1;
		}
	}
}

/** Soma um número de dias a uma data. */
void somaDias(int dias, int* d, int* m, int* a) {
	if (dias < 0) return;

	// Apenas some o número de dias e depois normalize a data
	*d += dias;
	normalizaData(d, m, a);
}


int vertificaAnoBissexto(int ano) {
	// Se não for divisível for 4, nunca será um bissexto
	if (ano % 4 != 0) return 0;

	// Se for divisível por 100, tem que ser divisível for 400 também
	if (ano % 100 == 0) {
		if (ano % 400 == 0) return 1;
		return 0;
	}
}

int verificaDataValida(int d, int m, int a) {
	// Não acho que existiam clubes de fotografia antes de cristo
	if (a < 1) return 0;

	// Mês fora de [1, 12]
	if (m < 1 || m > 12) return 0;

	// Vertificação de sanidade do número do dia
	int dias = diasDoMes(m, a);
	if (d < 1 || d > dias) return 0;

	// Tudo certo.
	return 1;
}

int diasDoMes(int mes, int ano) {
	// Se for um ano bissexto, haverá um dia a mais em fevereiro, usaremos o array diferente
	if (vertificaAnoBissexto(ano)) {
		return diasDosMesesBi[mes - 1];
	} else {
		return diasDosMeses[mes - 1];
	}
}