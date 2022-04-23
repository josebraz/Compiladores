
/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "arch_code_gen.h"
#include "types.h"

#define REG_NUM 16
#define MAX_REGISTER_NAME_SIZE 10

void get_reg_label(int reg, char *dest) {
    switch (reg) {
    case 0:
        strcpy(dest, "rax");
        break;
    case 1:
        strcpy(dest, "rbx");
        break;
    default:
        break;
    }
}

instruction_entry_t *arch_convert_code(instruction_entry_t *instruction_list, int* node_colors, graph_t* graph) {
    printf("\n\narch_convert_code");

    if (graph == NULL)
    {
        printf("\n\nParameter \"graph\" is NULL, function call: arch_convert_code. Exiting");
        return -1;
    }

    if (instruction_list == NULL)
    {
        printf("\n\nParameter \"instruction_list\" is NULL, function call: arch_convert_code. Exiting");
        return -1;
    }
    
    int i = 0;

    printf("\nRegister usage:\n");

    /* loop through node_colors, whose size is the same as graph->size */
    while (i < graph->size)
    {
        /* If the color in position i is != than index, a register can be re-used */
        /* And also the instruction op_type is OT_REG */
        if (node_colors[i] != i && instruction_list != NULL)
        {
            /* If the left side of the instruction is a registrator */
            if (instruction_list->entry->op1_type == OT_REG)
            {
                char register_name[MAX_REGISTER_NAME_SIZE];

                sprintf(register_name, "%d", node_colors[i]);

                /* Sets the register to be used as the register used before */
                strcpy(instruction_list->entry->code, register_name);

                /* DEBUG*/
                printf("r%s, ", register_name);
            }
        }

        i++;
        
        instruction_list->next;
    }

    // TODO: Conferir print
    // TODO: Conferir register name
    return instruction_list;
}