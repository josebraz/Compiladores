/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/


#ifndef INSTR_LST_H
#define INSTR_LST_H

#include "types.h"

int instr_lst_count(instruction_entry_t *list);

void instr_lst_free(instruction_entry_t *list);

instruction_entry_t *instr_lst_copy(instruction_entry_t *source);

instruction_entry_t *instr_lst_create(int size, ...);

instruction_entry_t *instr_lst_create_new(instruction_t *new_inst);

instruction_entry_t *instr_lst_join(int size, ...);

instruction_entry_t *instr_lst_add_next(instruction_entry_t *entry, instruction_t *new_inst);

instruction_entry_t *instr_lst_add_previous(instruction_entry_t *entry, instruction_t *new_inst);

instruction_entry_t *instr_lst_remove(instruction_entry_t *code);

int instr_lst_contain(instruction_entry_t *start, instruction_entry_t *end, instruction_t *find);

instruction_entry_t *instr_lst_remove_mark_interval(
    instruction_entry_t *inst, 
    int start_mark, 
    int end_mark
);

int instr_lst_end_with_code(instruction_entry_t *inst, char *code);

int instr_lst_count_regs(instruction_entry_t *code);

void instr_lst_change_reg(instruction_entry_t *code, int original_reg, int new_reg);

#endif


