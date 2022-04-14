/* autores: José Henrique da Silva Braz */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#include "code_gen.h"
#include "bool_lst.h"
#include "instr_lst.h"
#include "semantic.h"
#include "asp.h"
#include "types.h"

#define RET    1 // registrador para os end de retorno
#define EFEM   0 // registrador efemero que pode mudar a qualquer momento
#define EMPTY -1
#define RBSS  -3
#define RFP   -4
#define RSP   -5
#define RPC   -6

int instr_counter = 0;

int next_reg() {
    static int last_reg = 2;
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
    instruction_entry_t *rbss_load = generate_instructionI("loadI", EMPTY, counter + 6, RBSS);
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

    instruction_entry_t *store_instr = generate_instructionI("loadAI", reg, offset, n->reg_result);
    comment_instruction(store_instr, "Carrega variável %s", ident);

    n->code = store_instr;
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
    comment_instruction(store_instr, "Grava variável %s", ident);

    b->code = instr_lst_join(2, init->code, store_instr);
}

void generate_fun_return(node *s, node *e) {
    hashmap_t *global_scope;
    hashmap_t *function_scope = current_scope();
    char *fun_name = function_scope->label;
    hashmap_value_t *fun_decl = find_declaration(fun_name, &global_scope);

    // Escreve o retorno
    instruction_entry_t *store_result = generate_instructionS("storeAI", e->reg_result, RFP, 12);
    instruction_entry_t *load_last_rsp = generate_instructionI("loadAI", RFP, 4, EFEM);
    instruction_entry_t *copy_rsp = generate_instructionI("i2i", EFEM, EMPTY, RSP);
    instruction_entry_t *load_last_rfp = generate_instructionI("loadAI", RFP, 8, EFEM);
    instruction_entry_t *copy_rfp = generate_instructionI("i2i", EFEM, EMPTY, RFP);
    instruction_entry_t *load_ret_end = generate_instructionI("loadAI", RFP, 0, RET);
    instruction_entry_t *jump_ret = generate_jump(RET);

    comment_instruction(load_ret_end, "Carrega end de retorno");
    comment_instruction(load_last_rsp, "Carrega ultimo RSP");
    comment_instruction(load_last_rfp, "Carrega ultimo RFP");
    comment_instruction(e->code, "Início do retorno de %s", fun_name);
    comment_instruction(store_result, "Escreve o valor de retorno na pilha");

    s->code = instr_lst_join(8, e->code, store_result,
                                load_ret_end, load_last_rsp, copy_rsp, 
                                load_last_rfp, copy_rfp, jump_ret);
}

void insert_restore_reg_code(node *n, instruction_entry_t *restore_code) {
    if (strcmp(n->label, "return") == 0) {
        instruction_entry_t *copy = instr_lst_copy(restore_code);
        printf("insert_restore_reg_code\n");
        print_instr_lst(n->code);

        instruction_entry_t *current = n->code;
        while (current != NULL && (strcmp(current->entry->code, "loadAI") != 0 || current->entry->op3 != RET)) {
            current = current->next;
        }
        if (current != NULL) {
            instruction_entry_t *previous = current->previous;
            if (previous != NULL) {
                previous->next = copy;
                copy->previous = previous;
            }
            instr_lst_join(2, copy, current);
        }
    } else {
        for (int i = 0; i < n->size; i++) {
            insert_restore_reg_code(n->nodes[i], restore_code);
        }
        if (n->next != NULL) {
            insert_restore_reg_code(n->next, restore_code);
        }
    }
}

int is_destrutive_op(instruction_t *inst) {
    if (inst->op3_type == OT_REG && inst->op3 >= 2 && 
        (inst->op1 != EMPTY || inst->op2 != EMPTY)) {
        return 1;
    } else {
        return 0;
    }
}

