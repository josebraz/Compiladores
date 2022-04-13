#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "stack.h"
#include "types.h"
#include "errors.h"

/**
 * Inicializa a pilha de escopos e cria o 
 * escopo global
 * 
 */
void semantic_init();

stack_entry_t *current_scope();

/**
 * Cria um novo escopo com o label informado.
 * No caso de um escopo de função, o label
 * é o nome da função
 * 
 * @param label 
 */
void enter_scope(char *label);

/**
 * Remove o escopo atual da pilha
 * 
 */
void exit_scope();

void init_decl_list(int is_static, int is_const, enum data_type type);

/**
 * A partir de uma lista de declaração global,
 * cria todos as entradas necessárias no escopo
 * global.
 * 
 * @param type 
 * @param is_static 
 * @param list 
 */
void ident_var_array_global_decl_list(
    enum data_type type,
    int is_static,
    node *list
);

/**
 * Adiciona um literal na tabela global para ser compartilhado
 * em diferentes local com a mesma alocação de memória
 * 
 * @param literal 
 */
void literal_use(node* literal);

/**
 * Nova declaração de uma variável.
 * 
 * Verifica se já foi declarado nesse escopo, 
 * lançando #ERR_DECLARED caso positivo.
 * 
 * @param ident nome da variável
 * @param type tipo da variável
 */
hashmap_value_t *ident_var_declaration(
    char *ident,
    enum data_type type,
    int is_static
);

hashmap_value_t *ident_var_declaration_item(char *ident);

hashmap_value_t *ident_var_declaration_init_item(char *ident, node *init);

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
 * Cria um novo escopo e coloca as variáveis que são
 * parametros dessa função na tabela de simbolos, seguindo
 * as regras de declaração de variáveis
 * 
 * @param ident 
 * @param return_type 
 * @param argc 
 * @param ... 
 */
void ident_fun_declaration(
    char *ident,
    enum data_type return_type,
    node *params,
    int label
);

/**
 * Verifica o uso da variável ident. Caso seu uso seja
 * como vetor ou variável, lança um #ERR_VARIABLE.
 * 
 * Se o ident não foi declarado, lança #ERR_UNDECLARED
 * 
 * @param ident nome da variável
 */
hashmap_value_t *ident_var_use(char *ident);

/**
 * Verifica o uso do vetor ident. Caso seu uso seja
 * como função ou variável, lança um #ERR_VECTOR.
 * 
 * Se o ident não foi declarado, lança #ERR_UNDECLARED
 * 
 * @param ident nome do vetor
 */
hashmap_value_t *ident_vector_use(char *ident, node *index);

/**
 * Verifica o uso da função ident. Caso seu uso seja
 * como vetor ou variável, lança um #ERR_FUNCTION.
 * 
 * Se o ident não foi declarado, lança #ERR_UNDECLARED
 * 
 * Verifica se os arumentos informados batem com os
 * argumentos da declaração dessa função, caso a lista
 * informada seja menor, lança um #ERR_MISSING_ARGS;
 * caso seja maior, lança #ERR_EXCESS_ARGS.
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
 * Verifica o comando de atribuição de um vetor.
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
 * Verifica se o identificador usado é do tipo 
 * int ou float, caso contrário lança #ERR_WRONG_PAR_INPUT
 * 
 * @param ident 
 */
void verify_input_use(node *ident);

/**
 * Verifica se o identificador ou literal é do 
 * tipo int ou float, caso contrário lança #ERR_WRONG_PAR_OUTPUT
 * 
 * @param ident_or_literal 
 */
void verify_output_use(node *ident_or_literal);

/**
 * Verifica se o retorno é compatível com o retorno
 * da função, caso contrário lança #ERR_WRONG_PAR_RETURN
 * 
 * @param expression 
 */
void verify_return(node *expression);

/**
 * Verifica se o parametro do comando shift não ultrapassa
 * o número 16, caso seja lança #ERR_WRONG_PAR_SHIFT
 * 
 * @param p 
 */
void verify_shift(int p);

/**
 * Verifica se pode converter implicitamente de um tipo 
 * source para um dest.
 * 
 * @param source tipo de origem
 * @param dest tipo de destino
 * @return int 1 se é possível, 0 caso contrário
 */
int can_implicit_conversion(enum data_type source, enum data_type dest);

/**
 * Procura a entrada na tabela correspondente ao identificador
 * procurando recursivamente nos escopos mais internos
 * até os mais externos até o global.
 * Se não achar, lança o erro ERR_UNDECLARED
 * 
 * @param ident 
 * @return enum data_type 
 */
hashmap_value_t *find_declaration(char *ident, hashmap_t **fold_scope);

/**
 * Infere o tipo de uma expressão root.
 * 
 * @param root 
 * @return enum data_type 
 */
enum data_type infer_expression_type(node *root);

void print_stack();

#endif