#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

stack_t* stack_init() {
    stack_t* stack = (stack_t *) malloc(sizeof(stack_t));

    if (stack == NULL) {
        perror("Não foi possivel criar a pilha!");
        return NULL;
    }

    stack->actual_capacity = STACK_INITIAL_CAPACITY;
    stack->index = -1;
    stack->entries = (stack_entry_t **) malloc(sizeof(stack_entry_t*) * STACK_INITIAL_CAPACITY);

    if (stack->entries == NULL) {
        perror("Não foi possivel alocar memória inicial para as entradas da pilha!");
        return NULL;
    }

    return stack;
}

stack_t* stack_destroy(stack_t* s) {
    if (stack_is_empty(s) == 0) {
        for (int i = 0; i <= s->index; i++) {
            free(s->entries[i]);
        }
    }
    free(s->entries);
    free(s);
    
    return NULL;
}

stack_entry_t *stack_pop(stack_t *s) {
    if (stack_is_empty(s) == 1) {
        return NULL;
    } else {
        return s->entries[s->index--];
    }
}

stack_entry_t *stack_peek(stack_t *s) {
    if (stack_is_empty(s) == 1) {
        return NULL;
    } else {
        return s->entries[s->index];
    }
}

void stack_alloc_more_mem(stack_t *s) {
    size_t new_capacity = s->actual_capacity + STACK_REALLOC_STEP;
    s->entries = (stack_entry_t **) realloc(s->entries, sizeof(stack_entry_t*) * new_capacity);
    if (s->entries == NULL) {
        perror("Não foi possivel alocar mais memória para a pilha!");
        exit(1);
    }
    s->actual_capacity = new_capacity;
}

void stack_push(stack_t *s, stack_entry_t *entry) {
    if (stack_is_full(s) == 1)
        stack_alloc_more_mem(s);
    s->entries[++s->index] = entry;
}

int stack_is_empty(stack_t *s) {
    if (s->index <= -1) {
        return 1;
    } else {
        return 0;
    }
}

int stack_is_full(stack_t *s) {
    if (s->actual_capacity == s->index+1) {
        return 1;
    } else {
        return 0;
    }
}