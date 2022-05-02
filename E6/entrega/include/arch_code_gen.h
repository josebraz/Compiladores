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

void generateAsm(instruction_entry_t *instruction_list);

int print_assembly_instruction(instruction_entry_t *instruction_lst);

int print_label(instruction_entry_t *instruction_lst);

int print_jump_instruction(instruction_entry_t *instruction_lst);

int print_general_instruction(instruction_entry_t *instruction_lst);

int print_mem_instruction(instruction_entry_t *instruction_lst);

int print_mark_instruction(instruction_entry_t *instruction_lst);

void print_instruction_parameter(int op, int op_type, char *output);


#endif