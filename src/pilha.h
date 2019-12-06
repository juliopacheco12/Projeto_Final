#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#define TAMANHO_DADOS_PILHA 100

typedef struct pilhas pilha_t;

pilha_t * cria_pilha (int tam);

void push(int dado, pilha_t *pilha);

int pop(pilha_t *pilha);

int pilha_vazia(pilha_t *pilha);

void liberar_pilha(pilha_t *vetor);


#endif // PILHA_H_INCLUDED

