/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "util.h"
#include "asp.h"
#include "instr_lst.h"
#include "semantic.h"
#include "hashmap.h"
#include "code_gen.h"

void print_tree_children(void *arvore) {
	int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    for (i = 0; i < n->size; i++) {
        if (n->nodes[i] != NULL) {
            printf("%p, %p\n", n, n->nodes[i]);
        }
    }
    if (n->next != NULL) {
        printf("%p, %p\n", n, n->next);
    }

    for (i = 0; i < n->size; i++) {
        print_tree_children(n->nodes[i]);
    }
    if (n->next != NULL) {
        print_tree_children(n->next);
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
    if (n->next != NULL) {
        print_tree_labels(n->next);
    }
}

void generate_dot_rec(void *arvore) {
    int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    printf("\t%ld [label=\"%s\" type=%d mark=%d]\n", n, n->label, n->type, n->mark);
    
    for (i = 0; i < n->size; i++) {
        if (n->nodes[i] != NULL) {
            printf("\t%ld -> %ld\n", n, n->nodes[i]);
        }
    }
    if (n->next != NULL) {
        printf("\t%ld -> %ld\n", n, n->next);
    }

    for (i = 0; i < n->size; i++) {
        generate_dot_rec(n->nodes[i]);
    }
    if (n->next != NULL) {
        generate_dot_rec(n->next);
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
    // print_stack();
    print_instr_lst(((node*) arvore)->code);
}

void free_tree(node *n) {
    int i;

    if (n == NULL) return;
    for (i = 0; i < n->size; i++) {
        free_tree(n->nodes[i]);
    }
    if (n->next != NULL) {
        free_tree(n->next);
    }
    
    free_node(n);
}

void libera(void *arvore) {
    node *n = (node *) arvore;
    instr_lst_free(n->code);
    n->code = NULL;
    free_tree(arvore);
    free_scopes();
}