void generate_fun_decl(node *fun) {
    char *fun_name = (char*) fun->label;

    hashmap_t *global_scope;
    hashmap_t *function_scope = current_scope();
    hashmap_value_t *fun_decl = find_declaration(fun_name, &global_scope);

    instruction_entry_t *instr_fun_label = generate_label_instruction(fun_decl->fun_label);
    instruction_entry_t *update_rfp = generate_instructionI("i2i", RSP, EMPTY, RFP);
    int rsp_gap = function_scope->offset + 4 * 4; // offset de variáveis + end retorno, rsp salvo, rfp salvo, valor de retorno

    comment_instruction(instr_fun_label, "Declaração da função %s", fun_name);

    instruction_entry_t *store_used_reg = NULL;
    instruction_entry_t *load_used_reg = NULL;
    instruction_entry_t *fun_body_code = fun->nodes[0]->code;
    while (fun_body_code != NULL) {
        if (is_destrutive_op(fun_body_code->entry) == 1) {
            store_used_reg = instr_lst_join(2, store_used_reg, 
                            generate_instructionS("storeAI", fun_body_code->entry->op3, RFP, rsp_gap));
            load_used_reg = instr_lst_join(2, load_used_reg, 
                            generate_instructionI("loadAI", RFP, rsp_gap, fun_body_code->entry->op3));
            rsp_gap += 4;
        }
        fun_body_code = fun_body_code->next;
    }
    comment_instruction(store_used_reg, "Salva o estado dos registradores usados na função");
    comment_instruction(load_used_reg, "Restaura o estado dos registradores usados");

    instruction_entry_t *update_rsp = generate_instructionI("addI", RSP, rsp_gap, RSP);

    fun->code = instr_lst_join(5, instr_fun_label, update_rfp, 
                                  update_rsp, store_used_reg, 
                                  fun->nodes[0]->code);

    insert_restore_reg_code(fun->nodes[0], load_used_reg);

    if (strcmp(fun_name, "main") == 0) {
        // quando acabar a main a gente acaba a máquina com um halt
        instruction_entry_t *instr_halt = generate_instruction("halt", EMPTY, EMPTY, EMPTY);
        fun->code = instr_lst_join(2, fun->code, instr_halt);
    }
}

void generate_fun_call(node *s, node *params) {
    char *fun_name = (char *) s->value;
    hashmap_t *global_scope;
    hashmap_value_t *fun_decl = find_declaration(fun_name, &global_scope);

    instruction_entry_t *store_rsp = generate_instructionS("storeAI", RSP, RSP, 4);
    instruction_entry_t *store_rfp = generate_instructionS("storeAI", RFP, RSP, 8);

    // para cada parametro da função cria um store
    int param_offset = 16;
    instruction_entry_t *param_lst = params->code;
    node *p = params;
    while (p != NULL) {
        instruction_entry_t *p_store = generate_instructionS("storeAI", p->reg_result, RSP, param_offset);
        comment_instruction(p_store, "grava o parametro %d da função", (param_offset - 16) / 4 + 1);
        param_lst = instr_lst_join(2, param_lst, p_store);
        param_offset += 4;
        p = p->next;
    }

    // prepara o endereço de retorno que é após essas 2 instr e do jump
    instruction_entry_t *cal_ret_end = generate_instructionI("addI", RPC, 3, EFEM);
    instruction_entry_t *store_ret_end = generate_instructionS("storeAI", EFEM, RSP, 0);
    instruction_entry_t *jump_fun = generate_jumpI(fun_decl->fun_label);

    int ret_value_reg = next_reg();
    instruction_entry_t *load_return_value = generate_instructionI("loadAI", RSP, 12, ret_value_reg);

    comment_instruction(store_rsp, "Inicio da chamada de %s()", fun_name);
    comment_instruction(load_return_value, "Carrega o valor de retorno de %s()", fun_name);
    comment_instruction(jump_fun, "Salta para a função %s()", fun_name);

    s->reg_result = ret_value_reg;
    s->code = instr_lst_join(7, store_rsp, store_rfp, 
                                param_lst, cal_ret_end,
                                store_ret_end, jump_fun, load_return_value);
}

