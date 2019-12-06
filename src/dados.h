#ifndef DADO_H_INCLUDED
#include "pilha.h"
/* Cria��o de tipo abstrato dado_t */
typedef struct dados dado_t;

/**
  * @brief  Cria um novo dado
  * @param  amostra: identificador da amostra
  * @param  temperatura: valor da temperatura
  * @param  timestamp: data e hora da amostra
  *
  * @retval dado_t: ponteiro para uma novo dado
  */
dado_t * criar_dado (int index, char *data, float prize, float total ,char *tipo, char *regiao);


/* Outras fun��es aqui: fazer os coment�rios */

dado_t **ler_dados_csv(char *nome_do_arquivo, int *num_linhas);

void liberar_dados(dado_t **vetor, int tamanho);

int obter_index(dado_t *dado);

float obter_prize(dado_t *dado);

float obter_total(dado_t *dado);

char *obter_data(dado_t *dado);

char *obter_tipo(dado_t *dado);

char *obter_regiao(dado_t *dado);

void swap(dado_t **dados, int j, int j_um);

void quicksort(dado_t **dados, int esquerda, int direita);

int particiona(dado_t **dados, int esquerda, int direita);

int med_tres(dado_t **dados, int esquerda, int direita);

void quicksort_iterativo(dado_t **dados, pilha_t *pilha_temp, int esquerda, int direita);

void quicksort(dado_t **dados, int esquerda, int direita);

int particiona(dado_t **dados, int esquerda, int direita);

int cmp(const void *x, const void *y);

#endif

