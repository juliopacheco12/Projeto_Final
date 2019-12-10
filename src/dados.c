
/* de um arquivo CSV conforme o padrï¿½o:
  *         Series;Value;Time
  *         <int>;<float>;<string>
  *         <int>;<float>;<string> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "pilha.h"

struct dados {
    int index;			//*!< Identificador numï¿½rido da amostra */
    char data[68];		//*!< Valor do dado: temperatura */
    float prize;		//*!< Time stamp */
    float total;		/*volume de vendas*/
	char tipo[30];		/*Tipo de abacate*/
	char regiao[64];	/*Região de medição*/
};


dado_t * criar_dado (int index, char *data, float prize, float total ,char *tipo, char *regiao){

    dado_t * meu_novo_dado = malloc(sizeof(dado_t));

    if(meu_novo_dado == NULL){
        perror("Erro criar_dado");
        exit(-1);
    }

    // Colocar a criaï¿½ï¿½o dos dados aqui


    meu_novo_dado->index = index;
    strncpy(meu_novo_dado->data, data, 64);
    meu_novo_dado->prize = prize;
    meu_novo_dado->total = total;
    strncpy(meu_novo_dado->tipo, tipo, 20);
    strncpy(meu_novo_dado->regiao, regiao, 64);

    return meu_novo_dado;
}



dado_t **ler_dados_csv(char *nome_do_arquivo, int *num_linhas){

    int index;			/*/*!< Identificador numerico da amostra */
    char data[64];		/*/*!< Valor do dado: temperatura */
    float prize;		//*!< Time stamp */
    float total;		/*volume de vendas*/
	char tipo[20];		/*Tipo de abacate*/
	char regiao[64];	/*Região de medição*/

	char texto[128];
	int i = 0;

    /* Demais Variï¿½veis */


    dado_t **dados;

    FILE *fp = fopen(nome_do_arquivo,"r");

    if (!fp){
        perror("ler_dados_csv");
        exit(-1);
    }

    /* Ignora primeira linha */
    fgets(texto,128, fp);

    /* Contar todas as linhas: use while e fgets() */
    while(fgets(texto,128,fp)!=NULL){
        (*num_linhas)++;
    }


    /* Aloque memï¿½ria:
     * Agora ï¿½ um vetor de ponteiros */
    dados = malloc(sizeof(dado_t ) * (*num_linhas));

    rewind(fp);
     /* Ignora primeira linha */
    fgets(texto,128, fp);


    while (fscanf (fp, "%d, %63[^,], %f, %f, %19[^,], %63[^\n]", &index, data, &prize, &total, tipo, regiao) == 6){
       // printf("Lido %d, %f, %s\n", amostra, temperatura, texto);
        /* Cria um novo dado abstrato e armazena a sua referï¿½ncia */
        dados[i] = criar_dado(index, data, prize, total, tipo, regiao);

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

int obter_index(dado_t *dado){
    return dado->index;
}

float obter_prize(dado_t *dado){
    return dado->prize;
}

char *obter_data(dado_t *dado){
    return dado->data;
}

char *obter_tipo(dado_t *dado){
    return dado->tipo;
}

char *obter_regiao(dado_t *dado){
    return dado->regiao;
}

float obter_total(dado_t *dado){
    return dado->total;
}

int med_tres(dado_t **dados, int esquerda, int direita)
{
	int med;

	med = (esquerda + direita)/2;

	if((dados[direita]->prize) < dados[esquerda]->prize)
		swap(dados, esquerda, direita);

	if(dados[med]->prize < dados[esquerda]->prize)
			swap(dados, med, direita);

	if(dados[direita]->prize < dados[med]->prize)
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

		p = particiona(dados, esquerda, direita);

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

void quicksort(dado_t **dados, int esquerda, int direita)
{
	int p;

	if(esquerda < direita)
		{
			p = particiona(dados, esquerda, direita);
			quicksort(dados, esquerda, p);
			quicksort(dados, p+1, direita);
		}
}

int particiona(dado_t **dados, int esquerda, int direita)
{
	int med,i,j;
	float pivot_temp;

	med = med_tres(dados, esquerda, direita);

	pivot_temp = dados[med]->prize;

	i = esquerda - 1;
	j = direita	 + 1;

	while(1)
	{
		do{

		i = i +1;

		}while(dados[i]->prize < pivot_temp);

		do{
			j = j - 1;

		}while(dados[j]->prize > pivot_temp);

		if( i >= j)
			return j;

		swap(dados,i,j);
	}
}

int cmp(const void* elem1, const void* elem2)
{
    if(*(const float*)elem1 < *(const float*)elem2)
        return -1;
    return *(const float*)elem1 > *(const float*)elem2;
}
