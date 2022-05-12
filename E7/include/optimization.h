/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include "types.h"

void optimization_setup(int argc, char **argv);

instruction_entry_t *optimize_function_code(instruction_entry_t *code);

instruction_entry_t *optimize_iloc_register_usage(instruction_entry_t *code);

#endif