void generate_for(node *s, node *s1, node *b, node *s2, node *s3) {
    int label_start = next_label();
    int label_true = next_label();
    int label_end = next_label();

    instruction_entry_t *instr_start_label = generate_label_instruction(label_start);
    instruction_entry_t *instr_true_label = generate_label_instruction(label_true);
    instruction_entry_t *instr_end_label = generate_label_instruction(label_end);
    instruction_entry_t *jump_start = generate_jumpI(label_start);

    comment_instruction(instr_start_label, "Label do teste do for");
    comment_instruction(instr_true_label, "Label de dentro do for");
    comment_instruction(instr_end_label, "Label do final do for");

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

    comment_instruction(instr_true_label, "Label de dentro do while");
    comment_instruction(instr_start_label, "Label do teste do while");
    comment_instruction(instr_end_label, "Label do final do while");

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

    comment_instruction(instr_true_label, "Label true do if");
    comment_instruction(instr_end_label, "Label de final do if");

    if (b_false != NULL) {
        int label_false = next_label();
        instruction_entry_t *instr_false_label = generate_label_instruction(label_false);

        comment_instruction(instr_false_label, "Label false do if");

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

int print_instr_param(int op, int op_type) {
    if (op_type == OT_IMED) {
        return printf("%d", op);
    } else if (op_type == OT_LABEL) {
        return printf("L%d", op);
    } else {
        if (op == RBSS) {
            return printf("rbss");
        } else if (op == RFP) {
            return printf("rfp");
        } else if (op == RSP) {
            return printf("rsp");
        } else if (op == RPC) {
            return printf("rpc");
        } else {
            return printf("r%d", op);
        }
    }
}

void print_instruction(instruction_t *inst) {
    int char_counter = 0;
    if (inst->op1_type == OT_LABEL) {
        char_counter += printf("L%d:", inst->op1);
    } else if (strncmp(inst->code, "store", 5) == 0 || strcmp(inst->code, "cbr") == 0) {
        char_counter += printf("%s ", inst->code);
        char_counter += print_instr_param(inst->op1, inst->op1_type);
        char_counter += printf(" => ");
        char_counter += print_instr_param(inst->op2, inst->op2_type);
        char_counter += printf(", ");
        char_counter += print_instr_param(inst->op3, inst->op3_type);
    } else if (strcmp(inst->code, "halt") == 0 || strcmp(inst->code, "nop") == 0) { 
        char_counter += printf("%s", inst->code);
    } else {
        char_counter += printf("%s ", inst->code);
        if (inst->op1_type != OT_DISABLED && inst->op1 != EMPTY) {
            char_counter += print_instr_param(inst->op1, inst->op1_type);
        }
        if (inst->op2_type != OT_DISABLED && inst->op2 != EMPTY) {
            if (inst->op1_type != OT_DISABLED && inst->op1 != EMPTY) {
                char_counter += printf(", ");
            }
            char_counter += print_instr_param(inst->op2, inst->op2_type);
        }
        char_counter += printf(" => ");
        if (inst->op3_type != OT_DISABLED && inst->op3 != EMPTY) {
            char_counter += print_instr_param(inst->op3, inst->op3_type);
        }
    }
    if (strlen(inst->comment) > 0) {
        for (int i = 0; i < 30 - char_counter; i++) {
            printf(" ");
        }
        printf("// %s", inst->comment);
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
    *offset = decl->men_offset + 16;
}

void comment_instruction(instruction_entry_t *entry, char *message, ...) {
    va_list argptr;
    va_start(argptr, message);
    vsprintf(entry->entry->comment, message, argptr);
    va_end(argptr);
}

instruction_entry_t *generate_label_instruction(int label) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    instr->op1_type = OT_LABEL;
    instr->op1 = label;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_DISABLED;
    instr->op3 = EMPTY;
    strcpy(instr->comment, "\0");
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
    strcpy(instr->comment, "\0");
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
    strcpy(instr->comment, "\0");
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
    strcpy(instr->comment, "\0");
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
    strcpy(instr->comment, "\0");
    instr_counter++;
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_jump(int reg) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "jump");
    instr->op1_type = OT_DISABLED;
    instr->op1 = EMPTY;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_REG;
    instr->op3 = reg;
    strcpy(instr->comment, "\0");
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
    strcpy(instr->comment, "\0");
    instr_counter++;
    return instr_lst_create_new(instr);
}

