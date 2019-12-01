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

	int i, esquerda = 0, direita;
    int num_linhas = 0;
    double time_sec, med=0;
    clock_t init_time;
    dado_t **dados;

    for(i = 0; i < NUM; i++)
    {
		num_linhas = 0;

		dados = ler_dados_csv("camera_temp.csv", &num_linhas);

		direita = num_linhas -1;

		pilha_t *pilha_temp = cria_pilha(direita - esquerda +1);

		init_time = clock();

		quicksort_iterativo(dados, pilha_temp, esquerda, direita);

		time_sec = ((double)clock() - init_time);

		med = med + time_sec;

		if(i == NUM - 1)
		{
			 /*Imprima os dados*/
			for (i=0; i < num_linhas; i++){
					printf(" %d, %f, %s\n", obter_amostra(dados[i]), obter_temperatura(dados[i]),obter_tempo(dados[i]));
					//printf( "...", dados[i]->amostra, ... );
				}
		}

		liberar_dados(dados, num_linhas);
		free(pilha_temp);

    }

	printf("\t\nTempo medio para %d ordenacoes: %f ms",NUM, (med/NUM));

    return 0;
}
