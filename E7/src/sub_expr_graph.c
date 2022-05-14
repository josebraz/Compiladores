/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sub_expr_graph.h"
#include "instr_lst.h"
#include "types.h"

void print_sub_expr_graph(sub_expr_graph *graph) {
    printf("strict graph {\n");
    for (int i = 0; i < graph->size; i++) {
        sub_expr_node *node = graph->nodes[i];
        printf("\t%ld [label=\"%s (REG=%d, VERSION=%d)\"]\n", (long)node, node->operation, node->reg, node->version);
        for (int j = 0; j < node->neigh_size; j++) {
            printf("\t%ld -- %ld\n", (long) node, (long) node->neigh[j]);
        }
    }
    printf("}\n");
}

sub_expr_node *sub_expr_graph_find_node(sub_expr_graph *graph, int reg, int version) {
    for (int i = 0; i < graph->size; i++) {
        sub_expr_node *node = graph->nodes[i];
        if (node->reg == reg && node->version == version) {
            return node;
        } 
    }
    return NULL;
}

sub_expr_node *get_neigh_same_operation(sub_expr_node *node1, sub_expr_node *node2, char* operation) {
    if (node1 == NULL || node2 == NULL) return NULL;
    for (int i = 0; i < node1->neigh_size; i++) {
        sub_expr_node *parent1 = node1->neigh[i];
        if (strcmp(parent1->operation, operation) == 0) {
            for (int j = 0; j < node2->neigh_size; j++) {
                sub_expr_node *parent2 = node2->neigh[j];
                if (strcmp(parent2->operation, operation) == 0 && parent1 == parent2) {
                    return parent1;
                }
            }
        }
    }
    return NULL;
}

void sub_expr_graph_add_node(sub_expr_graph *graph, sub_expr_node *node) {
    graph->nodes[graph->size++] = node;
}

void sub_expr_graph_add_neigh(sub_expr_node *node1, sub_expr_node *node2) {
    node1->neigh[node1->neigh_size++] = node2;
    node2->neigh[node2->neigh_size++] = node1;
}

void sub_expr_graph_free(sub_expr_graph *graph) {
    for (int i = 0; i < graph->size; i++) {
        sub_expr_node *node = graph->nodes[i];
        free(node);
    }
    free(graph);
}

instruction_entry_t *sub_expr_graph_optimize(instruction_entry_t *code, int *update) {
    int size = instr_lst_count_regs(code);
    int index = 0;
    int *reg_versions = (int *) calloc(size, sizeof(int));
    sub_expr_graph *graph = (sub_expr_graph *) calloc(1, sizeof(sub_expr_graph));

    sub_expr_node *temp = NULL, *child1 = NULL, *child2 = NULL;
    instruction_entry_t *current = code;
    instruction_t *instr = NULL;
    while (current != NULL) {
        instr = current->entry;
        int reg_result = instr->reg_result;
        if (reg_result >= 0) {
            // incrementa a versão o registrador quando uma instrução alterar ele
            reg_versions[reg_result] += 1;
        }
        // para simplicidade, só consideramos as operações o tipo CODE op1, op2 => op3
        if (reg_result >= 0 && instr->op1_type == OT_REG && instr->op2_type == OT_REG) {
            // procura no grafo os registradores com a versão que estamos usando
            child1 = sub_expr_graph_find_node(graph, instr->op1, reg_versions[instr->op1]);
            child2 = sub_expr_graph_find_node(graph, instr->op2, reg_versions[instr->op2]);

            sub_expr_node *parent = get_neigh_same_operation(child1, child2, instr->code);
            if (parent != NULL) {
                // procura se os dois tem um vizinho com a mesma operação
                // isso significa que da pra aproveitar a operação
                int original_reg = instr->reg_result;
                int new_reg = parent->reg;
                current = instr_lst_remove(current);
                instr_lst_change_reg(current, original_reg, new_reg);
                *update = 1;
            } else {
                if (child1 == NULL) {
                    child1 = (sub_expr_node *) calloc(1, sizeof(sub_expr_node));
                    child1->reg = instr->op1;
                    child1->version = reg_versions[instr->op1];
                    if (instr->mark_property != NULL) {
                        strcpy(child1->operation, instr->mark_property);
                    }
                    sub_expr_graph_add_node(graph, child1);
                } 

                if (child2 == NULL) {
                    child2 = (sub_expr_node *) calloc(1, sizeof(sub_expr_node));
                    child2->reg = instr->op2;
                    child2->version = reg_versions[instr->op2];
                    if (instr->mark_property != NULL) {
                        strcpy(child2->operation, instr->mark_property);
                    }
                    sub_expr_graph_add_node(graph, child2);
                }

                temp = (sub_expr_node *) calloc(1, sizeof(sub_expr_node));
                strcpy(temp->operation, instr->code);
                temp->reg = reg_result;
                temp->version = reg_versions[reg_result];
                sub_expr_graph_add_neigh(child1, temp);
                sub_expr_graph_add_neigh(child2, temp);
                sub_expr_graph_add_node(graph, temp);
            }
        } else if (reg_result >= 0) {
            temp = (sub_expr_node *) calloc(1, sizeof(sub_expr_node));
            temp->reg = instr->reg_result;
            temp->version = reg_versions[instr->reg_result];
            if (instr->mark_property != NULL) {
                strcpy(temp->operation, instr->mark_property);
            }
            sub_expr_graph_add_node(graph, temp);
        }
        index++;
        current = current->next;
    }

    // print_sub_expr_graph(graph);
    free(reg_versions);
    sub_expr_graph_free(graph);

    return code;
}