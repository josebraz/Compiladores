
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
#include "semantic.h"
#include "types.h"
#include "hashmap.h"
#include "instr_lst.h"

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

int print_conver_fail(instruction_entry_t *instruction_lst);

void print_global_var() {
    stack_entry_t * global_scope = current_scope();

    if (global_scope != NULL) {
        // não não temos inicialização de variável global
        // vai ser apenas declarar seus nomes e tamanho
        int fold = 0;
        int index = 0;
        while (fold < global_scope->size) {
            hashmap_entry_t *entry = global_scope->values[index++];
            if (entry != NULL) {
                if (entry->value->nature == NT_VARIABLE) {
                    printf("\t.comm\t%s,%d,%d\n", entry->key, 
                        entry->value->men_size, entry->value->men_size);
                }
                fold++;
            }
        }
    }
}

void print_x86_64_assembly_code(instruction_entry_t *instruction_list) {
    print_global_var();

    instruction_entry_t *current = instruction_list;
    while (current != NULL) {
        int processed = print_assembly_instruction(current);

        for (int i = 0; i < processed; i++)
            current = current->next;
    }
}

/**
 * @brief 
 * 
 * @param instruction_lst 
 * @return int Quantas instr. do iloc pode pular
 */
int print_assembly_instruction(instruction_entry_t *instruction_lst) {
    int temp;
    temp = print_mark_instruction(instruction_lst);
    if (temp > 0) {
        return temp;
    }
    temp = print_label(instruction_lst);
    if (temp > 0) {
        return temp;
    }
    temp = print_general_instruction(instruction_lst);
    if (temp > 0) {
        return temp;
    }
    temp = print_mem_instruction(instruction_lst);
    if (temp > 0) {
        return temp;
    }
    temp = print_conver_fail(instruction_lst);
    return 1;
}

void print_fun_header(hashmap_value_t *fun_value, char *fun_name) {
    printf("\t.globl\t%s\n", fun_name);
    printf("\t.type\t%s, @function\n", fun_name);
    printf("%s:\n", fun_name);
    printf(".LFB0:\n");
    printf("\t.cfi_startproc\n");
    printf("\tendbr64\n");
    printf("\tpushq\t%%rbp\n");
    printf("\t.cfi_def_cfa_offset 16\n");
    printf("\t.cfi_offset 6, -16\n");
    printf("\tmovq\t%%rsp, %%rbp\n");
    printf("\t.cfi_def_cfa_register 6\n");
    // TODO: deslocar o rsp para a quantidade de valores da pilha: subq	$16, %rsp
}

void print_fun_footer(hashmap_value_t *fun_value, char *fun_name) {
    printf(".LFE0:\n");
    printf("\t.size\t%s, .-%s\n", fun_name, fun_name);
}

