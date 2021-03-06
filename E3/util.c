/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "util.h"
#include "asp.h"

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
    
    printf("\t%ld [label=\"%s\" type=%d]\n", n, n->label, n->type);
    
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
}

void free_node(node *n) {
    if (n != NULL) {
        if (n->value != NULL) free(n->value);
        if (n->label != NULL) free(n->label);
        if (n->nodes != NULL) free(n->nodes);
        free(n);
    }
}

void libera(void *arvore) {
    int i;
    node *n = (node *) arvore;

    if (n == NULL) return;

    for (i = 0; i < n->size; i++) {
        libera(n->nodes[i]);
    }
    
    free_node(n);
}
