#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "asp.h"

node* create_node(char *label, int nodes, ...) {
    printf("Create node => %s with %d nodes\n", label, nodes);
    int i;
    va_list arguments;
    
    va_start(arguments, nodes);
    
    node *new_node = (node*) malloc(sizeof(node));
    new_node->label = label;
    new_node->size = nodes;
    
    new_node->nodes = (struct node**) calloc(nodes, sizeof(node*));
    for (i = 0; i < nodes; i++) {
        new_node->nodes[i] = (struct node*) va_arg(arguments, node*);
    }
    
    va_end(arguments);
    
    return new_node;
}

node* create_leaf(void *value, char* label) {
    printf("Create leaf => %s\n", label);
    node *new_leaf = (node*) malloc(sizeof(node));
    new_leaf->label = label;
    new_leaf->value = value;
    new_leaf->size = 0;
    new_leaf->nodes = NULL;
    
    return new_leaf;
}

node* create_leaf_int(int value, char* label) {
    return create_leaf((void *) &value, label);
}


