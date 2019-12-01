
/* de um arquivo CSV conforme o padr�o:
  *         Series;Value;Time
  *         <int>;<float>;<string>
  *         <int>;<float>;<string> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "pilha.h"

struct dados {
    int amostra;        /*!< Identificador num�rido da amostra */
    float temperatura;  /*!< Valor do dado: temperatura */
    char tempo[64];      /*!< Time stamp */
};


dado_t * criar_dado (int amostra, float temperatura, char *tempo){

    dado_t * meu_novo_dado = malloc(sizeof(dado_t));

    if(meu_novo_dado == NULL){
        perror("Erro criar_dado");
        exit(-1);
    }

    // Colocar a cria��o dos dados aqui

    meu_novo_dado->amostra = amostra;
    meu_novo_dado->temperatura = temperatura;
    //meu_novo_dado->tempo] = tempo[64];
    strncpy(meu_novo_dado->tempo, tempo, 64);

    return meu_novo_dado;
}



dado_t **ler_dados_csv(char *nome_do_arquivo, int *num_linhas){
    char texto[64];
    int i=0;
    //int n_linhas=0;
    int amostra;
    float temperatura;

    /* Demais Vari�veis */


    dado_t **dados;

    FILE *fp = fopen(nome_do_arquivo,"r");

    if (!fp){
        perror("ler_dados_csv");
        exit(-1);
    }

    /* Ignora primeira linha */
    fgets(texto,64, fp);

    /* Contar todas as linhas: use while e fgets() */
    while(fgets(texto,64,fp)!=NULL){
        (*num_linhas)++;
    }



    /* Aloque mem�ria:
     * Agora � um vetor de ponteiros */
    dados = malloc(sizeof(dado_t ) * (*num_linhas));

    rewind(fp);
     /* Ignora primeira linha */
    fgets(texto,64, fp);


    while (fscanf (fp, "%d,%f,%63[^\n]", &amostra, &temperatura, texto) == 3){
       // printf("Lido %d, %f, %s\n", amostra, temperatura, texto);

        /* Cria um novo dado abstrato e armazena a sua refer�ncia */
        dados[i] = criar_dado(amostra, temperatura, texto);

        i++;
    }

    fclose(fp);
    //*num_linhas = n_linhas;
    return dados;
}



void liberar_dados(dado_t **vetor, int tamanho){

    int i;

    for (i=0; i < tamanho; i++){
        free(vetor[i]);
    }

    free(vetor);

}

int obter_amostra(dado_t *dado){
    return dado->amostra;
}

float obter_temperatura(dado_t *dado){
    return dado->temperatura;
}

char *obter_tempo(dado_t *dado){
    return dado->tempo;
}

int med_tres(dado_t **dados, int esquerda, int direita)
{
	int med;

	med = (esquerda + direita)/2;

	if((dados[direita]->temperatura) < dados[esquerda]->temperatura)
		swap(dados, esquerda, direita);

	if(dados[med]->temperatura < dados[esquerda]->temperatura)
			swap(dados, med, direita);

	if(dados[direita]->temperatura < dados[med]->temperatura)
			swap(dados, direita, med);

	return med;
}

void swap(dado_t **dados, int j, int j_um)
{
	dado_t *temp;

	temp = dados[j];
	dados[j] = dados[j_um];
	dados[j_um] = temp;

}

void quicksort_iterativo(dado_t **dados,pilha_t *pilha_temp, int esquerda, int direita)
{
	//pilha_t *pilha_temp;
	int p;

	//pilha_temp = cria_pilha(direita - esquerda +1);

	push(esquerda, pilha_temp);
	push(direita, pilha_temp);

	while(!pilha_vazia(pilha_temp))
	{
		direita = pop(pilha_temp);
		esquerda = pop(pilha_temp);

		p = particiona_iterativo(dados, pilha_temp, esquerda, direita);

		if(p - 1 > esquerda)
		{
			push(esquerda, pilha_temp);
			push(p - 1, pilha_temp);
		}

		if(p + 1 < direita)
		{
			push(p + 1, pilha_temp);
			push(direita, pilha_temp);
		}
	}
}

int particiona_iterativo(dado_t **dados, pilha_t *pilha_temp, int esquerda, int direita)
{

	float pivot;

	int med,i,j;

	med = med_tres(dados, esquerda, direita);

	pivot = dados[med]->temperatura;

	i = esquerda - 1;

	for(j = esquerda; j <= direita - 1; j++)
	{
		if(dados[j]->temperatura <= pivot)
		{
			i++;
			swap(dados,i,j);
		}
	}
	swap(dados, i+1, direita);
	return (i+1);
}
