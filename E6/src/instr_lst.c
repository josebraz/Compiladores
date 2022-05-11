/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "instr_lst.h"

/**
 * @brief Counts instruction in the received argument list
 * 
 * @param list instruction_entry_t structure pointer
 * @return int number of instructions
 */
int instr_lst_count(instruction_entry_t *list) {
    instruction_entry_t *current = list;
    int counter = 0;
    while (current != NULL) {
        if (current->entry->op1_type != OT_LABEL && current->entry->op1_type != OT_MARK) {
            counter++;
        }
        current = current->next;
    }
    return counter;
}

void free_instruction(instruction_t *entry) {
    if (entry->live_out != NULL) {
        free(entry->live_out);
        entry->live_out = NULL;
    }
    if (entry->mark_property != NULL) {
        free(entry->mark_property);
        entry->mark_property = NULL;
    }
    if (entry->comment != NULL) {
        free(entry->comment);
        entry->comment = NULL;
    }
    free(entry);
}

void instr_lst_free(instruction_entry_t *head) {
    instruction_entry_t *temp;
    instruction_entry_t *list = head;
    
    while (list->next != NULL) {
        temp = list->next;
        free_instruction(list->entry);
        free(list);
        list = temp;
    }
}

instruction_entry_t *instr_lst_copy(instruction_entry_t *source) {
    instruction_entry_t *temp = NULL;
    instruction_entry_t *current = source, *first = NULL, *last = NULL;
    while (current != NULL) {
        temp = (instruction_entry_t*) calloc(1, sizeof(instruction_entry_t));
        temp->entry = (instruction_t*) malloc(sizeof(instruction_t));
        *(temp->entry) = *(current->entry);
        temp->next = NULL;
        temp->previous = NULL;

        if (first == NULL) {
            first = temp;
        } else {
            temp->previous = last;
            last->next = temp;
        }
        last = temp;
        current = current->next;
    }
    return first;
}

instruction_entry_t *instr_lst_create_new(instruction_t *new_inst) {
    instruction_entry_t *new_entry = (instruction_entry_t*) malloc(sizeof(instruction_entry_t));
    new_entry->next = NULL;
    new_entry->previous = NULL;
    new_entry->entry = new_inst;
    return new_entry;
}

instruction_entry_t *instr_lst_join_internal(instruction_entry_t *entry1, instruction_entry_t *entry2) {
    if (entry1 == NULL) return entry2;
    if (entry2 == NULL) return entry1;
    instruction_entry_t *last = entry1;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = entry2;
    entry2->previous = last;
    return entry1;
}

instruction_entry_t *instr_lst_join(int size, ...) {
    instruction_entry_t *instr = NULL;
    va_list arguments;
    va_start(arguments, size);
    if (size >= 1) {
        instr = (instruction_entry_t*) va_arg(arguments, instruction_entry_t*);
        for (int i = 0; i < size - 1; i++) {
            instr = instr_lst_join_internal(instr, (instruction_entry_t*) va_arg(arguments, instruction_entry_t*));
        }
    }
    va_end(arguments);
    return instr;
}

instruction_entry_t *instr_lst_create(int size, ...) {
    instruction_t *instr;
    instruction_entry_t *entry, *last_entry = NULL, *first_entry = NULL;
    va_list arguments;
    
    va_start(arguments, size);
    for (int i = 0; i < size; i++) {
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

int instr_lst_contain(instruction_entry_t *start, instruction_entry_t *end, instruction_t *find) {
    instruction_entry_t *current = start;
    while (current != NULL) {
        if (current->entry == find) {
            return 1;
        }
        if (current == end) {
            return 0;
        }
        current = current->next;
    }
    return 0;
}

instruction_entry_t *instr_lst_remove(instruction_entry_t *inst) {
    instruction_entry_t *current_instruction_next = inst->next;

    if (inst->previous != NULL) {
        inst->previous->next = current_instruction_next;
    }

    if (current_instruction_next != NULL) {
        current_instruction_next->previous = inst->previous;
    }

    free_instruction(inst->entry);
    free(inst);

    return current_instruction_next;
}

instruction_entry_t *instr_lst_remove_mark_interval(
    instruction_entry_t *inst, 
    int start_mark, 
    int end_mark
) {
    instruction_entry_t *current = inst;
    instruction_entry_t *start = NULL;
    int is_removing = 0;
    while (current != NULL) {
        // estamos ainda procurando a marcação de start
        if (current->entry->op1_type == OT_MARK && current->entry->op1 == start_mark) {
            is_removing = 1;
        }
        if (is_removing == 1) {
            // Estamos na marcação de end
            if (current->entry->op1_type == OT_MARK && current->entry->op1 == end_mark) {
                is_removing = 0;
            }
            current = instr_lst_remove(current);
        } else {
            if (start == NULL) {
                start = current;
            }
            current = current->next;
        }
    }

    return start;
}

int instr_lst_end_with_code(instruction_entry_t *inst, char *code) {
    instruction_entry_t *current = inst;
    if (current == NULL) {
        return 0;
    }
    // navega até o final da lista
    while (current->next != NULL) {
        current = current->next;
    }
    if (strcmp(current->entry->code, code) == 0) {
        return 1;
    } else {
        return 0;
    }
}