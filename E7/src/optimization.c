/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "optimization.h"
#include "code_gen.h"
#include "bool_lst.h"
#include "instr_lst.h"
#include "semantic.h"
#include "depend_graph.h"
#include "asp.h"
#include "types.h"

int optimization_mode = OPT_DISABLED;

void optimization_setup(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-O") == 0) {
            optimization_mode = OPT_ENABLED;
        }
    }
}

instruction_entry_t *optimize_function_code(instruction_entry_t *code) {
    if (optimization_mode == OPT_ENABLED) {

    }
    return optimize_iloc_register_usage(code);
}

instruction_entry_t *optimize_iloc_register_usage(instruction_entry_t *code) {
    graph_t *graph = generate_depend_graph(code);

    int *node_colors = NULL;

    // tenta colorir o grafo com 3 cores primeiro e vai aumentando
    int result = 0;
    int colors = 2;
    while (result == 0) {
        colors++;
        result = try_color_graph(colors, graph, &node_colors);
    }

    instruction_entry_t *instruction_list_copy = code;

    /* loop through node_colors, whose size is the same as graph->size */
    while (instruction_list_copy != NULL)
    {
        instruction_t *current_instruction = instruction_list_copy->entry;

        /* Operand type is REGISTER and the index >= 0 means its a regular temp reg */
        /* special registers are negative */
        if (current_instruction->op1_type == OT_REG && current_instruction->op1 >= 0)
            current_instruction->op1 = node_colors[current_instruction->op1];

        if (current_instruction->op2_type == OT_REG && current_instruction->op2 >= 0)
            current_instruction->op2 = node_colors[current_instruction->op2];

        if (current_instruction->op3_type == OT_REG && current_instruction->op3 >= 0)
            current_instruction->op3 = node_colors[current_instruction->op3];
        
        if (current_instruction->reg_result >= 0) {
            current_instruction->reg_result = node_colors[current_instruction->reg_result];
        }

        instruction_list_copy = instruction_list_copy->next;
    }

    free_depend_graph(graph);
    if (node_colors != NULL) {
        free(node_colors);
    }

    return code;
}