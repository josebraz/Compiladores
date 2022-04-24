/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#ifndef UTIL_H
#define UTIL_H

#include "types.h"
#include "depend_graph.h"

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

void print_graph_node_colors(graph_t *graph, int *node_colors);

#endif
