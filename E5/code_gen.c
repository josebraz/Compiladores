/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "code_gen.h"
#include "bool_lst.h"
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

    instruction_entry_t *rfp_load = generate_instructionI("loadI", EMPTY, 1024, RFP);
    instruction_entry_t *rsp_load = generate_instructionI("loadI", EMPTY, 1024, RSP);
    instruction_entry_t *rbss_load = generate_instructionI("loadI", EMPTY, counter + 5, RBSS);
    instruction_entry_t *jump_main = generate_jumpI(main_decl->fun_label);
    return instr_lst_join(4, rfp_load, rsp_load, rbss_load, jump_main);
}

void generate_general_code(char *code, node *b, node *n1, node *n2) {
    b->reg_result = next_reg();
    instruction_entry_t *instr = generate_instruction(code, n1->reg_result, n2->reg_result, b->reg_result);
    b->code = instr_lst_join(3, n1->code, n2->code, instr);
}

void generate_var_load(node *n) {
    int reg, offset;
    char *ident = (char *) n->value;
    get_var_mem_loc(ident, &reg, &offset);
    n->reg_result = next_reg();
    n->code = generate_instructionI("loadAI", reg, offset, n->reg_result);
}

void generate_literal_load(node *n) {
    n->reg_result = next_reg();
    int value = *((int *) n->value);
    n->code = generate_instructionI("loadI", EMPTY, value, n->reg_result);
}

void generate_var_assignment(char *ident, node *b, node *init) {
    if (init->mark == VAR_T) {
        generate_var_load(init);
    }
    int reg, offset;
    get_var_mem_loc(ident, &reg, &offset);
    instruction_entry_t *store_instr = generate_instructionS("storeAI", init->reg_result, reg, offset);
    b->code = instr_lst_join(2, init->code, store_instr);
}

void generate_for(node *s, node *s1, node *b, node *s2, node *s3) {
    int label_start = next_label();
    int label_true = next_label();
    int label_end = next_label();

    instruction_entry_t *instr_start_label = generate_label_instruction(label_start);
    instruction_entry_t *instr_true_label = generate_label_instruction(label_true);
    instruction_entry_t *instr_end_label = generate_label_instruction(label_end);
    instruction_entry_t *jump_start = generate_jumpI(label_start);

    bool_lst_remenda(b->true_list, label_true);
    bool_lst_remenda(b->false_list, label_end);

    s->code = instr_lst_join(8, s1->code, instr_start_label, 
                                b->code, instr_true_label, 
                                s3->code, s2->code, 
                                jump_start, instr_end_label);
}

void generate_while(node *s, node *b, node *s1) {
    int label_start = next_label();
    int label_true = next_label();
    int label_end = next_label();

    instruction_entry_t *instr_start_label = generate_label_instruction(label_start);
    instruction_entry_t *instr_true_label = generate_label_instruction(label_true);
    instruction_entry_t *instr_end_label = generate_label_instruction(label_end);
    instruction_entry_t *jump_start = generate_jumpI(label_start);

    bool_lst_remenda(b->true_list, label_true);
    bool_lst_remenda(b->false_list, label_end);

    s->code = instr_lst_join(6, instr_start_label, b->code, 
                                instr_true_label, s1->code, 
                                jump_start, instr_end_label);
}

void generate_if(node *b, node *e, node *b_true, node *b_false) {
    int label_true = next_label();
    int label_end = next_label();
    
    instruction_entry_t *instr_true_label = generate_label_instruction(label_true);
    instruction_entry_t *instr_end_label = generate_label_instruction(label_end);
    instruction_entry_t *jump_end = generate_jumpI(label_end);

    if (b_false != NULL) {
        int label_false = next_label();
        instruction_entry_t *instr_false_label = generate_label_instruction(label_false);

        bool_lst_remenda(e->true_list, label_true);
        bool_lst_remenda(e->false_list, label_false);

        b->code = instr_lst_join(7, e->code, instr_true_label, 
                                    b_true->code, jump_end, instr_false_label, 
                                    b_false->code, instr_end_label);
    } else {
        bool_lst_remenda(e->true_list, label_true);
        bool_lst_remenda(e->false_list, label_end);

        b->code = instr_lst_join(4, e->code, instr_true_label, b_true->code, instr_end_label);
    }
}

void generate_and(node *b, node *b1, node *b2) {
    int label = next_label();
    instruction_entry_t *label_inst = generate_label_instruction(label);
    bool_lst_remenda(b1->true_list, label);
    b->true_list = b2->true_list;
    b->false_list = bool_lst_concat(b1->false_list, b2->false_list);
    b->code = instr_lst_join(3, b1->code, label_inst, b2->code);
}

void generate_or(node *b, node *b1, node *b2) {
    int label = next_label();
    instruction_entry_t *label_inst = generate_label_instruction(label);
    bool_lst_remenda(b1->false_list, label);
    b->false_list = b2->false_list;
    b->true_list = bool_lst_concat(b1->true_list, b2->true_list);
    b->code = instr_lst_join(3, b1->code, label_inst, b2->code);
}

