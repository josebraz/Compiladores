/* autores: José Henrique da Silva Braz */

#ifndef INSTR_LST_H
#define INSTR_LST_H

#include "types.h"

instruction_entry_t *instr_lst_create(int size, ...);

instruction_entry_t *instr_lst_create_new(instruction_t *new_inst);

instruction_entry_t *instr_lst_join(int size, ...);

instruction_entry_t *instr_lst_add_next(instruction_entry_t *entry, instruction_t *new_inst);

instruction_entry_t *instr_lst_add_previous(instruction_entry_t *entry, instruction_t *new_inst);

#endif


