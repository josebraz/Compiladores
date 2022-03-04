#include <stdio.h>
#include <stdlib.h>

#include "asp.h"
#include "util.h"

void print_tree_children(void *arvore) {
	int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    for (i = 0; i < n->size; i++) {
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

void exporta(void *arvore) {
    print_tree_children(arvore);
    print_tree_labels(arvore);
}

// TODO: Testar com o valgrind
void libera(void *arvore) {
//     int i;
//     node *n = (node *) arvore;
//     
//     if (n == NULL) return;
//     
//     for (i = 0; i < n->size; i++) {
//         libera(n->nodes[i]);
//     }
//     
//     free(n->value);
//     free(n->label);
//     free(n);
}
