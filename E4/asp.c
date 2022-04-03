/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "asp.h"
#include "types.h"

node *inner_scope_start = NULL;
node *inner_scope_last_start = NULL;
node *inner_scope_end = NULL;
node *inner_scope_last_end = NULL;

void asp_scope_clear() {
    inner_scope_start = NULL;
    inner_scope_last_start = NULL;
    inner_scope_end = NULL;
    inner_scope_last_end = NULL;
}

void asp_scope_completed(node *start_node) {
    inner_scope_last_start = inner_scope_start;
    inner_scope_start = start_node;
    // printf("# asp_scope_completed start: %s ", start_node->label);
    // if (inner_scope_last_start != NULL) {
    //     printf("last start %s", inner_scope_last_start->label);
    // }
    // printf("\n");
}

void asp_scope_end(node *end_node) {
    if (inner_scope_end != inner_scope_last_start) {
        inner_scope_last_end = inner_scope_end;
    }
    inner_scope_end = end_node;
    // printf("# asp_scope_end end: %s ", end_node->label);
    // if (inner_scope_last_end != NULL) {
    //     printf("last end %s", inner_scope_last_end->label);
    // }
    // printf("\n");
}

node *asp_stmt_list(node *head, node *tail) {
    // printf("# asp_stmt_list - ");
    // if (head != NULL) {
    //     printf("HEAD %s ", head->label);
    // } else {
    //     printf("HEAD NULL ");
    // }
    // if (tail != NULL) {
    //     printf("TAIL %s", tail->label);
    // } else {
    //     printf("TAIL NULL");
    // }
    // printf("\n");

    if (head == NULL) return tail;
    
    if (head == inner_scope_start && inner_scope_last_end != NULL) {
        add_child(inner_scope_last_end, tail);
    } else {
        if (head == inner_scope_last_start) {
            add_child(inner_scope_last_end, tail);
        } else {
            add_child(head, tail);
        }
    }
    return head;
}

node *next_node(node *parent) {
    if (parent->nodes != NULL) {
        return parent->nodes[parent->size-1];
    } else {
        return NULL;
    }
}

node *remove_uninit_decl_var(node *n) {
    node *root = NULL;
    node *parent = NULL;
    node *p = n;
    while (p != NULL) {
        if (p->mark == DECL_VAR_T && parent != NULL) {
            parent->nodes[parent->size-1] = p->nodes[p->size-1];
            free_node(p);
        }
        if (p->mark != DECL_VAR_T) {
            parent = p;
            if (root == NULL) {
                root = p;
            }
        }
        
        p = next_node(p);
    }
    return root;
}

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

node *add_child(node *father, node *child) {
    if (father == NULL || child == NULL) return NULL;
    
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

    return father;
}

void print_node(node *node) {
    struct node *child;
    int i, size;
    
    if (node == NULL) {
        printf("NULL\n");
    } else {
        printf("label: %s type %d, children: ", node->label, node->mark);
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

node* find_last_node_of_type(node *parent, enum node_mark mark) {
    if (parent == NULL) return NULL;
    
    if (parent->size > 0) { // o nodo está no meio, chama recursão
        node *child = parent->nodes[parent->size-1];
        node *fold = find_last_node_of_type(child, mark);
        
        // Vem testando de baixo pra cima
        if (fold == NULL && child->mark == mark) {
            return child;
        } else {
            return fold;
        }
    } else { // o nodo é folha
        if (parent->mark == mark) {
            return parent;
        } else {
            return NULL;
        }
    }
}

node* create_node(char *label, enum node_mark mark, int nodes, ...) {
    int i;
    va_list arguments;
    
    va_start(arguments, nodes);
    
    node *new_node = (node*) malloc(sizeof(node));
    new_node->label = strdup(label);
    new_node->size = nodes;
    new_node->value = NULL;
    new_node->mark = mark;
    
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
    new_leaf->mark = LITERAL_T;
    new_leaf->type = DT_UNKNOWN;

    return new_leaf;
}

node* create_leaf_type(char *ident, enum data_type type) {
    node *leaf = create_leaf((void *) ident, strdup(ident));
    leaf->type = type;
    return leaf;
}

node* create_node_array_decl(char *ident, int size) {
    node *id_node = create_leaf_id(ident);
    node *size_node = create_leaf_int(size); 
    return create_node("[]", ARRAY_T, 2, id_node, size_node);
}

node* create_leaf_int(int value) {
    char *label = malloc(20 * sizeof(char));
    sprintf(label, "%d", value);
    int *value_ref = malloc(sizeof(int));
    *value_ref = value;
    node *id =  create_leaf((void *) value_ref, label);
    id->type = DT_INTEGER;
    return id;
}

node* create_leaf_char(char value) {
    char *label = malloc(2 * sizeof(char));
    label[0] = value;
    label[1] = '\0';
    char *value_ref = malloc(sizeof(char));
    *value_ref = value;
    node *id = create_leaf((void *) value_ref, label);
    id->type = DT_CHAR;
    return id;
}

node* create_leaf_float(float value) {
    char *label = malloc(20 * sizeof(char));
    sprintf(label, "%f", value);
    float *value_ref = malloc(sizeof(float));
    *value_ref = value;
    node *id = create_leaf((void *) value_ref, label);
    id->type = DT_FLOAT;
    return id;
}

node* create_leaf_bool(int value, char* label) {
    int *value_ref = malloc(sizeof(int));
    *value_ref = value;
    node *id = create_leaf((void *) value_ref, strdup(label));
    id->type = DT_BOOL;
    return id;
}

node* create_leaf_id(char *value) {
    node *id = create_leaf((void *) value, strdup(value));
    id->mark = VAR_T;
    return id;
}

node* create_leaf_decl_var(char *value) {
    node *id = create_leaf((void *) value, strdup(value));
    id->mark = DECL_VAR_T;
    return id;
}

node* create_leaf_string(char *value) {
    node *id = create_leaf((void *) value, strdup(value));
    id->type = DT_STRING;
    return id;
}

node* create_leaf_fun_call(char *value, node* params) {
    char *label = calloc(strlen(value) + 6, sizeof(char));
    strcpy(label, "call ");
    strcat(label, value);
    node *leaf = create_leaf((void *) value, label);
    add_child(leaf, params);
    leaf->mark = FUN_CALL_T;
    return leaf;
}

void free_node(node *n) {
    if (n != NULL) {
        if (n->value != NULL) free(n->value);
        if (n->label != NULL) free(n->label);
        if (n->nodes != NULL) free(n->nodes);
        free(n);
    }
}

