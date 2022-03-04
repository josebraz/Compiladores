#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "asp.h"

void add_child(node *father, node *child) {
    int i;
    int size = father->size;
    struct node **new_childrens = (struct node**) calloc(size + 1, sizeof(node*));
    for (i = 0; i < size; i++) {
        new_childrens[i] = father->nodes[i];
    }
    new_childrens[size] = child;
    
    if (father->nodes != NULL) {
        free(father->nodes);
    }
    
    father->nodes = new_childrens;
}

node* create_node(char *label, int nodes, ...) {
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
    
    printf("Create node => %s with %d nodes -- %p\n", label, nodes, new_node);
    
    return new_node;
}

node* create_node_id_array(char *value, node* index) {
    node* id_node = create_leaf_id(value);
    return create_node("[]", 2, id_node, index);
}

node* create_node_unary_ope(char *value, node* next) {
    return create_node(value, 1, next);
}

node* create_leaf(void *value, char* label) {
    node *new_leaf = (node*) malloc(sizeof(node));
    new_leaf->label = label;
    new_leaf->value = value;
    new_leaf->size = 0;
    new_leaf->nodes = NULL;
    
    printf("Create leaf => %s -- %p\n", label, new_leaf);
    
    return new_leaf;
}

node* create_leaf_int(int value) {
    char *label = malloc(20 * sizeof(char));
    sprintf(label, "%d", value);
    return create_leaf((void *) &value, label);
}

node* create_leaf_char(char value) {
    char *label = malloc(2 * sizeof(char));
    label[0] = value;
    label[1] = '\0';
    return create_leaf((void *) &value, label);
}

node* create_leaf_float(float value) {
    char *label = malloc(20 * sizeof(char));
    sprintf(label, "%f", value);
    return create_leaf((void *) &value, label);
}

node* create_leaf_bool(int value, char* label) {
    return create_leaf((void *) &value, label);
}

node* create_leaf_id(char *value) {
    return create_leaf((void *) value, value);
}

node* create_leaf_string(char *value, char* label) {
    return create_leaf((void *) value, label);
}

node* create_leaf_spec_char(char *value, char* label) {
    return create_leaf((void *) value, label);
}

node* create_leaf_comp_oper(char *value, char* label) {
    return create_leaf((void *) value, label);
}

node* create_leaf_fun_call(char *value, char* label) {
    return create_leaf((void *) value, label);
}


