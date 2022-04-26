
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

// Special ILOC regs definition
#include "code_gen.h"

#define REG_NUM 16

int char_counter = 0;

/*
Special x86_64 regs ref: https://wiki.cdot.senecacollege.ca/wiki/X86_64_Register_and_Instruction_Quick_Start

rbp - register base pointer (start of stack)
rsp - register stack pointer (current location in stack, growing downwards)
rsi - register source index (source for data copies)
rdi - register destination index (destination for data copies)
*/

void print_x86_64_assembly_code(instruction_entry_t *instruction_list) {
    printf("\nAssembly:\n");
    while (instruction_list != NULL) {
        instruction_t *current_instruction = instruction_list->entry;

        if (instruction_list->entry != NULL) {
            print_assembly_instruction(current_instruction);
        }

        instruction_list = instruction_list->next;
    }
}

void print_assembly_instruction(instruction_t *instruction) {
    // store a, b = mov a, b
    print_label(instruction);
    print_store(instruction);
    print_add(instruction);
}

void print_label(instruction_t *instruction) {
    if (instruction->op1_type == OT_LABEL) {
        char_counter += printf("L%d:\n", instruction->op1);
    }
}

void print_store(instruction_t *instruction) {
    if (strncmp(instruction->code, "store", 5) == 0) {
        char_counter += printf("mov ");
        print_instruction_parameter((int)instruction->op1, instruction->op1_type);
        char_counter += printf(",");
        print_instruction_parameter(instruction->op2, instruction->op2_type);
        printf("\n");
    }
}

void print_storeAI(instruction_t *instruction) {
    // storeAI: r0 => rfp, 12 // Memoria(rfp + 12) = r0
    if (strncmp(instruction->code, "storeAI", 7) == 0) {
        // add the immediate address
        // need to have the add address on some register than mov it to the store register...
        char_counter += printf("add");
        print_instruction_parameter(instruction->op1, instruction->op1_type);
        char_counter += printf(",");
        print_instruction_parameter(instruction->op2, instruction->op2_type);

        printf("\n");

        // print move
        char_counter += printf("mov ");
        print_instruction_parameter(instruction->op1, instruction->op1_type);
        char_counter += printf(",");
        print_instruction_parameter(instruction->op2, instruction->op2_type);

        printf("\n");
    }
    // storeAI: r0 => rfp, 12 // Memoria(rfp + 12) = r0
    // storeai
    // Como traduzir isso para MOV?
    // store normal: Memoria(r2) = r1

    // add rfp, 12
    // mov rfp, r0
}

void print_instruction_parameter(int op, int op_type) {
    // TODO: special registers on x86_64
    if (op_type == OT_IMED)
        char_counter += printf(" %d", op);
    else if (op == RBSS)
        char_counter += printf(" rbss");
    else if (op == RFP)
        char_counter += printf(" rfp");
    else if (op == RPC)
        char_counter += printf(" rpc");
    else {
        char register_name[10];
        get_x86_64_assembly_register_name(op, register_name);
        printf(" %s", register_name);
    }
}

void print_add(instruction_t *instruction) {
    if (strncmp(instruction->code, "add", 3) == 0) {
        // add r1, r2 => r3 // r3 = r1 + r2

        // add r1, r2 // r1 = source, destiny = r2
        char_counter += printf("add");
        print_instruction_parameter(instruction->op1, instruction->op1_type);
        char_counter += printf(" ,");
        print_instruction_parameter(instruction->op2, instruction->op2_type);

        printf("\n");

        // add r2, r3 // r2 = source, destiny = r3
        char_counter += printf("add");
        print_instruction_parameter(instruction->op2, instruction->op2_type);
        char_counter += printf(" ,");
        print_instruction_parameter(instruction->op3, instruction->op3_type);

        printf("\n");
    }
}

/**
 * @brief Get the x86 64 assembly register name object 
 * There are 12 registers to use, 4 of them are the special registers on this file header
 * @param reg 
 * @param dest 
 */
void get_x86_64_assembly_register_name(int reg, char *dest) {
    switch (reg) {
        case 0:
            strcpy(dest, "rax");
            break;
        case 1:
            strcpy(dest, "rbx");
            break;
        case 2:
            strcpy(dest, "rcx");
            break;
        case 3:
            strcpy(dest, "rdx");
            break;
        case 4:
            strcpy(dest, "r8");
            break;
        case 5:
            strcpy(dest, "r9");
            break;
        case 6:
            strcpy(dest, "r10");
            break;
        case 7:
            strcpy(dest, "r11");
            break;
        case 8:
            strcpy(dest, "r12");
            break;
        case 9:
            strcpy(dest, "r13");
            break;
        case 10:
            strcpy(dest, "r14");
            break;
        case 11:
            strcpy(dest, "r15");
            break;
        default:
            break;
    }
}

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