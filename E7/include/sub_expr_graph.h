/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/


#ifndef SUB_EXPR_GRAPH_H
#define SUB_EXPR_GRAPH_H

#include "types.h"

typedef struct sub_expr_node {
    char operation[10];  // qual a operação executada (add, sub, mult, =)
    int reg;             // o número que representa o temporário 
    int version;         // a versão do temporário
    int neigh_size;      // quantos vizinho esse nodo tem
    struct sub_expr_node *neigh[100];
} sub_expr_node;

typedef struct sub_expr_graph {
    sub_expr_node *nodes[100];
    int size;
} sub_expr_graph;

void print_sub_expr_graph(sub_expr_graph *graph);

sub_expr_node *sub_expr_graph_find_node(sub_expr_graph *graph, int reg, int version);

sub_expr_node *get_neigh_same_operation(sub_expr_node *node1, sub_expr_node *node2, char* operation);

void sub_expr_graph_add_node(sub_expr_graph *graph, sub_expr_node *node);

void sub_expr_graph_add_neigh(sub_expr_node *node1, sub_expr_node *node2);

instruction_entry_t *sub_expr_graph_optimize(instruction_entry_t *code, int *update);

#endif