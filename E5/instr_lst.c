/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "instr_lst.h"
#include "semantic.h"
#include "types.h"

#define EMPTY -1
#define RBSS  -3
#define RFP   -4
#define RSP   -5

int instr_counter = 0;

int next_reg() {
    static int last_reg = 0;
    return last_reg++;
}

int next_label() {
    static int last_label = 0;
    return last_label++;
}

instruction_entry_t *generate_init_code() {
    int counter = instr_counter;

    hashmap_value_t *main_decl = find_declaration("main", NULL);
    if (main_decl == NULL) exit(1);

    instruction_t *rfp_load = generate_instructionI("loadI", EMPTY, 1024, RFP);
    instruction_t *rsp_load = generate_instructionI("loadI", EMPTY, 1024, RSP);
    instruction_t *rbss_load = generate_instructionI("loadI", EMPTY, counter + 5, RBSS);
    instruction_t *jump_main = generate_jumpI(main_decl->fun_label);
    return instr_lst_create(4, rfp_load, rsp_load, rbss_load, jump_main);
}

instruction_entry_t *generate_code(
    char *code, 
    instruction_entry_t *instr1, 
    instruction_entry_t *instr2
) {
    instruction_t *instr = generate_instruction(code, instr1->entry->op3, instr2->entry->op3, next_reg());
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_codeI(
    char *code, 
    instruction_entry_t *instr1, 
    instruction_entry_t *instr2
) {
    instruction_t *instr = generate_instructionI(code, instr1->entry->op3, instr2->entry->op3, next_reg());
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_var_load(char *ident) {
    int reg, offset;
    get_var_mem_loc(ident, &reg, &offset);
    instruction_t *code = generate_instructionI("loadAI", reg, offset, next_reg());
    return instr_lst_create_new(code);
}

instruction_entry_t *generate_literal_load(int value) {
    instruction_t *code = generate_instructionI("loadI", EMPTY, value, next_reg());
    return instr_lst_create_new(code);
}

instruction_t *generate_jumpI(int label) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "jumpI");
    instr->op1_type = OT_DISABLED;
    instr->op1 = EMPTY;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_LABEL;
    instr->op3 = label;
    return instr;
}

instruction_entry_t *process_arith_expression(node *head) {
    printf("Label %s\n", head->label);
    instruction_entry_t *instr_current;
    if (head->mark == LITERAL_T && head->type == DT_INTEGER) {
        head->code = generate_instructionI("loadI", EMPTY, *((int *) head->value), next_reg());
        instr_current = instr_lst_create_new(head->code);
    } else if (head->mark == VAR_T) {
        generate_var_load((char *) head->value);
    } else if (head->mark == ARRAY_T) {
        // TODO
    } else if (head->mark == FUN_CALL_T) {
        // TODO
    } else {
        // chamamos a recursão para ir até o mais a esquerda e abaixo
        instruction_entry_t *instr1 = NULL;
        instruction_entry_t *instr2 = NULL;
        instruction_entry_t *instr3 = NULL;

        if (head->size >= 1) instr1 = process_arith_expression(head->nodes[0]);
        if (head->size >= 2) instr2 = process_arith_expression(head->nodes[1]);
        if (head->size >= 3) instr3 = process_arith_expression(head->nodes[2]);

        if (strcmp(head->label, "*") == 0) {
            return generate_code("mult", instr1, instr2);
        } else if (strcmp(head->label, "/") == 0) {
            return generate_code("div", instr1, instr2);
        } else if (strcmp(head->label, "+") == 0) {
            return generate_code("add", instr1, instr2);
        } else if (strcmp(head->label, "-") == 0) {
            return generate_code("sub", instr1, instr2);
        }
    }
    return instr_current;
}

void print_instr_lst(instruction_entry_t *entry) {
    instruction_entry_t *current = entry;
    while (current != NULL && current->entry != NULL) {
        print_instruction(current->entry);
        current = current->next;
    }
}

void print_instr_param(int op, int op_type) {
    if (op_type == OT_IMED) {
        printf("%d", op);
    } else if (op_type == OT_LABEL) {
        printf("L%d", op);
    } else {
        if (op == RBSS) {
            printf("rbss");
        } else if (op == RFP) {
            printf("rfp");
        } else if (op == RSP) {
            printf("rsp");
        } else {
            printf("r%d", op);
        }
    }
}

