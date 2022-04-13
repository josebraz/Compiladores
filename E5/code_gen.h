/* autores: José Henrique da Silva Braz */

#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "types.h"

int next_reg();

int next_label();

void generate_fun_return(node *s, node *e);

void generate_fun_decl(node *fun);

void generate_fun_call(node *s, node *params);

void generate_for(node *s, node *s1, node *b, node *s2, node *s3);

void generate_while(node *s, node *b, node *s1);

void generate_if(node *b, node *e, node *b_true, node *b_false);

void generate_and(node *b, node *b1, node *b2);

void generate_or(node *b, node *b1, node *b2);

void generate_not(node *b, node *b1);

void generate_true(node *b);

void generate_false(node *b);

void generate_relop(char *code, node *parent, node *n1, node *n2);

void generate_general_code(char *code, node *b, node *n1, node *n2);

void generate_var_load(node *n);

void generate_literal_load(node *n);

void generate_var_assignment(char *ident, node *b, node *init);

instruction_entry_t *generate_init_code();

instruction_entry_t *generate_instruction(char *code, int reg1, int reg2, int reg3);

instruction_entry_t *generate_instructionI(char *code, int reg1, int value, int reg3);

instruction_entry_t *generate_instructionS(char *code, int reg1, int value, int reg3);

instruction_entry_t *generate_instructionB(int reg, int label1, int label2);

instruction_entry_t *generate_jumpI(int label);

instruction_entry_t *generate_jump(int reg);

instruction_entry_t *generate_label_instruction(int label);

void comment_instruction(instruction_entry_t *entry, char *message, ...);

void get_var_mem_loc(char *ident, int *reg, int *offset);

void print_instr_lst(instruction_entry_t *entry);

void print_instruction(instruction_t *new_inst);

void output_code_from_node(node* n);

#endif


