/* autores: José Henrique da Silva Braz */

#ifndef STACK_H
#define STACK_H

#include "stdlib.h"

#define STACK_INITIAL_CAPACITY 10
#define STACK_REALLOC_STEP     10

// Estrura que representa uma entrada na pilha
// não suportado ponteiros de alocação dinâmica nesta estrutura
typedef struct __stack_entry {
    int test; // TODO: incluir os campos que precisar
} stack_entry_t;

// ATENÇÃO: Não mexer nos atributos desta estrutura diretamete!
typedef struct __stack
{
    int index;               // Indice atual da pilha, -1 é vazia
    size_t actual_capacity;  // Capacidade atual da pilha
    stack_entry_t **entries; // Ponteiro para as entradas da pilha
} stack_t;

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
 * Cria uma entrada, sem alterar o estado da pilha 
 */
stack_entry_t* stack_create_entry(int value);

/**
 * Atualiza entry como o elemento mais acima da pilha e remove
 * e retorna 1, caso a pilha esteja vazia, retorna 0
 * 
 * Obs: Desaloca memória se for preciso
 */
int stack_pop(stack_t *s, stack_entry_t *entry);

/**
 * Apenas atualiza entry como o elemento de cima sem remover
 * e retorna 1, caso a pilha esteja vazia, retorna 0
 */
int stack_peek(stack_t *s, stack_entry_t *entry);

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