// Marcações são usadas no código iloc e são invisíveis,
// mas servem para transmitir um pouco mais de semantica e 
// contexto do que as instruções
int print_mark_instruction(instruction_entry_t *instruction_lst) {
    hashmap_t *global_scope = current_scope();
    instruction_t *instruction = instruction_lst->entry;

    if (instruction->op1_type != OT_MARK) {
        return 0;
    }

    int mark_type = instruction->op1;

    if (mark_type == CODE_MARK_FUN_START) {
        char *fun_name = instruction->mark_property;
        hashmap_value_t *fun_entry = hashmap_get(global_scope, fun_name);

        if (fun_entry != NULL) {
            print_fun_header(fun_entry, fun_name);
        }
        instruction_entry_t *current = instruction_lst;
        for (int i = 0; i < 3; i++) {
            current = current->next;
        }
        // estamos na instrução de deslocamento da pilha
        // precisa ser um múltiplo de 16 e um sub, exemplo: subq $32, %rsp
        int offset = current->entry->op2;
        offset += 16 - (offset % 16);
        current->entry->op2 = offset;
        strcpy(current->entry->code, "subI");
        return 3 + print_general_instruction(current);
    } else if (mark_type == CODE_MARK_FUN_END) {
        char *fun_name = instruction->mark_property;
        hashmap_value_t *fun_entry = hashmap_get(global_scope, fun_name);
        if (fun_entry != NULL) {
            print_fun_footer(fun_entry, fun_name);
        }
        return 1;
    } else if (mark_type == CODE_MARK_FUN_CALL_START) {
        return 1;
    } else if (mark_type == CODE_MARK_FUN_CALL_JUMP) {
        char *fun_name = instruction->mark_property;
        printf("\tcall\t%s\n", fun_name);
        return 4; // marcação + add rpc + store ret + jump
    } else if (mark_type == CODE_MARK_FUN_RETURN_VALUE) {
        // TODO: bug = retorno de funcao nao ta passando valor pro eax 
        // sempre é storeAI
        instruction_t* return_value_instruction = instruction_lst->next->entry;
        // storeAI r13 => rfp, 12        // Escreve o valor de retorno na pilha
        if (return_value_instruction->op1 != 0) { // se já não está no EAX
            char reg_name[10];
            print_instruction_parameter(return_value_instruction->op1, return_value_instruction->op1_type, reg_name);
            printf("\tmovl\t%s, %%eax\n", reg_name);
        }
        printf("\tleave\n\t.cfi_def_cfa 7, 8 \n\tret\n\t.cfi_endproc\n");
        return 4;
    } else if (mark_type == CODE_MARK_FUN_RET_END) {
        // Caso de encerramento de uma função geral, jump => r0 nao processado
        instruction_t* previous_instruction_jump = instruction_lst->previous->entry;
        char reg_name[10];
        print_instruction_parameter(previous_instruction_jump->op1, previous_instruction_jump->op1_type, reg_name);
        printf("\tpopq\t%%rbp\n");
        printf("\tleave\n\t.cfi_def_cfa 7, 8\n\tret\n\t.cfi_endproc\n");
        // Consome jump, três marks
        return 1;
    } else if (mark_type == CODE_MARK_SAVE_REGS_START || mark_type == CODE_MARK_SAVE_REGS_END) {
        // Só consome, achoo que não vamos precisar
        return 1;
    } 

    return 0;
}

// ultimo caso, quando não deu pra converter a instrução nos 
// mostramos isso, REMOVER ANTES DE ENTREGAR
int print_conver_fail(instruction_entry_t *instruction_lst) {
    printf("\t# Não rolou de imprimir: ");
    print_instruction(instruction_lst->entry);
    return 1;
}

int print_label(instruction_entry_t *instruction_lst) {
    if (instruction_lst->entry->op1_type == OT_LABEL) {
        printf("L%d:\n", instruction_lst->entry->op1);
        return 1;
    }
    return 0;
}

char get_correct_suffix(int op1, int op1_type, int op2, int op2_type) {
    if (op1 == RBSS || op2 == RBSS) {
        return 'q';
    }
    if (op1 == RSP || op2 == RSP) {
        return 'q';
    }
    if (op1 == RFP || op2 == RFP) {
        return 'q';
    }
    if (op1 == RPC || op2 == RPC) {
        return 'q';
    }
    if ((op1 >= 4 && op1 <= 11 && op1_type == OT_REG) || (op2 >= 4 && op2 <= 11 && op2_type == OT_REG)) {
        return 'q';
    }
    return 'l'; // só suportamos inteiro :)
}

