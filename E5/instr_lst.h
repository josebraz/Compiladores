/* autores: José Henrique da Silva Braz */

#ifndef INSTR_LST_H
#define INSTR_LST_H

#include "types.h"

int next_reg();

instruction_entry_t *generate_init_code();

instruction_entry_t *generate_code(
    char *code, 
    instruction_entry_t *instr1, 
    instruction_entry_t *instr2
);

instruction_entry_t *generate_codeI(
    char *code, 
    instruction_entry_t *instr1, 
    instruction_entry_t *instr2
);

instruction_entry_t *generate_var_load(char *ident);

instruction_entry_t *generate_literal_load(int value);

instruction_entry_t *process_arith_expression(node *head);

instruction_t *generate_instruction(char *code, int reg1, int reg2, int reg3);

instruction_t *generate_instructionI(char *code, int reg1, int value, int reg3);

instruction_t *generate_jumpI(int label);

void get_var_mem_loc(char *ident, int *reg, int *offset);

void print_instr_lst(instruction_entry_t *entry);

void print_instruction(instruction_t *new_inst);

void output_code_from_node(node* n);

instruction_entry_t *instr_lst_create(int size, ...);

instruction_entry_t *instr_lst_create_new(instruction_t *new_inst);

instruction_entry_t *instr_lst_join(instruction_entry_t *entry1, instruction_entry_t *entry2);

instruction_entry_t *instr_lst_add_next(instruction_entry_t *entry, instruction_t *new_inst);

instruction_entry_t *instr_lst_add_previous(instruction_entry_t *entry, instruction_t *new_inst);

#endif


