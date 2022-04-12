/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "util.h"
#include "asp.h"
#include "semantic.h"
#include "hashmap.h"
#include "code_gen.h"

void print_tree_children(void *arvore) {
	int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    for (i = 0; i < n->size; i++) {
        if (n->nodes[i] != NULL)
            printf("%p, %p\n", n, n->nodes[i]);
    }
    for (i = 0; i < n->size; i++) {
        print_tree_children(n->nodes[i]);
    }
}

void print_tree_labels(void *arvore) {
	int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    printf("%p [label=\"%s\"];\n", n, n->label);
    
    for (i = 0; i < n->size; i++) {
        print_tree_labels(n->nodes[i]);
    }
}

void generate_dot_rec(void *arvore) {
    int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    printf("\t%ld [label=\"%s\" mark=%d]\n", n, n->label, n->mark);
    
    for (i = 0; i < n->size; i++) {
        if (n->nodes[i] != NULL) {
            printf("\t%ld -> %ld\n", n, n->nodes[i]);
        }
    }
    for (i = 0; i < n->size; i++) {
        generate_dot_rec(n->nodes[i]);
    }
}

void generate_dot(void *arvore) {
    printf("digraph {\n");
    generate_dot_rec(arvore);
    printf("}\n");
}

void exporta(void *arvore) {
    // print_tree_children(arvore);
    // print_tree_labels(arvore);
    generate_dot(arvore);
    print_stack();
    print_instr_lst(((node*) arvore)->code);
}

void free_list(instruction_entry_t *head) {
    if (head != NULL) {
        free(head->entry);
        head->entry = NULL;

        if (head->next != NULL) {
            free_list(head->next);
            free(head);
        }
    }
}

void free_tree(void *arvore) {
    int i;
    node *n = (node *) arvore;

    if (n == NULL) return;
    for (i = 0; i < n->size; i++) {
        free_tree(n->nodes[i]);
    }
    
    free_node(n);
    free_list(n->code);
}

void libera(void *arvore) {
    // free_tree(arvore);
    // for (int i = 0; i < scope_stack->actual_capacity; i++) {
    //     hashmap_destroy(scope_stack->entries[i]);
    //     scope_stack->entries[i] = NULL;
    // }
    // stack_destroy(scope_stack);
}

