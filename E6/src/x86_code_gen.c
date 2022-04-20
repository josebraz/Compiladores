
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

instruction_entry_t *arch_convert_code(instruction_entry_t *input) {
    // 1 - Simplificar os regs do ILOC (coloração de grafos) e derramamento
    // 2 - Verificar salvamento de registradores no ILOC
    // 3 - Mapeamento da tabela de simbolos global para o seguimento de dados do assembly
    // 4 - Mapeamento do ILOC simplificado para x86

    // TODO: Aqui vai ter a lógica de conversão das intruções de ILOC para o x86
}