
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

// 1:1 com registradores x86_64 com ILOC até onde der
void get_reg_label(int reg, char *dest) {
    switch (reg) {
    // case 0 == r0
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

// r0 => rax
// r1 => rbx

instruction_entry_t *optimize_iloc_register_usage(instruction_entry_t *instruction_list, int* node_colors, graph_t* graph) {
    instruction_entry_t *instruction_list_copy = instruction_list;

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

        instruction_list_copy = instruction_list_copy->next;
    }

    /* Prints the start of the instruction list */
    print_instr_lst(instruction_list);

    return instruction_list;
    // 1 - Simplificar os regs do ILOC (coloração de grafos) [x]
    //     1.1 Derramamento [ ]
    // 2 - Verificar salvamento de registradores no ILOC (recursão, salvar regs na pilha) [ ]
    // 3 - Mapeamento da tabela de simbolos global para o seguimento de dados do assembly (acho que é 1:1, direto) [ ]
    // 4 - Mapeamento do ILOC simplificado para x86 [ ] (funcao de print instructions x86)
}

// regs especiais = num negativo referencia: code_gen.c (valores)
// ver regs especiais no x86 e se tem correspondente, quais são

// TODO: Mudar o nome da função
// TODO: Agora temos o ILOC com regs otimizados
// TODO: Mapear regs até os regs que temos no x86_64 assembly, pros regs do ILOC
// TODO: Devolver algum código inteiro quando não for possível mapear o registrador (derramamento)