void print_instruction(instruction_t *inst) {
    printf("%s ", inst->code);
    if (inst->op1_type != OT_DISABLED && inst->op1 != EMPTY) {
        print_instr_param(inst->op1, inst->op1_type);
        printf(", ");
    }
    if (inst->op2_type != OT_DISABLED && inst->op2 != EMPTY) {
        print_instr_param(inst->op2, inst->op2_type);
    }
    printf(" => ");
    if (inst->op3_type != OT_DISABLED && inst->op3 != EMPTY) {
        print_instr_param(inst->op3, inst->op3_type);
    }
    printf("\n");
}

void get_var_mem_loc(char *ident, int *reg, int *offset) {
    hashmap_t *scope;
    hashmap_value_t *decl = find_declaration(ident, &scope);
    if (strcmp(scope->label, "global") == 0) {
        *reg = RBSS;
    } else {
        *reg = RFP;
    }
    *offset = decl->men_offset;
}

instruction_t *generate_instruction(char *code, int reg1, int reg2, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_REG;
    instr->op2 = reg2;
    instr->op3_type = OT_REG;
    instr->op3 = reg3;

    instr_counter++;
    return instr;
}

instruction_t *generate_instructionI(char *code, int reg1, int value, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_IMED;
    instr->op2 = value;
    instr->op3_type = OT_REG;
    instr->op3 = reg3;

    instr_counter++;
    return instr;
}

void output_code_from_node_rec(node* n) {
    for (int i = 0; i < n->size; i++) {
        output_code_from_node_rec(n->nodes[i]);
    }
    print_instr_lst(n->code);
}

void output_code_from_node(node* n) {
    printf("output_code_from_node\n");
    instruction_entry_t *init_code = generate_init_code();
    print_instr_lst(init_code);
    output_code_from_node_rec(n);
}

instruction_entry_t *instr_lst_create_new(instruction_t *new_inst) {
    instruction_entry_t *new_entry = (instruction_entry_t*) malloc(sizeof(instruction_entry_t));
    new_entry->next = NULL;
    new_entry->previous = NULL;
    new_entry->entry = new_inst;
    return new_entry;
}

instruction_entry_t *instr_lst_join(instruction_entry_t *entry1, instruction_entry_t *entry2) {
    instruction_entry_t *last = entry1;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = entry2;
    entry2->previous = last;
    return entry1;
}

instruction_entry_t *instr_lst_create(int size, ...) {
    int i;
    instruction_t *instr;
    instruction_entry_t *entry, *last_entry = NULL, *first_entry = NULL;
    va_list arguments;
    
    va_start(arguments, size);
    for (i = 0; i < size; i++) {
        instr = (instruction_t*) va_arg(arguments, instruction_t*);
        entry = instr_lst_create_new(instr);
        if (i == 0) first_entry = entry;

        if (last_entry != NULL) {
            last_entry->next = entry;
            entry->previous = last_entry;
        }
        last_entry = entry;
    }
    va_end(arguments);

    return first_entry;
}

//   A <-> B <-> C 
//                  entra o D no meio do A e B
//   A <-> D <-> B <-> C
instruction_entry_t *instr_lst_add_next(instruction_entry_t *a, instruction_t *new_inst) {
    instruction_entry_t *d = instr_lst_create_new(new_inst);
    if (a == NULL) {
        return d;
    }
    instruction_entry_t *b = a->next;
    d->next = b;
    d->previous = a;
    if (b != NULL) {
        b->previous = d;
    }
    a->next = d;
    return a;
}



//   A <-> B <-> C 
//                  entra o D no meio do A e B
//   A <-> D <-> B <-> C
instruction_entry_t *instr_lst_add_previous(instruction_entry_t *b, instruction_t *new_inst) {
    instruction_entry_t *d = instr_lst_create_new(new_inst);
    if (b == NULL) {
        return d;
    }
    instruction_entry_t *a = b->previous;
    return instr_lst_add_next(a, new_inst);
}


