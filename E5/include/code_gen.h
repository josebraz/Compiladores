/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/


#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "types.h"

/**
 * gera um novo registrador sempre diferente 
 * representado como um inteiro
 * 
 * @return int 
 */
int next_reg();

/**
 * Gera um novo label único representado como
 * um inteiro
 * 
 * @return int 
 */
int next_label();

/**
 * gera os códigos para o retorno de um função, 
 * carrega o endereço de retorno da pilha e restaura
 * os registradores
 * 
 * @param s node de retorno
 * @param e expressão do retorno
 */
void generate_fun_return(node *s, node *e);

/**
 * Gera os códigos de uma declaração de função:
 * Grava os registradores que serão usado na pilha,
 * atualiza o rfp e rsp. Coloca um comando de halt
 * se a função for a main
 * 
 * @param fun 
 */
void generate_fun_decl(node *fun);

/**
 * Gera o código de uma chamada de função,
 * empilha o endereço de retorno, rsp e rfp e ainda
 * os parâmetros da função se houverem
 * 
 * @param s nodo da chamada de função
 * @param params parametros da função
 */
void generate_fun_call(node *s, node *params);

/**
 * Gera o código para o loop for
 * 
 * @param s nodo do loop
 * @param s1 inicialização do loop
 * @param b teste para entrar na iteração
 * @param s2 incremento do indice do loop
 * @param s3 código de dentro do loop
 */
void generate_for(node *s, node *s1, node *b, node *s2, node *s3);

/**
 * Gera o código para o loop while
 * 
 * @param s 
 * @param b 
 * @param s1 
 */
void generate_while(node *s, node *b, node *s1);

/**
 * Gera o código para o comando if
 * 
 * @param b 
 * @param e 
 * @param b_true 
 * @param b_false 
 */
void generate_if(node *b, node *e, node *b_true, node *b_false);

/**
 * Gera o código para o AND lógico
 * 
 * @param b nodo do AND
 * @param b1 primeiro argumento
 * @param b2 segundo argumento
 */
void generate_and(node *b, node *b1, node *b2);

/**
 * Gera o código para o OR lógico
 * 
 * @param b nodo do OR
 * @param b1 primeiro argumento
 * @param b2 segundo argumento
 */
void generate_or(node *b, node *b1, node *b2);

/**
 * Gera o código para o NOT lógico
 * 
 * @param b nodo do NOT
 * @param b1 primeiro argumento
 */
void generate_not(node *b, node *b1);

/**
 * Gera o código para a constante TRUE
 * 
 * @param b 
 */
void generate_true(node *b);

/**
 * Gera o código para a constante FALSE
 * 
 * @param b 
 */
void generate_false(node *b);

/**
 * Gera o código para as operações de relação 
 * 
 * @param code texto que identifica qual é o operador (EQ, LT, ...)
 * @param parent 
 * @param n1 
 * @param n2 
 */
void generate_relop(char *code, node *parent, node *n1, node *n2);

/**
 * Gera um código com dois argumentos n1 e n2, com a instrução
 * code e coloca no nodo b
 * 
 * @param code instrução
 * @param b 
 * @param n1 primeiro argumento
 * @param n2 segundo argumento
 */
void generate_general_code(char *code, node *b, node *n1, node *n2);

/**
 * Gera o código para o carregamento de uma
 * variável no nodo n
 * 
 * @param n 
 */
void generate_var_load(node *n);

/**
 * Gera o código para o carregamente de um
 * literal no nodo n
 * 
 */
void generate_literal_load(node *n);

/**
 * Gera o código de set de uma variável
 * 
 * @param ident 
 * @param b 
 * @param init 
 */
void generate_var_assignment(char *ident, node *b, node *init);

/**
 * Gera o código de início que inicializa os registradores
 * do programa e pula para função main
 * 
 */
void generate_init_code(node *s);

/**
 * Imprime a lista de instrução uma em cada linha
 * 
 */
void print_instr_lst(instruction_entry_t *entry);

#endif


