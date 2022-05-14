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
#include "sub_expr_graph.h"
#include "asp.h"
#include "types.h"

int optimization_mode = OPT_DISABLED;

int get_optimization_flag() {
    return optimization_mode;
}

instruction_entry_t *optimize_with_windows(instruction_entry_t *code, int *update);

void optimization_setup(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-O") == 0) {
            optimization_mode = OPT_ENABLED;
        }
    }
}

instruction_entry_t *optimize_code(instruction_entry_t *code) {
    if (optimization_mode != OPT_ENABLED) return code;
    
    int update;
    do {
        update = 0;
        code = optimize_with_windows(code, &update);
    } while (update == 1);

    do {
        update = 0;
        code = sub_expr_graph_optimize(code, &update);
        // print_sub_expr_graph(graph);
    } while (update == 1);

    return code;
}

instruction_entry_t *optimize_function_code(instruction_entry_t *code) {
    // printf("#ORIGINAL\n");
    // print_instr_lst(code);

    code = optimize_code(code);

    // printf("#OPTMIZED\n");
    // print_instr_lst(code);


    code = optimize_iloc_register_usage(code);

    return code;
}

instruction_entry_t *optimize_with_windows(instruction_entry_t *code, int *update) {
    instruction_entry_t *current = code;
    while (current != NULL) {
        instruction_t *current_instr = current->entry;

        ///////////////////////////////////////////////
        // Otimização de 1 instrução
        // move o conteúdo entre o mesmo registrador
        if (strcmp(current_instr->code, "i2i") == 0 && current_instr->op1 == current_instr->op3 ) {
            current = instr_lst_remove(current);
            *update = 1;
            continue;
        }

        if ((strcmp(current_instr->code, "add") == 0 || strcmp(current_instr->code, "sub") == 0) && 
                ((current_instr->op1 == 0 && current_instr->op1_type == OT_IMED) || 
                 (current_instr->op2 == 0 && current_instr->op2_type == OT_IMED))) {
            current = instr_lst_remove(current);
            *update = 1;
            continue;
        }

        if ((strcmp(current_instr->code, "mult") == 0 || strcmp(current_instr->code, "div") == 0) && 
                ((current_instr->op1 == 1 && current_instr->op1_type == OT_IMED) || 
                 (current_instr->op2 == 1 && current_instr->op2_type == OT_IMED))) {
            current = instr_lst_remove(current);
            *update = 1;
            continue;
        }

        ///////////////////////////////////////////////
        // Otimização de 2 instruções
        instruction_t *next_instr = NULL;
        if (current->next != NULL) {
            next_instr = current->next->entry;
        } else {
            break;
        }

        // elimina load depois de store da mesma variável. exemplo:
        // storeAI r0 => rfp, 16         // Grava variável a
        // loadAI rfp, 16 => r0          // Carrega variável a
        if (strcmp(current_instr->code, "storeAI") == 0 && 
                strcmp(next_instr->code, "loadAI") == 0 &&
                current_instr->op2 == next_instr->op1 &&
                current_instr->op3 == next_instr->op2 &&
                current_instr->op1 == next_instr->op3
        ) {
            instr_lst_remove(current->next);
            *update = 1;
        }

        // elimina store depois um load da mesma variável, 
        // não mudou nada para precisar de um store. exemplo:
        // loadAI rfp, 16 => r0          // Carrega variável a
        // storeAI r0 => rfp, 16         // Grava variável a
        if (strcmp(current_instr->code, "loadAI") == 0 && 
                strcmp(next_instr->code, "storeAI") == 0 &&
                current_instr->op2 == next_instr->op1 &&
                current_instr->op3 == next_instr->op2 &&
                current_instr->op1 == next_instr->op3
        ) {
            instr_lst_remove(current->next);
            *update = 1;
        }

        ///////////////////////////////////////////////
        // Otimização de 3 instruções
        instruction_t *next_next_instr = NULL;
        if (current->next->next != NULL) {
            next_next_instr = current->next->next->entry;
        } else {
            current = current->next;
            continue;
        }

        // tentamos calcular as operações constantes. exemplo:
        // loadI 4 => r0
        // loadI 4 => r2
        // mult r0, r2 => r3
        if (strcmp(current_instr->code, "loadI") == 0 && 
                strcmp(next_instr->code, "loadI") == 0 &&
                next_next_instr->op1_type == OT_REG && 
                next_next_instr->op2_type == OT_REG && 
                (next_next_instr->op1 == current_instr->op3 || next_next_instr->op2 == current_instr->op3) &&
                (next_next_instr->op1 == next_instr->op3 || next_next_instr->op2 == next_instr->op3)
        ) {
            int value1, value2; 
            if (next_next_instr->op1 == current_instr->op3) {
                value1 = current_instr->op2;
                value2 = next_instr->op2;
            } else {
                value1 = next_instr->op2;
                value2 = current_instr->op2;
            }

            int direct_value, known_instr = 0;
            if (strcmp(next_next_instr->code, "div") == 0) {
                direct_value = value1 / value2;
                known_instr = 1;
            } else if (strcmp(next_next_instr->code, "mult") == 0) {
                direct_value = value1 * value2;
                known_instr = 1;
            } else if (strcmp(next_next_instr->code, "add") == 0) {
                direct_value = value1 + value2;
                known_instr = 1;
            } else if (strcmp(next_next_instr->code, "sub") == 0) {
                direct_value = value1 - value2;
                known_instr = 1;
            } else if (strcmp(next_next_instr->code, "and") == 0) {
                direct_value = value1 & value2;
                known_instr = 1;
            } else if (strcmp(next_next_instr->code, "or") == 0) {
                direct_value = value1 | value2;
                known_instr = 1;
            }
            if (known_instr == 1) {
                // 3 instruções viram uma de carregamento direto com o valor
                current_instr->op2 = direct_value;
                current_instr->op3 = next_next_instr->op3;
                current_instr->reg_result = next_next_instr->reg_result;

                instr_lst_remove(current->next->next);
                instr_lst_remove(current->next);
                *update = 1;
            }
        }

        current = current->next;
    }

    return code;
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