int print_mem_instruction(instruction_entry_t *instruction_lst) {
    instruction_t *instruction = instruction_lst->entry;
    char asm_op1[10], asm_op2[10], asm_op3[10];
    char suffix;

    print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
    print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);
    print_instruction_parameter(instruction->op3, instruction->op3_type, asm_op3);
    
    if (strcmp(instruction->code, "load") == 0) {
        suffix = get_correct_suffix(-1, OT_REG, instruction->op3, instruction->op3_type);
        printf("\tmov%c\t(%s), %s\n", suffix, asm_op2, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "loadAI") == 0) {
        suffix = get_correct_suffix(-1, OT_REG, instruction->op3, instruction->op3_type);
        if (instruction->op2 != 0) {
            printf("\tmov%c\t-%d(%s), %s\n", suffix, instruction->op2, asm_op1, asm_op3);
        } else {
            printf("\tmov%c\t(%s), %s\n", suffix, asm_op1, asm_op3);
        }
        return 1;
    } else if (strcmp(instruction->code, "loadI") == 0) {
        int imediate_value = instruction->op2;
        instruction_t *next = instruction_lst->next->entry;
        if (next != NULL && ((next->op1 == instruction->reg_result && next->op1_type == OT_REG) || 
            (next->op2 == instruction->reg_result && next->op2_type == OT_REG))) 
        {
            // foi feito um loadI para usar o valor direto na 
            // próxima instrução, vamos tentar converter a próxima
            // usando esse valor imediato
            instruction_t *next_copy = (instruction_t*) malloc(sizeof(instruction_t));
            *next_copy = *next;
            if (next->op1 == instruction->reg_result) {
                next_copy->op1_type = OT_IMED;
                next_copy->op1 = imediate_value;
            } else {
                next_copy->op2_type = OT_IMED;
                next_copy->op2 = imediate_value;
            }
            instruction_entry_t *next_copy_lst = instr_lst_create_new(next_copy);

            int result = print_general_instruction(next_copy_lst);
            free(next_copy);
            free(next_copy_lst);

            if (result >= 1) {
                // conseguimos converter a próxima, não precisamos converter
                // esse loadI já que em asm isso é uma instrução apenas, então pulamos (+1)
                return result + 1;
            }
        }
        suffix = get_correct_suffix(instruction->op2, instruction->op2_type, instruction->op3, instruction->op3_type);
        printf("\tmov%c\t%s, %s\n", suffix, asm_op2, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "i2i") == 0) {
        suffix = get_correct_suffix(instruction->op1, instruction->op1_type, instruction->op3, instruction->op3_type);
        printf("\tmov%c\t%s, %s\n", suffix, asm_op1, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "store") == 0) {
        suffix = get_correct_suffix(instruction->op2, instruction->op2_type, -1, OT_REG);
        printf("\tmov%c\t%s, (%s)\n", suffix, asm_op2, asm_op3);
        return 1;
    } else if (strcmp(instruction->code, "storeAI") == 0) {
        suffix = get_correct_suffix(instruction->op1, instruction->op1_type, -1, OT_REG);
        if (instruction->op3 != 0) {
            printf("\tmov%c\t%s, -%d(%s)\n", suffix, asm_op1, instruction->op3, asm_op2);
        } else {
            printf("\tmov%c\t%s, (%s)\n", suffix, asm_op1, asm_op2);
        }
        return 1;
    }

    return 0;
}

