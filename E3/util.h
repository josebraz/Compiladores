/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

#ifndef UTIL_H
#define UTIL_H

#include "types.h"

/**
 * Escreve na saída padrão o texto formatado
 * de acordo com a especialização
 * 
 * @param arvore 
 */
void exporta(void *arvore);

/**
 * Libera toda arvore recursivamente e seus filhos
 * 
 * @param arvore 
 */
void libera(void *arvore);

/**
 * Imprime os filhos de todos os nodos recursivamente
 * 
 * @param arvore 
 */
void print_tree_children(void *arvore);

/**
 * Imprime, para todos os nodos, os labels do nodo
 * 
 * @param arvore 
 */
void print_tree_labels(void *arvore);

/**
 * Libera a memória do nodo n
 * 
 * @param n 
 */
void free_node(node *n);

/**
 * Lida com a lista declaração de variável local 
 * 
 * @param n 
 * @return node* o nodo recebido
 */
node *process_local_desc(node *n);

/**
 * Lida com a lista de comandos, tratando as questões de 
 * bloco de comandos e lista de decalarações de variáveis locais
 * 
 * @param head comando atual que está sendo captado pelo bison
 * @param back comandos que o bison já processou e passou por essa função
 * @return node* o comando mais acima válido (não nulo)
 */
node *process_stmt_list(node *head, node *back);

#endif
