// **************************************************
// *												*
// *												*
// *              EXERCÍCIO PROGRAMA 2 				*
// *												*
// * André Morales de Oliveira Carneiro - xxxxxxxx  *
// *												*
// *												*
// **************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38
#define NumeroMaxJogos NumeroMaxTimes * NumeroMaxRodadas

typedef struct auxtime {
	int pontosGanhos;
	int golsMarcados;
	int golsSofridos;
	int saldoDeGols;
	int vitorias;
	int empates;
	int derrotas;
	float golAverage;
	char nome[31];
} Time;

typedef struct auxjogo {
	char local[30];
	char visitante[30];
	int golsLocal;
	int golsVisitante;
} Jogo;

Time times[NumeroMaxTimes];
Jogo jogos[NumeroMaxJogos];
int noJogos = 0;
int noTimes = 0;

void leNomeTime(char* s);
Time* criaTime(char*);
Time* encontraTime(char*);
void atualizaTime(Time*, int, int);
void criaListaTimes();
void computaDadosTimes();
void ordenaPontos(Time*, int);
void ordenaSaldoGols(Time*, int);
void imprimeClassificacao();
void salvaClassificacao(char*);

int main() {
	int i, golslocal = 0, golsvisitante = 0;
	char local[30];
	char visitante[30];

	printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
	for(i = 0; i < NumeroMaxJogos; ++i) {
		leNomeTime(local);
		leNomeTime(visitante);
		scanf("%d,%d", &golslocal, &golsvisitante);
		getchar(); // consome o enter do scanf

		// printf("local %s visitante %s ", local, visitante);
		// printf("golslocal %d, golsvisitante %d\n", golslocal,golsvisitante);
		if (golslocal < 0)
			break; // termina a entrada de dados

		if(strcmp(local, visitante) == 0)
			continue; // possui o mesmo nome time local e visitante

		strncpy(jogos[i].local, local, 30);
		strncpy(jogos[i].visitante, visitante, 30);

		jogos[i].golsLocal = golslocal;
		jogos[i].golsVisitante = golsvisitante;
	}
	noJogos = i;

	// Confirmando os valores lidos
	// for(i=0; i < nojogos;++i)
	//   printf("%d:%s,%s,%d,%d\n",i+1,jogos[i].local,jogos[i].visitante,jogos[i].golslocal,jogos[i].golsvisitante);

	criaListaTimes();
	// printf("Notimes: %d\n", notimes);
	// printf("\nTimes:\n");
	// for(i=0; i < notimes;++i)
	//   printf("%2d:%s\n",i+1,times[i].nome);

	computaDadosTimes();
	/*printf("\nResultado da computação dos dados dos jogos:\n");
	for(i = 0; i < noTimes; i++) {
	   printf("-- %d:%s\n",i,times[i].nome);
	   printf("Pontos ganhos: %d\n",times[i].pontosGanhos);
	   printf("Gols marcados: %d\n",times[i].golsMarcados);
	   printf("Gols sofridos: %d\n",times[i].golsSofridos);
	   printf("Vitorias: %d\n",times[i].vitorias);
	   printf("Empates: %d\n",times[i].empates);
	   printf("Saldo de gols: %d\n",times[i].saldoDeGols);
	   printf("Gols average: %2.3f\n",times[i].golAverage);
	   printf("\n");
	}*/

	imprimeClassificacao();

	// Opcional
	salvaClassificacao("campeonatoIP.dat");

}

/** Computa dados times */
void computaDadosTimes() {
	// Preenche os campos dos elementos do arranjo timescampeonato: Vitorias,
	// GolsSofridos, GolsMarcados, Golsaverage, SaldoDeGols, PontosGanhos.
	for (int i = 0; i < noJogos; i++) {
		Jogo* jogo = &jogos[i];

		int golsA = jogo->golsLocal;
		int golsB = jogo->golsVisitante;
		Time* timeA = encontraTime(jogo->local);
		Time* timeB = encontraTime(jogo->visitante);

		atualizaTime(timeA, golsA, golsB);
		atualizaTime(timeB, golsB, golsA);
	}	

	ordenaPontos(times, noTimes);

	//imprimeClassificacao();

	// De time em time...
	for (int i = 0; i < noTimes; i++) {

		// Verifica se há uma sequência de times com o mesmo numero de pontos ganhos
		int n = 1;
		for (int k = i + 1; k < noTimes; k++) {
			if (times[i].pontosGanhos == times[k].pontosGanhos) {
				n++;
			} else {
				break;
			}
		}

		// Se houverem de fato 2 ou mais times com a mesma pontuação
		// Ordene-os começando pelo primeiro até o último time com o número repetido
		if (n >= 2) {
			ordenaSaldoGols(&times[i], n);
		}
	}
}

