/* autores: José Henrique da Silva Braz */

#ifndef STACK_H
#define STACK_H

#include "types.h"

#define STACK_INITIAL_CAPACITY 10
#define STACK_REALLOC_STEP     10

/**
 * Cria uma pilha nova com capacidade inicial de 10
 * Caso não seja possível criar a pilha, retorna NULL
 */
stack_t* stack_init();

/**
 * Destroi a pilha, desalocando toda a memória
 */
stack_t* stack_destroy(stack_t* s);

/**
 * Atualiza entry como o elemento mais acima da pilha e remove
 * e retorna 1, caso a pilha esteja vazia, retorna 0
 * 
 * Obs: Desaloca memória se for preciso
 */
stack_entry_t *stack_pop(stack_t *s);

/**
 * Apenas atualiza entry como o elemento de cima sem remover
 * e retorna 1, caso a pilha esteja vazia, retorna 0
 */
stack_entry_t *stack_peek(stack_t *s);

/**
 * Coloca um novo elemento no topo da pilha
 * Se a pilha estiver cheia, alocamos mais memória
 * para pode comportar os novos componentes
 */
void stack_push(stack_t *s, stack_entry_t *entry);

/**
 * Retorna 1 se a pilha estiver vazia ou 0 caso contrário
 * 
 * @param s 
 * @return int 
 */
int stack_is_empty(stack_t *s);

/**
 * Retorna 1 caso a capacidade da pilha for atingida ou 0 caso contrário
 */
int stack_is_full(stack_t *s);

#endif