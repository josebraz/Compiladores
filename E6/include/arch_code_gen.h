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

void print_x86_64_assembly_code(instruction_entry_t *instruction_list);
void get_x86_64_assembly_register_name(int reg, char *dest);
void print_assembly_instruction(instruction_t *instruction);
void print_label(instruction_t *instruction);
void print_store(instruction_t *instruction);
void print_instruction_parameter(int op, int op_type);
void print_add(instruction_t *instruction);

#endif