void generate_not(node *b, node *b1) {
    b->false_list = b1->true_list;
    b->true_list = b1->false_list;
}

void generate_true(node *b) {
    int x = bool_lst_next_remendo();
    b->code = generate_jumpI(x);
    b->true_list = bool_lst_create(1, &(b->code->entry->op3));
    b->false_list = NULL;
}

void generate_false(node *b) {
    int x = bool_lst_next_remendo();
    b->code = generate_jumpI(x);
    b->false_list = bool_lst_create(1, &(b->code->entry->op3));
    b->true_list = NULL;
}

void generate_relop(char *code, node *parent, node *b1, node *b2) {
    int x = bool_lst_next_remendo();
    int y = bool_lst_next_remendo();

    if (strcmp(code, "EQ") == 0) {
        generate_general_code("cmp_EQ", parent, b1, b2);
    } else if (strcmp(code, "NE") == 0) {
        generate_general_code("cmp_NE", parent, b1, b2);
    } else if (strcmp(code, "LT") == 0) {
        generate_general_code("cmp_LT", parent, b1, b2);
    } else if (strcmp(code, "LE") == 0) {
        generate_general_code("cmp_LE", parent, b1, b2);
    } else if (strcmp(code, "GT") == 0) {
        generate_general_code("cmp_GT", parent, b1, b2);
    } else if (strcmp(code, "GE") == 0) {
        generate_general_code("cmp_GE", parent, b1, b2);
    } else {
        perror("Code não reconhecido");
        exit(1);
    }

    instruction_entry_t *cbr_code = generate_instructionB(parent->reg_result, x, y);

    parent->code       = instr_lst_join(2, parent->code, cbr_code);
    parent->true_list  = bool_lst_create(1, &(cbr_code->entry->op2));
    parent->false_list = bool_lst_create(1, &(cbr_code->entry->op3));
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
    if (inst->op1_type == OT_LABEL) {
        printf("L%d:", inst->op1);
    } else if (strncmp(inst->code, "store", 5) == 0 || strcmp(inst->code, "cbr") == 0) {
        printf("%s ", inst->code);
        print_instr_param(inst->op1, inst->op1_type);
        printf(" => ");
        print_instr_param(inst->op2, inst->op2_type);
        printf(", ");
        print_instr_param(inst->op3, inst->op3_type);
    } else {
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
    }
    printf("\n");
}

void get_var_mem_loc(char *ident, int *reg, int *offset) {
    hashmap_t *scope;
    hashmap_value_t *decl = find_declaration(ident, &scope);
    if (decl == NULL || scope == NULL) {
        exit(1);
    }
    if (strcmp(scope->label, "global") == 0) {
        *reg = RBSS;
    } else {
        *reg = RFP;
    }
    *offset = decl->men_offset;
}

instruction_entry_t *generate_label_instruction(int label) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    instr->op1_type = OT_LABEL;
    instr->op1 = label;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_DISABLED;
    instr->op3 = EMPTY;

    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instructionB(int reg, int label1, int label2) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "cbr");
    instr->op1_type = OT_REG;
    instr->op1 = reg;
    instr->op2_type = OT_LABEL;
    instr->op2 = label1;
    instr->op3_type = OT_LABEL;
    instr->op3 = label2;

    instr_counter++;
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instruction(char *code, int reg1, int reg2, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_REG;
    instr->op2 = reg2;
    instr->op3_type = OT_REG;
    instr->op3 = reg3;

    instr_counter++;
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instructionI(char *code, int reg1, int value, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_IMED;
    instr->op2 = value;
    instr->op3_type = OT_REG;
    instr->op3 = reg3;

    instr_counter++;
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instructionS(char *code, int reg1, int value, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_REG;
    instr->op2 = value;
    instr->op3_type = OT_IMED;
    instr->op3 = reg3;
    instr_counter++;
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_jumpI(int label) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "jumpI");
    instr->op1_type = OT_DISABLED;
    instr->op1 = EMPTY;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_LABEL;
    instr->op3 = label;
    return instr_lst_create_new(instr);
}

void output_code_from_node_rec(node* n) {
    int max;
    if (n == NULL) return;
    if (n->size > 0 && n->nodes[n->size-1]->mark == STMT_T) {
        max = n->size-1;
    } else {
        max = n->size;
    }
    for (int i = 0; i < max; i++) {
        output_code_from_node_rec(n->nodes[i]);
    }
    print_instr_lst(n->code);
    if (max != n->size) {
        output_code_from_node_rec(n->nodes[n->size-1]);
    }
}

void output_code_from_node(node* n) {
    printf("output_code_from_node\n");
    // instruction_entry_t *init_code = generate_init_code();
    // print_instr_lst(init_code);
    // output_code_from_node_rec(n);
}
