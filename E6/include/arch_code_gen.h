/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/


#ifndef ARCH_CODE_H
#define ARCH_CODE_H

#include "types.h"
#include "depend_graph.h"

instruction_entry_t *arch_convert_code(instruction_entry_t *instruction_list, int* node_colors, graph_t* graph);


#endif