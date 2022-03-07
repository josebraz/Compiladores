#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "asp.h"
#include "types.h"

int remove_child(node *parent, node *to_remove) {
    int fold = 0;
    int i, j;
    int size = parent->size;
    struct node **new_childrens;
    
    if (parent == NULL || to_remove == NULL || size == 0) return 0;
    
    for (i = 0; i < size; i++) {
        if (parent->nodes[i] == to_remove) {
            fold = 1;
            break;
        }
    }
    
    if (fold == 1) {
        if (size == 1) {
            free(parent->nodes);
            parent->nodes = NULL;
            parent->size = 0;
        } else {
            new_childrens = (struct node**) calloc(size - 1, sizeof(node*));
            j = 0;
            for (i = 0; i < size; i++) {
                if (parent->nodes[i] != to_remove) {
                    new_childrens[j++] = parent->nodes[i];
                }
            }
            free(parent->nodes);
            parent->nodes = new_childrens;
            parent->size = size - 1;
        }
        return 1;
    } else {
        return 0;
    }
}

void add_child(node *father, node *child) {
    if (father == NULL || child == NULL) return;
    
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
    father->size = size + 1;
}

void print_node(node *node) {
    struct node *child;
    int i, size;
    
    if (node == NULL) {
        printf("NULL\n");
    } else {
        printf("label: %s type %d, children: ", node->label, node->type);
        if (node->nodes != NULL) {
            size = node->size;
            for (i = 0; i < size; i++) {
                child = node->nodes[i];
                if (child != NULL && child->label != NULL) {
                    printf("%s, ", child->label);
                } else {
                    printf("NULL, ");
                }
            }
        } else {
            printf("NULL");
        }
        printf("\n");
    }
}

node* find_last_node_of_type(node *parent, enum node_type type) {
    if (parent == NULL) return NULL;
    
    if (parent->size > 0) { // o nodo está no meio, chama recursão
        node *child = parent->nodes[parent->size-1];
        node *fold = find_last_node_of_type(child, type);
        
        // Vem testando de baixo pra cima
        if (fold == NULL && child->type == type) {
            return child;
        } else {
            return fold;
        }
    } else { // o nodo é folha
        if (parent->type == type) {
            return parent;
        } else {
            return NULL;
        }
    }
}

node* create_node(char *label, enum node_type type, int nodes, ...) {
    int i;
    va_list arguments;
    
    va_start(arguments, nodes);
    
    node *new_node = (node*) malloc(sizeof(node));
    new_node->label = strdup(label);
    new_node->size = nodes;
    new_node->value = NULL;
    new_node->type = type;
    
    new_node->nodes = (struct node**) calloc(nodes, sizeof(node*));
    for (i = 0; i < nodes; i++) {
        new_node->nodes[i] = (struct node*) va_arg(arguments, node*);
    }
    
    va_end(arguments);

    return new_node;
}

node* create_node_id_array(char *value, node* index) {
    node* id_node = create_leaf_id(value);
    return create_node("[]", ARRAY_T, 2, id_node, index);
}

node* create_node_unary_ope(char *value, node* next) {
    return create_node(value, EXPRES_T, 1, next);
}

node* create_node_binary_ope(char *value, node* node1, node *node2) {
    return create_node(value, EXPRES_T, 2, node1, node2);
}

node* create_node_ternary_ope(char *value, node* node1, node *node2, node *node3) {
    return create_node(value, EXPRES_T, 3, node1, node2, node3);
}

node* create_node_function(char *name, node* body, node* next) {
    node *new_node = create_node(name, EXPRES_T, 2, body, next); 
    free(name);
    return new_node;
}

node* create_leaf(void *value, char* label) {
    node *new_leaf = (node*) malloc(sizeof(node));
    new_leaf->label = label;
    new_leaf->value = value;
    new_leaf->size = 0;
    new_leaf->nodes = NULL;
    new_leaf->type = LITERAL_T;

    return new_leaf;
}

node* create_leaf_int(int value) {
    char *label = malloc(20 * sizeof(char));
    sprintf(label, "%d", value);
    int *value_ref = malloc(sizeof(int));
    *value_ref = value;
    return create_leaf((void *) value_ref, label);
}

node* create_leaf_char(char value) {
    char *label = malloc(2 * sizeof(char));
    label[0] = value;
    label[1] = '\0';
    char *value_ref = malloc(sizeof(char));
    *value_ref = value;
    return create_leaf((void *) value_ref, label);
}

node* create_leaf_float(float value) {
    char *label = malloc(20 * sizeof(char));
    sprintf(label, "%f", value);
    float *value_ref = malloc(sizeof(float));
    *value_ref = value;
    return create_leaf((void *) value_ref, label);
}

node* create_leaf_bool(int value, char* label) {
    int *value_ref = malloc(sizeof(int));
    *value_ref = value;
    return create_leaf((void *) value_ref, strdup(label));
}

node* create_leaf_id(char *value) {
    return create_leaf((void *) value, strdup(value));
}

node* create_leaf_string(char *value) {
    return create_leaf((void *) value, strdup(value));
}

node* create_leaf_spec_char(char *value, char* label) {
    return create_leaf((void *) value, strdup(label));
}

node* create_leaf_comp_oper(char *value, char* label) {
    return create_leaf((void *) value, strdup(label));
}

node* create_leaf_fun_call(char *value, char* label) {
    return create_leaf((void *) value, strdup(label));
}


