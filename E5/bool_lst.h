/* autores: José Henrique da Silva Braz */

#ifndef BOOL_LST_H
#define BOOL_LST_H

#include "types.h"

bool_list *bool_lst_create(int size, ...);

void bool_list_free(bool_list *list);

bool_list *bool_lst_new_entry(int *bool_pointer);

bool_list *bool_lst_concat(bool_list *entry1, bool_list *entry2);

int bool_lst_next_remendo();

void bool_lst_remenda(bool_list *lst, int value);

#endif


