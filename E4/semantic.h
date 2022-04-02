#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "stack.h"
#include "types.h"
#include "errors.h"

static stack_t* scope_stack = NULL;

void semantic_init();

void enter_scope();

void exit_scope();

void ident_var_array_global_decl_list(
    enum data_type type,
    int is_static,
    node *list
);

void ident_var_array_local_decl_list(
    enum data_type type,
    int is_static,
    int is_const,
    node *list
);

/**
 * Nova declaração de uma variável.
 * 
 * Verifica se já foi declarado nesse escopo, 
 * lançando #ERR_DECLARED caso positivo.
 * 
 * @param ident nome da variável
 * @param type tipo da variável
 */
void ident_var_declaration(
    char *ident,
    enum data_type type,
    int is_static
);

/**
 * Nova declaração de um vetor.
 * 
 * Verifica se já foi declarado nesse escopo, 
 * lançando #ERR_DECLARED caso positivo.
 * 
 * Se o vetor declarado for do tipo string, lança
 * um #ERR_STRING_VECTOR
 * 
 * @param ident nome do vetor
 * @param type tipo dos itens do vetor
 * @param vector_size tamanho do vetor
 */
void ident_vector_declaration(
    char *ident,
    enum data_type type,
    int is_static,
    int vector_size
);

/**
 * Nova declaração de uma função.
 * 
 * Verifica se já foi declarado nesse escopo, 
 * lançando #ERR_DECLARED caso positivo.
 * 
 * O retorno e os paramentros não podem ser do tipo
 * string, caso forem lança um #ERR_FUNCTION_STRING
 * 
 * @param ident 
 * @param return_type 
 * @param argc 
 * @param ... 
 */
void ident_fun_declaration(
    char *ident,
    enum data_type return_type,
    node *params
);

/**
 * Verifica o uso da variável ident. Caso seu uso seja
 * como vetor ou variável, lança um #ERR_VARIABLE.
 * 
 * Se o ident não foi declarado, lança #ERR_UNDECLARED
 * 
 * @param ident nome da variável
 */
void ident_var_use(char *ident);

/**
 * Verifica o uso do vetor ident. Caso seu uso seja
 * como função ou variável, lança um #ERR_VECTOR.
 * 
 * Se o ident não foi declarado, lança #ERR_UNDECLARED
 * 
 * @param ident nome do vetor
 */
void ident_vector_use(char *ident);

/**
 * Verifica o uso da função ident. Caso seu uso seja
 * como vetor ou variável, lança um #ERR_FUNCTION.
 * 
 * Se o ident não foi declarado, lança #ERR_UNDECLARED
 * 
 * Verifica se os arumentos informados batem com os
 * argumentos da declaração dessa função, caso a lista
 * informada seja menor, lança um #ERR_MISSING_ARGS;
 * caso seja maior, lança #ERR_MISSING_ARGS.
 * 
 * Se a quantidade for correta, mas os tipos estiveram
 * errados lança um #ERR_WRONG_TYPE_ARGS.
 * 
 * @param ident nome da função
 */
void ident_fun_use(char *ident, node *params);

/**
 * Verifica o comando de atribuição de variável.
 * 
 * Se a expressão value avaliar para um tipo que que não
 * da para converter implicitamente para o tipo de ident,
 * então lança um erro #ERR_WRONG_TYPE
 * 
 * Se ident for uma string e o valor exceceder o tamanho
 * definido na atribuição, lança um erro #ERR_STRING_MAX
 * 
 * @param ident nome da variável
 * @param value expressão do novo valor
 */
void ident_var_set(char *ident, node *value);

/**
 * Verifica o comando de atribuição de variável.
 * 
 * Se a expressão value avaliar para um tipo que que não
 * da para converter implicitamente para o tipo de ident,
 * então lança um erro #ERR_WRONG_TYPE
 * 
 * @param ident nome do vetor
 * @param index expressão do indice
 * @param value expressão do novo valor
 */
void ident_vector_set(char *ident, node *index, node *value);

/**
 * Infere o tipo de uma expressão root.
 * 
 * @param root 
 * @return enum data_type 
 */
enum data_type infer_expression_type(node *root);

void print_stack();

#endif