int print_general_instruction(instruction_entry_t *instruction_lst) {
    instruction_t *instruction = instruction_lst->entry;

    char asm_code[10], asm_op1[10], asm_op2[10], asm_op3[10];
    int is_comutative = 0;
    int is_three_op = 0;

    if (strncmp(instruction->code, "add", 3) == 0) {
        strcpy(asm_code, "add");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "sub", 3) == 0) {
        strcpy(asm_code, "sub");
    } else if (strncmp(instruction->code, "mult", 4) == 0) {
        strcpy(asm_code, "imul");
        is_comutative = 1;
        is_three_op = 1;
    } else if (strncmp(instruction->code, "div", 3) == 0) {
        strcpy(asm_code, "idiv");
    } else if (strncmp(instruction->code, "and", 3) == 0) {
        strcpy(asm_code, "and");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "or", 2) == 0) {
        strcpy(asm_code, "or");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "xor", 3) == 0) {
        strcpy(asm_code, "xor");
        is_comutative = 1;
    } else if (strncmp(instruction->code, "lshift", 6) == 0) {
        strcpy(asm_code, "sal");
    } else if (strncmp(instruction->code, "rshift", 6) == 0) {
        strcpy(asm_code, "sar");
    } else {
        // não conhecemos essa instrução como sendo um instrução
        // geral, deve ser outra coisa, então vamos sair...
        return 0;
    }

    if (is_three_op == 1) {
        // o x86 suporta essa instrução como uma instrução de 3 operandos, é tivial
        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);
        print_instruction_parameter(instruction->op3, instruction->op3_type, asm_op3);

        char suffix = get_correct_suffix(instruction->op1, instruction->op1_type, instruction->op2, instruction->op2_type);
        
        if (instruction->op2_type == OT_IMED) {
            printf("\t%s%c\t%s, %s, %s\n", asm_code, suffix, asm_op2, asm_op1, asm_op3);
        } else {
            printf("\t%s%c\t%s, %s, %s\n", asm_code, suffix, asm_op1, asm_op2, asm_op3);
        }
    
        return 1;
    } else if (instruction->op1 == instruction->op3) {
        // essas operações não importa a ordem, então da pra executar
        // em uma instrução apenas
        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);
        char suffix = get_correct_suffix(instruction->op1, instruction->op1_type, instruction->op2, instruction->op2_type);

        printf("\t%s%c\t%s, %s\n", asm_code, suffix, asm_op2, asm_op1);
    
        return 1;
    } else if (instruction->op2 == instruction->op3 && is_comutative == 1) {
        // Nesse caso a instrução não tá colocando no segundo operando
        // a conversão se torna bem mais fácil porque é 1:1
        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op2);
        char suffix = get_correct_suffix(instruction->op1, instruction->op1_type, instruction->op2, instruction->op2_type);

        printf("\t%s%c\t%s, %s\n", asm_code, suffix, asm_op1, asm_op2);
        
        return 1;
    } else {
        // Esse é um caso mais chato, precisamos gravar o resultado o operando 1 em um
        // registrador intermediário, usar ele para o cálculo com o operando 2 
        // e depois mover para o operando 3 (destino correto)
        char suffix;
        print_instruction_parameter(REG_EFE, OT_REG, asm_op2);
        
        print_instruction_parameter(instruction->op2, instruction->op2_type, asm_op1);
        suffix = get_correct_suffix(REG_EFE, OT_REG, instruction->op2, instruction->op2_type);
        printf("\tmov%c\t%s, %s\n", suffix, asm_op1, asm_op2);

        print_instruction_parameter(instruction->op1, instruction->op1_type, asm_op1);
        suffix = get_correct_suffix(REG_EFE, OT_REG, instruction->op1, instruction->op1_type);
        printf("\t%s%c\t%s, %s\n", asm_code, suffix, asm_op1, asm_op2);

        print_instruction_parameter(instruction->op3, instruction->op3_type, asm_op1);
        suffix = get_correct_suffix(REG_EFE, OT_REG, instruction->op3, instruction->op3_type);
        printf("\tmov%c\t%s, %s\n", suffix, asm_op2, asm_op1);

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
            strcpy(dest, "%eax");
            break;
        case 1:
            strcpy(dest, "%ebx");
            break;
        case 2:
            strcpy(dest, "%ecx");
            break;
        case 3:
            strcpy(dest, "%edx");
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

// regs especiais = num negativo referencia: code_gen.c (valores)
// ver regs especiais no x86 e se tem correspondente, quais são

// TODO: Mudar o nome da função
// TODO: Agora temos o ILOC com regs otimizados
// TODO: Mapear regs até os regs que temos no x86_64 assembly, pros regs do ILOC
// TODO: Devolver algum código inteiro quando não for possível mapear o registrador (derramamento)
// TODO: Colocar o "movl $0, %eax" antes de um call (pra não deixar lixo no eax)