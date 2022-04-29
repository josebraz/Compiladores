
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
#define REG_EFE 11 // registrador usado para os calculos intermediários


/*
Special x86_64 regs ref: https://wiki.cdot.senecacollege.ca/wiki/X86_64_Register_and_Instruction_Quick_Start

rbp - register base pointer (start of stack)
rsp - register stack pointer (current location in stack, growing downwards)
rsi - register source index (source for data copies)
rdi - register destination index (destination for data copies)
*/

void print_x86_64_assembly_code(instruction_entry_t *instruction_list) {
    printf("\nAssembly:\n");
    instruction_entry_t *current = instruction_list;
    while (current != NULL) {
        int processed = print_assembly_instruction(current);

        for (int i = 0; i < processed; i++)
            current = current->next;
    }
}

int print_conver_fail(instruction_entry_t *instruction_lst) {
    printf(" -----------> Não rolou de imprimir: ");
    print_instruction(instruction_lst->entry);
    return 1;
}

int print_assembly_instruction(instruction_entry_t *instruction_lst) {
    return print_label(instruction_lst) ||
        print_general_instruction(instruction_lst) ||
        print_mem_instruction(instruction_lst) || 
        print_conver_fail(instruction_lst);
}

int print_label(instruction_entry_t *instruction_lst) {
    if (instruction_lst->entry->op1_type == OT_LABEL) {
        printf("L%d:\n", instruction_lst->entry->op1);
        return 1;
    }
    return 0;
}

int print_mem_instruction(instruction_entry_t *instruction_lst) {
    instruction_t *instruction = instruction_lst->entry;
    char asm_op1[10], asm_op2[10], asm_op3[10];

    print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
    print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);
    print_instruction_parameter(instruction->op3, instruction->op3_type, asm_op3);
    
    if (strcmp(instruction->code, "load") == 0) {
        printf("movl\t(%s), %s\n", asm_op2, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "loadAI") == 0) {
        printf("movl\t%d(%s), %s\n", instruction->op2, asm_op1, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "loadI") == 0) {
        printf("movl\t%s, %s\n", asm_op2, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "i2i") == 0) {
        printf("movl\t%s, %s\n", asm_op1, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "store") == 0) {
        printf("movl\t%s, (%s)\n", asm_op2, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "storeAI") == 0) {
        printf("movl\t%s, %d(%s)\n", asm_op1, instruction->op3, asm_op2);
        return 1;
    }

    return 0;
}

int print_general_instruction(instruction_entry_t *instruction_lst) {
    instruction_t *instruction = instruction_lst->entry;

    char asm_code[10], asm_op1[10], asm_op2[10];
    int is_comutative = 0;

    if (strncmp(instruction->code, "add", 3) == 0) {
        strcpy(asm_code, "addl");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "sub", 3) == 0) {
        strcpy(asm_code, "subl");
    } else if (strncmp(instruction->code, "mult", 4) == 0) {
        strcpy(asm_code, "imultl");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "div", 3) == 0) {
        strcpy(asm_code, "idivl");
    } else if (strncmp(instruction->code, "and", 3) == 0) {
        strcpy(asm_code, "andl");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "or", 2) == 0) {
        strcpy(asm_code, "orl");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "xor", 3) == 0) {
        strcpy(asm_code, "xorl");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "lshift", 6) == 0) {
        strcpy(asm_code, "sall");
    } else if (strncmp(instruction->code, "rshift", 6) == 0) {
        strcpy(asm_code, "sarl");
    } else {
        // não conhecemos essa instrução como sendo um instrução
        // geral, deve ser outra coisa, então vamos sair...
        return 0;
    }

    if (instruction->op2 == instruction->op3) {
        // Nesse caso a instrução não tá colocando no segundo operando
        // a conversão se torna bem mais fácil porque é 1:1
        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);

        printf("%s\t%s, %s\n", asm_code, asm_op1, asm_op2);
        
        return 1;
    } else if (instruction->op1 == instruction->op3 && is_comutative == 1) {
        // essas operações não importa a ordem, então da pra executar
        // em uma instrução apenas
        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);

        printf("%s\t%s, %s\n", asm_code, asm_op2, asm_op1);
    
        return 1;
    } else {
        // Esse é um caso mais chato, precisamos gravar o resultado o operando 1 em um
        // registrador intermediário, usar ele para o cálculo com o operando 2 
        // e depois mover para o operando 3 (destino correto)
        print_instruction_parameter(REG_EFE, OT_REG, asm_op2);

        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op1);
        printf("movl\t%s, %s\n", asm_op1, asm_op2);

        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        printf("%s\t%s, %s\n", asm_code, asm_op1, asm_op2);

        print_instruction_parameter(instruction->op3, instruction->op3_type, asm_op1);
        printf("movl\t%s, %s\n", asm_op2, asm_op1);

        return 1;
    }
}


void print_instruction_parameter(int op, int op_type, char *dest) {
    if (op_type == OT_IMED)
        sprintf(dest, "$%d", op);
    else {
        switch (op) {
        case RBSS:
            strcpy(dest, "%rbss");
            break;
        case RSP:
            strcpy(dest, "%rsp");
            break;
        case RFP:
            strcpy(dest, "%rbp");
            break;
        case RPC:
            strcpy(dest, "%rip");
            break;
        case 0:
            strcpy(dest, "%rax");
            break;
        case 1:
            strcpy(dest, "%rbx");
            break;
        case 2:
            strcpy(dest, "%rcx");
            break;
        case 3:
            strcpy(dest, "%rdx");
            break;
        case 4:
            strcpy(dest, "%r8");
            break;
        case 5:
            strcpy(dest, "%r9");
            break;
        case 6:
            strcpy(dest, "%r10");
            break;
        case 7:
            strcpy(dest, "%r11");
            break;
        case 8:
            strcpy(dest, "%r12");
            break;
        case 9:
            strcpy(dest, "%r13");
            break;
        case 10:
            strcpy(dest, "%r14");
            break;
        case 11:
            strcpy(dest, "%r15");
            break;
        default:
            break;
        }
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
// TODO: Colocar o "movl $0, %eax" antes de um call (pra não deixar lixo no eax)