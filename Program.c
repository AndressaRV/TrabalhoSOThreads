//Trabalho SO
//Andressa Rocha Vinhal

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define SEED 13
#define MAX_LINHAS 30000
#define MAX_COLUNAS 30000
#define MAX_RANDOM 99999999
#define MACRO_LINHA 100
#define MACRO_COLUNA 100

typedef struct{
	unsigned long int **dado, linhas, colunas;
} Matriz;

typedef struct{
	unsigned long int comecoLinha, comecoColuna, fimLinha, fimColuna;
} Macrobloco;

Matriz* escolherTamanho(int, int);
Macrobloco* dividirMatriz();
void preencherMatriz();
void numeroThreads();
void executarProgramaSerial();
void executarProgramaParalelo();
void visualizarDados();
void encerrar();
unsigned int verificaPrimo(int);

Matriz *matriz;
Macrobloco *macrobloco;
int contadorPrimosSerial,contadorPrimosParalelo, numThreads;
unsigned int contMacro = 0;
unsigned int gerenciaMacrobloco = 0;
clock_t inicioSerial;
clock_t fimSerial;
clock_t inicioParalelo;
clock_t fimParalelo;

int main ()
{
	
	int opcao, x, y; //x - linhas e y - colunas
    printf("\n1 - Escolher o tamanho da matriz (Maximo 30000 30000) \n");
	printf("2 - Preencher a matriz \n");
	printf("3 - Escolher o numero de threads \n");
	printf("4 - Executar programa de forma serial \n");
	printf("5 - Executar programa de forma paralela(threads) \n");
	printf("6 - Visualizar tempo de execucao e quantidade de numeros primos \n");
	printf("7 - Encerrar programa \n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);

	switch(opcao)
	{
		case 1:
			printf("Digite primeiro o numero de linhas e depois o de colunas: \n");
			scanf("%d", &x);
			scanf("%d", &y);
			if (x > MAX_LINHAS || y > MAX_COLUNAS){
				printf("Numero de linhas ou colunas muito grande (Maximo 30000)");
				main();
			}
			else{
				matriz = escolherTamanho(x, y);
			}

			main();
			break;
		case 2:
			preencherMatriz();
			break;
		case 3:
			numeroThreads();
			main();
			break;
		case 4:
			inicioSerial = clock();
			executarProgramaSerial();
			fimSerial = clock();
			main();
			break;
		case 5:
			macrobloco = dividirMatriz();
			executarProgramaParalelo();
			main();
			break;
		case 6:
			visualizarDados();
			main();
			break;
		case 7:
			encerrar();
			break;
	}
    return 0;
}

Matriz* escolherTamanho(int linha, int coluna)
{
	int i;
	Matriz *matriz = malloc(sizeof(Matriz));

	matriz->dado = malloc(linha * sizeof(int*));

	for (i = 0; i < linha; i++) {
		matriz->dado[i] = malloc(coluna * sizeof(int));
	}

	matriz->linhas = linha;
	matriz->colunas = coluna;

	printf("\nMatriz criada\n");
	return matriz;
}

void preencherMatriz()
{
	srand(SEED);
	int i, j;
	for(i = 0; i<matriz->linhas; i++){
		for(j = 0; j<matriz->colunas; j++){
			matriz->dado[i][j] = rand() % (MAX_RANDOM + 1);
		}
	}
	printf("\nMatriz preenchida\n");
	main();
}

void encerrar()
{
	printf("\nEncerrando o programa...");
	return 0;
}

void visualizarDados()
{
	//impressão serial
	printf("\nNumeros primos na contagem serial: %d", contadorPrimosSerial);
	printf("\nTempo de execucao serial: %lf ", ((double)fimSerial-inicioSerial)/(CLOCKS_PER_SEC));
	printf("segundos\n");
	//impressao paralela
	printf("\nNumeros primos na contagem paralela: %d", contadorPrimosParalelo);
	printf("\nTempo de execucao paralela: %lf ", ((double)fimParalelo-inicioParalelo)/(CLOCKS_PER_SEC));
	printf("segundos\n");

}

void executarProgramaSerial() {
	int i, j;

	for (i = 0; i < matriz->linhas; i++) {
		for (j = 0; j < matriz->colunas; j++) {
			contadorPrimosSerial += verificaPrimo(matriz->dado[i][j]);
		}
	}
	printf("\nCodigo executado\n");
}

unsigned int verificaPrimo(int num)
{
	int i, resultado = 0;
	if (num == 2){
		return 1;
	}
	else if (num < 2 || num % 2 == 0) {
		return 0;
	}
	else{
		for (i = 2; i <= num / 2; i++){
    		if (num % i == 0) {
       		resultado++;
       		break;
   			 }
 		}
 
 	if (resultado == 0)
    	return 1;
 	else
    	return 0;
	}
}

void numeroThreads()
{
	printf("Quantas threads voce quer usar? : ");
	scanf("%d", &numThreads);
	printf("\nNumero definido\n");
}

Macrobloco* dividirMatriz()
{
	Macrobloco *macBloc;
	int macroblocoLinha, macroblocoColuna, macroblocoNumero = 0;

	contMacro = (matriz->linhas * matriz->colunas) / (MACRO_LINHA * MACRO_COLUNA);

	macBloc = malloc(contMacro * sizeof(Macrobloco));

	for (macroblocoLinha = 0; macroblocoLinha < matriz->linhas; macroblocoLinha += MACRO_LINHA) {
		for (macroblocoColuna = 0; macroblocoColuna < matriz->colunas; macroblocoColuna += MACRO_COLUNA, macroblocoNumero += 1) {
			macBloc[macroblocoNumero].comecoLinha = macroblocoLinha;
			macBloc[macroblocoNumero].fimLinha = macroblocoLinha + MACRO_LINHA;
			macBloc[macroblocoNumero].comecoColuna = macroblocoColuna;
			macBloc[macroblocoNumero].fimColuna = macroblocoColuna + MACRO_COLUNA;
		}
	}

	return macBloc;
}

void executarProgramaParalelo()
{
	
}