/** Ordena por Pontos de forma decrescente */
void ordenaPontos(Time* arr, int n) {
	// Bubble sort
	int trocou;
	do {
		trocou = 0;

		for (int i = 0; i < n - 1; i++) {
			int pontosA = arr[i + 0].pontosGanhos;
			int pontosB = arr[i + 1].pontosGanhos;

			if (pontosA < pontosB) {
				Time tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;

				trocou = 1;
			}
		}
	} while (trocou);

	// Selection sort
	/*for (int p = 0; p < n - 1; p++) {

		int maxPontos = arr[p].pontosGanhos;
		int maxTime = p;
		for (int i = p; i < n; i++) {
			int pontos = arr[i].pontosGanhos;

			if (pontos >= maxPontos) {
				maxPontos = pontos;
				maxTime = i;
			}
		}

		if (maxTime == p) continue;

		Time tmp = arr[p];
		arr[p] = arr[maxTime];
		arr[maxTime] = tmp;
	}*/
}

/** Ordena por saldo de gols de forma decrescente */
void ordenaSaldoGols(Time* arr, int n) {
	/*// Selection sort
	for (int p = 0; p < n - 1; p++) {

		int maxSaldo = arr[p].saldoDeGols;
		int maxTime = p;
		for (int i = p; i < n; i++) {
			int saldo = arr[i].saldoDeGols;

			if (saldo > maxSaldo) {
				maxSaldo = saldo;
				maxTime = i;
			}
		}

		//if (maxTime == p) continue;

		Time tmp = arr[p];
		arr[p] = arr[maxTime];
		arr[maxTime] = tmp;
	}*/

	// Bubble sort
	int trocou;
	do {
		trocou = 0;

		for (int i = 0; i < n - 1; i++) {
			int pontosA = arr[i + 0].saldoDeGols;
			int pontosB = arr[i + 1].saldoDeGols;

			if (pontosA < pontosB) {
				Time tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;

				trocou = 1;
			}
		}
	} while (trocou);
}

/** Cria um time com o dado nome e retorna um ponteiro para ele */
Time* criaTime(char* nome) {
	Time* time = &times[noTimes];
	strcpy(time->nome, nome);
	time->pontosGanhos = 0;
	time->golsMarcados = 0;
	time->golsSofridos = 0;
	time->saldoDeGols = 0;
	time->vitorias = 0;
	time->empates = 0;
	time->derrotas = 0;
	time->golAverage = 0;

	noTimes++;
	return time;
}



/** Atualiza o status de um time dado os seus gols e os gols do adversário. */
void atualizaTime(Time* time, int gols, int golsAdv) {
	time->golsMarcados += gols;
	time->golsSofridos += golsAdv;
	
	if (gols > golsAdv) {
		time->vitorias++;
		time->pontosGanhos += 3;
	} else if (gols == golsAdv) {
		time->empates++;
		time->pontosGanhos += 1;
	} else {
		time->derrotas++;
	}
	
	time->saldoDeGols = time->golsMarcados - time->golsSofridos;
	
	if (time->golsSofridos != 0) {
		time->golAverage = time->golsMarcados / (float)time->golsSofridos;
	}
}


/** Encontra se o time já está no arranjo de times do campeonato */
Time* encontraTime(char* nome) {
	for (int i = 0; i < noTimes; i++) {
		if (strcmp(times[i].nome, nome) == 0) {
			return &times[i];
		}
	}

	return NULL;
}
/** Cria a lista de times do campeonato a partir dos nojogos */
void criaListaTimes() {
	for (int i = 0; i < noJogos; i++) {
		char* nomeTimeA = jogos[i].local;
		char* nomeTimeB = jogos[i].visitante;
		
		if (!encontraTime(nomeTimeA)) {
			criaTime(nomeTimeA);
		}

		if (!encontraTime(nomeTimeB)) {
			criaTime(nomeTimeB);
		}
	}	
}

void imprimeStreamClassificacao(FILE* str) {
	fprintf(str, "Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average\n");

	for (int i = 0; i < noTimes; i++) {
		Time* time = &times[i];

		int   pos      = i + 1;
		char* nome     = time->nome;
		int   pontos   = time->pontosGanhos;
		int   vitorias = time->vitorias;
		int   empates  = time->empates;
		int   derrotas = time->derrotas;
		int   saldo    = time->saldoDeGols;
		float golAvg   = time->golAverage;

		fprintf(str, "%i,%s,%i,%i,%i,%i,%i,%.3f\n", pos, nome, pontos, vitorias, empates, derrotas, saldo, golAvg);	
	}
}

/** Imprime classificação */
void imprimeClassificacao() {
	imprimeStreamClassificacao(stdout);
}

/** Salva os dados da classificação dos tipos em arquivo no disco */
void salvaClassificacao(char* arquivo){
	FILE* f = fopen(arquivo, "w");
	imprimeStreamClassificacao(f);
	fclose(f);
}

void leNomeTime(char* s) {
	int i;
	s[0] = '\0';

	char c;
	c = getchar();
	for(i = 0; c != ',' && i < 30;++i) {
		s[i] = c;
		c = getchar();
	}
	s[i] = '\0';
}