/** Programa que exibe na tela dados formatados e ordenados
  * de um arquivo CSV conforme o padr�o:
  *         Series;Value;Time
  *         <int>;<float>;<string>
  *         <int>;<float>;<string>
  */

#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include <time.h>
#include "pilha.h"
#define  NUM 20

int main(){

	int i, esquerda = 0, direita, j,k;
    int num_linhas = 0;
    double time_sec, med=0, med2=0, med3=0;
    float *prize;
    clock_t init_time;
    dado_t **dados;

    for(i = 0; i < NUM; i++)
    {
		num_linhas = 0;

		dados = ler_dados_csv("abacatin.csv", &num_linhas);

		direita = num_linhas -1;

		init_time = clock();

		quicksort(dados, esquerda , direita);

		time_sec = ((double)clock() - init_time);

		med = med + time_sec;

		liberar_dados(dados, direita - esquerda +1);

    }

	 for(i = 0; i < NUM; i++)
    {
		num_linhas = 0;

		dados = ler_dados_csv("abacatin.csv", &num_linhas);

		direita = num_linhas -1;

		pilha_t *pilha_temp = cria_pilha(direita - esquerda +1);

		init_time = clock();

		quicksort_iterativo(dados, pilha_temp, esquerda , direita);

		time_sec = ((double)clock() - init_time);

		med2 = med2 + time_sec;

		/*if(i == NUM - 1)
		{
			 *Imprima os dados*
			for (i=0; i < num_linhas; i++){
					printf(" %d, %s, %.2f, %.2f, %s, %s\n", obter_index(dados[i]), obter_data(dados[i]),obter_prize(dados[i]), obter_total(dados[i]), obter_tipo(dados[i]), obter_regiao(dados[i]));
					//printf( "...", dados[i]->amostra, ... );
				}
		}*/

		liberar_pilha(pilha_temp);
		liberar_dados(dados, direita - esquerda +1);

    }

    for(i = 0; i < NUM; i++)
    {
		num_linhas = 0;

		dados = ler_dados_csv("abacatin.csv", &num_linhas);

		prize = malloc(sizeof(float)*num_linhas);

		for (j=0; j < num_linhas; j++){
            prize[j] = obter_prize(dados[j]);
		}

        init_time = clock();

        qsort(prize, num_linhas -1, sizeof(float), cmp);

		time_sec = ((double)clock() - init_time);

		med3 = med3 + time_sec;

		if(i == NUM - 1)
		{
			 /*Imprima os dados*/
			for (k=0; k < num_linhas-1; k++){
					printf("%.2f\n", prize[k]);
					//printf( "...", dados[i]->amostra, ... );
				}
		}

        free(prize);
        liberar_dados(dados, num_linhas);

    }


    printf("\t\nTempo medio para %d ordenacoes: %f ms",NUM, (med/NUM));
    printf("\t\nTempo medio para %d ordenacoes: %f ms",NUM, (med2/NUM));
    printf("\t\nTempo medio para %d ordenacoes: %f ms",NUM, (med3/NUM));

    return 0;
}
