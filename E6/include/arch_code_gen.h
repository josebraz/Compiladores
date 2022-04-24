/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#ifndef ARCH_CODE_H
#define ARCH_CODE_H

#include "types.h"
#include "depend_graph.h"
#include "code_gen.h"

instruction_entry_t *optimize_iloc_register_usage(instruction_entry_t *instruction_list, int* node_colors, graph_t* graph);

#endif