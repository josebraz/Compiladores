/* autores: José Henrique da Silva Braz */

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

#endif


