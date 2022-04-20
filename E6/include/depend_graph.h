/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/


#ifndef DEPEND_GRAPH_H
#define DEPEND_GRAPH_H

#include "types.h"

/**
 * @brief Estrutura que guarda o life_start e o life_end da variável
 * 
 */
typedef struct __var_live {
    int var;
    instruction_entry_t *start;
    instruction_entry_t *end;
} var_live;

/**
 * @brief Grafo utilizado para encontrar número mínimo de registradores utilizáveis
 * 
 */
typedef struct __graph {
    int size;
    char **edges;
} graph_t;

/**
 * @brief Printa o grafo na saída padrão
 * 
 * @param graph Ponteiro para estrutura do tipo grafo
 */
void print_graph(graph_t *graph);

/**
 * @brief Gera e retorna o tamanho do grafo necessário a partir do código
 * 
 */
int generate_depend_graph(instruction_entry_t *code, char ***graph_result);

/**
 * @brief Conta os vizinhos de um nodo do grafo
 * 
 */
int count_neighborhood(int node, graph_t *graph);

/**
 * @brief Tenta colorir o grafo graph com k colors
 * 
 */
int try_color_graph(int colors, graph_t *graph);

#endif
