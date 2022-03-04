#ifndef ASP_H
#define ASP_H

typedef struct node {
    char *label;
    void *value;
    int size;
    struct node **nodes;
} node; 

void add_child(node* father, node* child);

int remove_child(node *parent, node *to_remove);

node* create_node(char *label, int nodes, ...);

node* create_node_id_array(char *value, node* index);

node* create_node_unary_ope(char *value, node* next);

node* create_leaf(void *value, char* label);

node* create_leaf_int(int value);

node* create_leaf_char(char value);

node* create_leaf_float(float value);

node* create_leaf_bool(int value, char* label);

node* create_leaf_id(char *value);

node* create_leaf_string(char *value, char* label);

node* create_leaf_spec_char(char *value, char* label);

node* create_leaf_comp_oper(char *value, char* label);

node* create_leaf_fun_call(char *value, char* label);


#endif
