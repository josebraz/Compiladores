#include <stdio.h>
#include <stdlib.h>

#include "asp.h"
#include "util.h"

void exporta(void *arvore) {
    int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    for (i = 0; i < n->size; i++) {
        printf("%p, %p\n", n, n->nodes[i]);
    }
    for (i = 0; i < n->size; i++) {
        exporta(n->nodes[i]);
    }
}

// TODO: Testar com o valgrind
void libera(void *arvore) {
    int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    for (i = 0; i < n->size; i++) {
        libera(n->nodes[i]);
    }
    
    free(n->value);
    free(n->label);
    free(n);
}
