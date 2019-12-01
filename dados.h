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
dado_t * criar_dado (int amostra, float temperatura, char  *tempo);


/* Outras fun��es aqui: fazer os coment�rios */

dado_t **ler_dados_csv(char *nome_do_arquivo, int *num_linhas);

void liberar_dados(dado_t **vetor, int tamanho);

int obter_amostra(dado_t *dado);

float obter_temperatura(dado_t *dado);

char *obter_tempo(dado_t *dado);

void swap(dado_t **dados, int j, int j_um);

void quicksort(dado_t **dados, int esquerda, int direita);

int particiona(dado_t **dados, int esquerda, int direita);

int med_tres(dado_t **dados, int esquerda, int direita);

void quicksort_iterativo(dado_t **dados, pilha_t *pilha_temp, int esquerda, int direita);

int particiona_iterativo(dado_t **dados, pilha_t *pilha_temp, int esquerda, int direita);

#endif
