/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#ifndef LIST_H
#define LIST_H

#include "stdlib.h"
#include "types.h"

#define LIST_INITIAL_CAPACITY 10
#define LIST_REALLOC_STEP     10

list_t *list_init();

list_t *list_destroy(list_t* l);

void list_add(list_t* l, list_entry_t* entry);

void list_add_index(list_t* l, int index, list_entry_t* entry);

list_entry_t *list_get(list_t* l, int index);

#endif