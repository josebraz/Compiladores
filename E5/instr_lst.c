/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "instr_lst.h"

instruction_entry_t *instr_lst_create_new(instruction_t *new_inst) {
    instruction_entry_t *new_entry = (instruction_entry_t*) malloc(sizeof(instruction_entry_t));
    new_entry->next = NULL;
    new_entry->previous = NULL;
    new_entry->entry = new_inst;
    return new_entry;
}

instruction_entry_t *instr_lst_join(instruction_entry_t *entry1, instruction_entry_t *entry2) {
    if (entry1 == NULL) {
        return entry2;
    }
    instruction_entry_t *last = entry1;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = entry2;
    entry2->previous = last;
    return entry1;
}

instruction_entry_t *instr_lst_create(int size, ...) {
    int i;
    instruction_t *instr;
    instruction_entry_t *entry, *last_entry = NULL, *first_entry = NULL;
    va_list arguments;
    
    va_start(arguments, size);
    for (i = 0; i < size; i++) {
        instr = (instruction_t*) va_arg(arguments, instruction_t*);
        entry = instr_lst_create_new(instr);
        if (i == 0) first_entry = entry;

        if (last_entry != NULL) {
            last_entry->next = entry;
            entry->previous = last_entry;
        }
        last_entry = entry;
    }
    va_end(arguments);

    return first_entry;
}

//   A <-> B <-> C 
//                  entra o D no meio do A e B
//   A <-> D <-> B <-> C
instruction_entry_t *instr_lst_add_next(instruction_entry_t *a, instruction_t *new_inst) {
    instruction_entry_t *d = instr_lst_create_new(new_inst);
    if (a == NULL) {
        return d;
    }
    instruction_entry_t *b = a->next;
    d->next = b;
    d->previous = a;
    if (b != NULL) {
        b->previous = d;
    }
    a->next = d;
    return a;
}

//   A <-> B <-> C 
//                  entra o D no meio do A e B
//   A <-> D <-> B <-> C
instruction_entry_t *instr_lst_add_previous(instruction_entry_t *b, instruction_t *new_inst) {
    instruction_entry_t *d = instr_lst_create_new(new_inst);
    if (b == NULL) {
        return d;
    }
    instruction_entry_t *a = b->previous;
    return instr_lst_add_next(a, new_inst);
}


