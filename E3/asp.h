#ifndef ASP_H
#define ASP_H

#include "types.h"

void add_child(node* father, node* child);

int remove_child(node *parent, node *to_remove);

void print_node(node *node);

node* find_last_node_of_type(node *parent, enum node_type type);

node* create_node(char *label, enum node_type type, int nodes, ...);

node* create_node_id_array(char *value, node* index);

node* create_node_unary_ope(char *value, node* next);

node* create_node_binary_ope(char *value, node* node1, node *node2);

node* create_node_ternary_ope(char *value, node* node1, node *node2, node *node3);

node* create_node_function(char *name, node* body, node* next);

node* create_leaf(void *value, char* label);

node* create_leaf_int(int value);

node* create_leaf_char(char value);

node* create_leaf_float(float value);

node* create_leaf_bool(int value, char* label);

node* create_leaf_id(char *value);

node* create_leaf_string(char *value);

node* create_leaf_spec_char(char *value, char* label);

node* create_leaf_comp_oper(char *value, char* label);

node* create_leaf_fun_call(char *value);


#endif
