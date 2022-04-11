/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "bool_lst.h"


int bool_lst_next_remendo() {
    static int last_remendo = -100;
    return last_remendo--;
}

bool_list *bool_lst_create(int size, ...) {
    va_list arguments;
    bool_list *entry, *last_entry = NULL, *first_entry = NULL;
    va_start(arguments, size);
    for (int i = 0; i < size; i++) {
        entry = bool_lst_new_entry((int*) va_arg(arguments, int*));
        if (i == 0) first_entry = entry;
        if (last_entry != NULL) {
            last_entry->next = entry;
        }
        last_entry = entry;
    }
    va_end(arguments);
    return first_entry;
}

bool_list *bool_lst_new_entry(int *bool_pointer) {
    bool_list *new_entry = (bool_list*) malloc(sizeof(bool_list));
    new_entry->next = NULL;
    new_entry->label_pointer = bool_pointer;
    return new_entry;
}

bool_list *bool_lst_concat(bool_list *entry1, bool_list *entry2) {
    if (entry1 == NULL) {
        return entry2;
    }
    bool_list *last = entry1;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = entry2;
    return entry1;
}

void bool_lst_remenda(bool_list *lst, int value) {
    bool_list *item = lst;
    while (item != NULL) {
        *(item->label_pointer) = value;
        item = item->next;
    }
}