/* autores: José Henrique da Silva Braz */

#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "types.h"

int next_reg();

int next_label();

void generate_if(node *b, node *e, node *b_true, node *b_false);

void generate_and(node *b, node *b1, node *b2);

void generate_or(node *b, node *b1, node *b2);

void generate_not(node *b, node *b1);

void generate_true(node *b);

void generate_false(node *b);

void generate_relop(char *code, node *parent, node *n1, node *n2);

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

instruction_entry_t *generate_var_assignment(char *ident, instruction_entry_t *entry);

instruction_entry_t *generate_shift(int left, char *ident, int offset);

instruction_t *generate_instruction(char *code, int reg1, int reg2, int reg3);

instruction_t *generate_instructionI(char *code, int reg1, int value, int reg3);

instruction_t *generate_instructionS(char *code, int reg1, int value, int reg3);

instruction_t *generate_instructionB(int reg, int label1, int label2);

instruction_t *generate_jumpI(int label);

instruction_t *generate_label_instruction(int label);

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


