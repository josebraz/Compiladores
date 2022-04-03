/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

#ifndef ASP_H
#define ASP_H

#include "types.h"

node *asp_stmt_list(node *head, node *tail);

node *remove_uninit_decl_var(node *n);

node *next_node(node *parent);

/**
 * adiciona um filho ao pai
 * 
 * @param father o nodo pai
 * @param child o nodo que vai ser filho do pai
 * @return node* 
 */
node *add_child(node* father, node* child);

/**
 * Remove um nodo to_remove do nodo parent
 * 
 * @param parent 
 * @param to_remove 
 * @return int quantos nodos formam removidos
 */
int remove_child(node *parent, node *to_remove);

/**
 * Imprime um nodo formatado na saída padrão
 * 
 * @param node a ser impresso
 */
void print_node(node *node);

/**
 * Partindo o parent, retorna o último (mais profundo) nodo que 
 * não é folha, caso não encontre retorna NULL
 * 
 * @param parent 
 * @return node* 
 */
node* find_last_node_not_leaf(node *parent);

/**
 * Cria um nodo com o identificador label, do tipo type com o número
 * de filhos nodes (variável)
 * 
 * @param label 
 * @param mark 
 * @param nodes 
 * @param ... 
 * @return node* o novo nodo criado
 */
node* create_node(char *label, enum node_mark mark, int nodes, ...);

/**
 * Cria um novo do tipo identificador array
 * 
 * @param value o identificador do array
 * @param index representa a expressão do index
 * @return node* o novo nodo criado
 */
node* create_node_id_array(char *value, node* index);

/**
 * Cria um nodo de operador unário
 * 
 * @param value 
 * @param next 
 * @return node* o novo nodo criado
 */
node* create_node_unary_ope(char *value, node* next);

/**
 * Cria um nodo de operador binário
 * 
 * @param value 
 * @param node1 
 * @param node2 
 * @return node* o novo nodo criado
 */
node* create_node_binary_ope(char *value, node* node1, node *node2);

/**
 * Cria um nodo de operador ternário
 * 
 * @param value 
 * @param node1 
 * @param node2 
 * @param node3 
 * @return node* o novo nodo criado
 */
node* create_node_ternary_ope(char *value, node* node1, node *node2, node *node3);

/**
 * Cria um nodo de declaração de função
 * 
 * @param name nome da função
 * @param body primeiro comando da função
 * @return node* o novo nodo criado
 */
node* create_node_function(char *name, node* body);

/**
 * Cria uma nova folha genérica, é normalmente 
 * chamado pelas outras funções
 * 
 * @param value valor do nodo (verificar se será necessãrio)
 * @param label identificador do novo
 * @return node* a nova folha criada
 */
node* create_leaf(void *value, char* label);

/**
 * Cria uma nova folha para representar uma declaração de tipo
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_type(char *ident, enum data_type type);

node* create_node_array_decl(char *ident, int size);

/**
 * Cria uma nova folha do tipo inteiro
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_int(int value);

/**
 * Cria uma nova folha do tipo char
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_char(char value);

/**
 * Cria uma nova folha do tipo float
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_float(float value);

/**
 * Cria uma nova folha do tipo boolean
 * 
 * @param value 
 * @param label 
 * @return node* a nova folha criada
 */
node* create_leaf_bool(int value, char* label);

/**
 * Cria uma nova folha de identificador
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_id(char *value);

node* create_leaf_decl_var(char *value);

/**
 * Cria uma nova folha do tipo string
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_string(char *value);

/**
 * Cria uma nova folha para a chamada de uma função
 * 
 * @param value 
 * @return node* a nova folha criada
 */
node* create_leaf_fun_call(char *value, node* params);

/**
 * Libera a memória do nodo n
 * 
 * @param n 
 */
void free_node(node *n);

#endif
