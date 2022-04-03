#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_init() {
    list_t* list = (list_t *) malloc(sizeof(list_t));

    if (list == NULL) {
        perror("Não foi possivel criar a lista!");
        return NULL;
    }

    list->actual_capacity = LIST_INITIAL_CAPACITY;
    list->size = 0;
    list->entries = (list_entry_t **) malloc(sizeof(list_entry_t*) * LIST_INITIAL_CAPACITY);

    if (list->entries == NULL) {
        perror("Não foi possivel alocar memória inicial para as entradas da lista!");
        return NULL;
    }

    return list;
}

list_t *list_destroy(list_t* s) {
    for (int i = 0; i < s->size; i++) {
        free(s->entries[i]);
    }
    free(s->entries);
    free(s);
    
    return NULL;
}

void list_alloc_more_mem(list_t *s) {
    size_t new_capacity = s->actual_capacity + LIST_REALLOC_STEP;
    s->entries = (list_entry_t **) realloc(s->entries, sizeof(list_entry_t*) * new_capacity);
    if (s->entries == NULL) {
        perror("Não foi possivel alocar mais memória para a list!");
        exit(1);
    }
    s->actual_capacity = new_capacity;
}

void list_add(list_t* l, list_entry_t* entry) {
    if (l->actual_capacity <= l->size) {
        list_alloc_more_mem(l);
    }
    l->entries[l->size++] = entry;
}

void list_add_index(list_t* l, int index, list_entry_t* entry) {
    if (index >= l->size) {
        list_add(l, entry);
    } else {
        if (l->actual_capacity <= l->size) {
            list_alloc_more_mem(l);
        }
        for (int i = l->size; i >= index; i--) {
            l->entries[i] = l->entries[i-1];
        }
        l->entries[index] = entry;
        l->size++;
    }
}

list_entry_t *list_get(list_t* l, int index) {
    if (index < l->size && index >= 0) {
        return l->entries[index];
    } else {
        return NULL;
    }
}