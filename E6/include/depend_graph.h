/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/


#ifndef DEPEND_GRAPH_H
#define DEPEND_GRAPH_H

#include "types.h"

typedef struct __var_live {
    int var;
    instruction_entry_t *start;
    instruction_entry_t *end;
} var_live;

typedef struct __graph {
    int size;
    char **edges;
} graph_t;

void print_graph(int size, const char **graph);

int generate_depend_graph(instruction_entry_t *code, char ***graph_result);

int count_neighborhood(int node, int size, char **graph);

int try_color_graph(int colors, int size, const char **graph);

#endif
