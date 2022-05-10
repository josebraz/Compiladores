/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#include "code_gen.h"
#include "bool_lst.h"
#include "instr_lst.h"
#include "semantic.h"
#include "depend_graph.h"
#include "asp.h"
#include "types.h"

int last_reg = 0;

int next_reg() { 
    return last_reg++;
}

int next_label() {
    static int last_label = 0;
    return last_label++;
}

instruction_entry_t *generate_init_code(int counter) {
    hashmap_value_t *main_decl = find_declaration("main", NULL);
    if (main_decl == NULL) exit(1);

    instruction_entry_t *start_init_code = generate_mark(CODE_MARK_INIT_CODE_START, 0, 0, "");
    instruction_entry_t *rfp_load = generate_instructionI("loadI", EMPTY, 1024, RFP);
    instruction_entry_t *rsp_load = generate_instructionI("loadI", EMPTY, 1024, RSP);
    instruction_entry_t *rbss_load = generate_instructionI("loadI", EMPTY, counter + 6, RBSS);
    instruction_entry_t *jump_main = generate_jumpI(main_decl->fun_label);
    instruction_entry_t *end_init_code = generate_mark(CODE_MARK_INIT_CODE_END, 0, 0, "");

    return instr_lst_join(6, start_init_code, rfp_load, rsp_load, rbss_load, jump_main, end_init_code);
}

instruction_entry_t *remove_lazy_of_result(instruction_entry_t *instr, int reg, instruction_entry_t **fold) {
    instruction_entry_t *start = instr;
    instruction_entry_t *current = instr;
    while (current != NULL) {
        if (current->entry->lazy == 1 && current->entry->reg_result == reg) {
            instruction_entry_t *next = current->next;
            if (current->previous != NULL) {
                current->previous->next = next;
            }
            if (next != NULL) {
                next->previous = current->previous;
            }
            *fold = current;
            if (start == current) {
                start = current->previous;
            }
            break;
        }
        current = current->next;
    }
    return start;
}

void generate_general_code(char *code, node *b, node *n1, node *n2) {
    b->reg_result = next_reg();

    instruction_entry_t *lazy_op1 = NULL, *lazy_op2 = NULL;

    n1->code = remove_lazy_of_result(n1->code, n1->reg_result, &lazy_op1);
    if (lazy_op1 != NULL) {
        lazy_op1->entry->lazy = 0;
        lazy_op1->next = NULL;
        lazy_op1->previous = NULL;
    }
    n2->code = remove_lazy_of_result(n2->code, n2->reg_result, &lazy_op2);
     if (lazy_op2 != NULL) {
        lazy_op2->entry->lazy = 0;
        lazy_op2->next = NULL;
        lazy_op2->previous = NULL;
    }

    instruction_entry_t *instr = generate_instruction(code, n1->reg_result, n2->reg_result, b->reg_result);
    instr->entry->reg_result = b->reg_result;
    
    b->code = instr_lst_join(5, n1->code, n2->code, lazy_op1, lazy_op2, instr);
}

void generate_change_signal(node *b, node *parent) {
    if (parent->mark == LITERAL_T && parent->type == DT_INTEGER) {
        parent->code->entry->op2 = -(parent->code->entry->op2);
        b->reg_result = parent->reg_result;
        b->code = parent->code;
    } else {
        instruction_entry_t *instr = generate_instructionI("multI", parent->reg_result, -1, parent->reg_result);
        instr->entry->reg_result = parent->reg_result;
        b->reg_result = parent->reg_result;
        b->code = instr_lst_join(2, parent->code, instr);
    }
}

void generate_var_load(node *n) {
    int reg, offset;
    char *ident = (char *) n->value;
    get_var_mem_loc(ident, &reg, &offset);

    n->reg_result = next_reg();
    instruction_entry_t *store_instr = generate_instructionI("loadAI", reg, offset, n->reg_result);
    store_instr->entry->reg_result = n->reg_result;
    strcpy(store_instr->entry->mark_property, ident);
    
    comment_instruction(store_instr, "Carrega variável %s", ident);

    n->code = store_instr;
}

void generate_literal_load(node *n) {
    n->reg_result = next_reg();
    int value = *((int *) n->value);
    n->code = generate_instructionI("loadI", EMPTY, value, n->reg_result);
    n->code->entry->lazy = 1;
    n->code->entry->reg_result = n->reg_result;
}

void generate_var_assignment(char *ident, node *b, node *init) {
    if (init->mark == VAR_T) {
        generate_var_load(init);
    }
    int reg, offset;
    get_var_mem_loc(ident, &reg, &offset);
    instruction_entry_t *store_instr = generate_instructionS("storeAI", init->reg_result, reg, offset);
    comment_instruction(store_instr, "Grava variável %s", ident);
    strcpy(store_instr->entry->mark_property, ident);

    b->code = instr_lst_join(2, init->code, store_instr);
}

void generate_fun_return(node *s, node *e) {
    hashmap_t *fun_scope = function_scope();

    instruction_entry_t *store_result = generate_instructionS("storeAI", e->reg_result, RFP, 12);

    comment_instruction(e->code, "Início do retorno");
    comment_instruction(store_result, "Escreve o valor de retorno na pilha");

    instruction_entry_t *fun_return_value_mark = generate_mark(CODE_MARK_FUN_RETURN_VALUE_START, 0, 0, fun_scope->label);
    instruction_entry_t *fun_return_value_mark_end = generate_mark(CODE_MARK_FUN_RETURN_VALUE_END, 0, 0, fun_scope->label);

    if (strcmp(fun_scope->label, "main") == 0) {
        instruction_entry_t *instr_halt = generate_instruction("halt", EMPTY, EMPTY, EMPTY);
        comment_instruction(instr_halt, "Termina o programa");
        s->code = instr_lst_join(5, e->code, fun_return_value_mark,
                                    store_result, fun_return_value_mark_end, instr_halt);
    } else {
        int rsp_reg = next_reg();
        int rfp_reg = next_reg();
        int ret_reg = next_reg();

        instruction_entry_t *load_last_rsp = generate_instructionI("loadAI", RFP, 4, rsp_reg);
        load_last_rsp->entry->reg_result = rsp_reg;
        instruction_entry_t *copy_rsp = generate_instructionI("i2i", rsp_reg, EMPTY, RSP);
        copy_rsp->entry->reg_result = RFP;
        instruction_entry_t *load_last_rfp = generate_instructionI("loadAI", RFP, 8, rfp_reg);
        load_last_rfp->entry->reg_result = rfp_reg;
        instruction_entry_t *copy_rfp = generate_instructionI("i2i", rfp_reg, EMPTY, RFP);
        copy_rfp->entry->reg_result = RFP;
        instruction_entry_t *load_ret_end = generate_instructionI("loadAI", RFP, 0, ret_reg);
        load_ret_end->entry->reg_result = ret_reg;
        instruction_entry_t *jump_ret = generate_jump(ret_reg);

        comment_instruction(load_ret_end, "Carrega end de retorno");
        comment_instruction(load_last_rsp, "Carrega ultimo RSP");
        comment_instruction(load_last_rfp, "Carrega ultimo RFP");

        s->code = instr_lst_join(10, e->code, fun_return_value_mark, store_result,
                                 fun_return_value_mark_end, load_last_rsp, copy_rsp, 
                                 load_last_rfp, copy_rfp, 
                                 load_ret_end, jump_ret);
    }
}

void insert_restore_reg_code(node *n, instruction_entry_t *restore_code) {
    instruction_entry_t *current = n->code;
    while (current != NULL) {
        while (current != NULL && 
                (current->entry->op1 != CODE_MARK_FUN_CALL_END && current->entry->op1 != OT_MARK)) {
            current = current->next;
        }
        if (current != NULL) {
            instruction_entry_t *copy = instr_lst_copy(restore_code);
            int result_reg = current->previous->entry->op3; // loadAI rsp, 12 => result_reg
            // não restaura o registrador usado para o retorno da funçao
            instruction_entry_t *temp = copy;
            while (temp != NULL) {
                if (temp->entry->op3 == result_reg && temp->entry->op3_type == OT_REG) {
                    if (temp->previous != NULL) {
                        temp->previous->next = temp->next;
                    }
                    if (temp->next != NULL) {
                        temp->next->previous = temp->previous;
                    }

                    if (temp == copy) { // removemos a primeira instrução
                        copy = copy->next;
                    }
                    free(temp->entry);
                    free(temp);
                    break;
                }
                temp = temp->next;
            }

            // colocamos a restauração dos regs depois do store do resultado
            if (copy != NULL) {
                instruction_entry_t *previous = current->previous;
                if (previous != NULL) {
                    previous->next = copy;
                    copy->previous = previous;
                }
                instr_lst_join(2, copy, current);
            }
            current = current->next;
        }
    }
}

instruction_entry_t *optimize_iloc_register_usage(instruction_entry_t *code) {
    graph_t *graph = generate_depend_graph(code);
    int *node_colors;

    // tenta colorir o grafo com 3 cores primeiro e vai aumentando
    int result = 0;
    int colors = 2;
    while (result == 0) {
        colors++;
        result = try_color_graph(colors, graph, &node_colors);
    }

    instruction_entry_t *instruction_list_copy = code;

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
        
        if (current_instruction->reg_result >= 0) {
            current_instruction->reg_result = node_colors[current_instruction->reg_result];
        }

        instruction_list_copy = instruction_list_copy->next;
    }
    
    return code;
}

void generate_fun_decl(node *fun) {
    char *fun_name = (char*) fun->label;

    hashmap_t *global_scope;
    hashmap_t *function_scope = current_scope();
    hashmap_value_t *fun_decl = find_declaration(fun_name, &global_scope);

    instruction_entry_t *instr_fun_label = generate_label_instruction(fun_decl->fun_label);
    instruction_entry_t *update_rfp = generate_instructionI("i2i", RSP, EMPTY, RFP);
    update_rfp->entry->reg_result = RFP;
    int rsp_gap = function_scope->offset + 4 * 4; // offset de variáveis + end retorno, rsp salvo, rfp salvo, valor de retorno

    comment_instruction(instr_fun_label, "Declaração da função %s", fun_name);

    // If this function has childrens
    if (fun->nodes[0] != NULL)
    {
        instruction_entry_t *update_rsp = NULL;
        if (fun_decl->fun_call_other_fun >= 1) {
            update_rsp = generate_instructionI("addI", RSP, rsp_gap, RSP);
        }

        instruction_entry_t *fun_body_code = fun->nodes[0]->code;
        instruction_entry_t *start_fun_mark = generate_mark(CODE_MARK_FUN_START, 0, 0, fun_name);
        instruction_entry_t *end_fun_mark = generate_mark(CODE_MARK_FUN_END, 0, 0, fun_name);

        fun->code = instr_lst_join(6, start_fun_mark, instr_fun_label, update_rfp, 
                                      update_rsp, fun_body_code, end_fun_mark);

        fun->code = optimize_iloc_register_usage(fun->code);

        instruction_entry_t *current = fun_body_code;
        instruction_entry_t *tail;
        int regs = compute_live_out(fun_body_code);
        // print_graph(graph);
        // print_instr_lst(fun->code);
        while (current != NULL) {
            int need_save_regs = 0;
            instruction_entry_t *store_used_reg = generate_mark(CODE_MARK_SAVE_REGS_START, 0, 0, "");
            instruction_entry_t *load_used_reg = generate_mark(CODE_MARK_LOAD_REGS_START, 0, 0, "");

            // navega até a próxima finalização de passagem de argumentos de uma função
            while (current != NULL && 
                    (current->entry->op1 != CODE_MARK_PUTING_PARAMS_END && current->entry->op1 != OT_MARK)) {
                current = current->next;
            }

            if (current == NULL) break;

            // criamos a lista de instruções usadas para salvar e restaurar os registradores
            for (int reg = 0; reg < regs; reg++) {
                if (current->entry->live_out[reg] == 1) {
                    need_save_regs = 1;
                    instruction_entry_t *load_inst = generate_instructionI("loadAI", RFP, rsp_gap, reg);
                    load_inst->entry->reg_result = reg;
                    instruction_entry_t *store_inst = generate_instructionS("storeAI", reg, RFP, rsp_gap);

                    store_used_reg = instr_lst_join(2, store_used_reg, store_inst);
                    load_used_reg = instr_lst_join(2, load_used_reg, load_inst);
                    rsp_gap += 4;
                }
            }
            store_used_reg = instr_lst_join(2, store_used_reg, generate_mark(CODE_MARK_SAVE_REGS_END, 0, 0, ""));
            comment_instruction(store_used_reg, "Salva o estado dos registradores usados na função");
            load_used_reg = instr_lst_join(2, load_used_reg, generate_mark(CODE_MARK_LOAD_REGS_END, 0, 0, ""));
            comment_instruction(load_used_reg, "Restaura o estado dos registradores usados");

            if (need_save_regs == 1) {
                // salvamos os registradores ativos antes de ir pra função
                tail = current->next;
                current->next = NULL;
                tail->previous = NULL;
                fun_body_code = instr_lst_join(3, fun_body_code, store_used_reg, tail);

                // navega até voltar da função
                while (current != NULL && 
                        (current->entry->op1 != CODE_MARK_FUN_CALL_JUMP_END && current->entry->op1 != OT_MARK)) {
                    current = current->next;
                }

                // restauramos os registradores depois da volta da função
                tail = current->next;
                current->next = NULL;
                tail->previous = NULL;
                fun_body_code = instr_lst_join(3, fun_body_code, load_used_reg, tail);
            }

            if (current != NULL) {
                current = current->next;
            }
        }

        // gravamos os registradores usados no início da função
        if (update_rsp != NULL) {
            update_rsp->entry->op2 = rsp_gap;
        }
    }
    // resetamos o contador de registradores
    last_reg = 0;
}

void generate_fun_call(node *s, node *params) {
    char *target_fun_name = (char *) s->value;
    char *current_fun_name = function_scope()->label;
    hashmap_t *global_scope;
    hashmap_value_t *target_fun_decl = find_declaration(target_fun_name, &global_scope);
    hashmap_value_t *current_fun_decl = find_declaration(current_fun_name, &global_scope);

    instruction_entry_t *start_fun_call_mark = generate_mark(CODE_MARK_FUN_CALL_START, 0, 0, target_fun_name);
    instruction_entry_t *end_fun_call_mark = generate_mark(CODE_MARK_FUN_CALL_END, 0, 0, target_fun_name);
    instruction_entry_t *call_jump_mark_start = generate_mark(CODE_MARK_FUN_CALL_JUMP_START, 0, 0, target_fun_name);
    instruction_entry_t *call_jump_mark_end = generate_mark(CODE_MARK_FUN_CALL_JUMP_END, 0, 0, target_fun_name);
    instruction_entry_t *store_rsp = generate_instructionS("storeAI", RSP, RSP, 4);
    instruction_entry_t *store_rfp = generate_instructionS("storeAI", RFP, RSP, 8);
    current_fun_decl->fun_call_other_fun += 1;

    // para cada parametro da função cria um store
    instruction_entry_t *param_lst = NULL;
    if (params != NULL) {
        int param_offset = 16;
        param_lst = params->code;
        param_lst = instr_lst_join(2, param_lst, generate_mark(CODE_MARK_PUTING_PARAMS_START, 0, 0, target_fun_name));
        node *p = params;
        while (p != NULL) {
            instruction_entry_t *p_store = generate_instructionS("storeAI", p->reg_result, RSP, param_offset);
            comment_instruction(p_store, "grava o parametro %d da função", (param_offset - 16) / 4 + 1);
            param_lst = instr_lst_join(2, param_lst, p_store);
            param_offset += 4;
            p = p->next;
        }
        param_lst = instr_lst_join(2, param_lst, generate_mark(CODE_MARK_PUTING_PARAMS_END, 0, 0, target_fun_name));
    }

    // prepara o endereço de retorno que é após essas 2 instr e do jump
    int ret_reg = next_reg();
    instruction_entry_t *cal_ret_end = generate_instructionI("addI", RPC, 3, ret_reg);
    cal_ret_end->entry->reg_result = ret_reg;
    instruction_entry_t *store_ret_end = generate_instructionS("storeAI", ret_reg, RSP, 0);
    instruction_entry_t *jump_fun = generate_jumpI(target_fun_decl->fun_label);

    int ret_value_reg = next_reg();
    instruction_entry_t *load_return_value = generate_instructionI("loadAI", RSP, 12, ret_value_reg);
    load_return_value->entry->reg_result = ret_value_reg;

    comment_instruction(store_rsp, "Inicio da chamada de %s()", target_fun_name);
    comment_instruction(load_return_value, "Carrega o valor de retorno de %s()", target_fun_name);
    comment_instruction(jump_fun, "Salta para a função %s()", target_fun_name);

    s->reg_result = ret_value_reg;
    s->code = instr_lst_join(11, start_fun_call_mark, store_rsp, store_rfp, 
                                param_lst, call_jump_mark_start, cal_ret_end,
                                store_ret_end, jump_fun, load_return_value, 
                                call_jump_mark_end, end_fun_call_mark);
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

        if (instr_lst_end_with_code(b_true->code, "jump") == 1) {
            // já tem um salto, nao precisa do outro
            b->code = instr_lst_join(6, e->code, instr_true_label, 
                                        b_true->code, instr_false_label, 
                                        b_false->code, instr_end_label);
        } else {
            b->code = instr_lst_join(7, e->code, instr_true_label, 
                                        b_true->code, jump_end, instr_false_label, 
                                        b_false->code, instr_end_label);
        }
        
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
    if (entry == NULL) {
        printf("LIST NULL\n");
        return;
    }
    instruction_entry_t *current = entry;
    while (current != NULL && current->entry != NULL) {
        printf("#");
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

int print_mark(instruction_t *inst) {
    int char_counter = 0;
    char_counter += printf("// MARK: ");
    switch (inst->op1)
    {
    case CODE_MARK_FUN_START:
        char_counter += printf("CODE_MARK_FUN_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_END:
        char_counter += printf("CODE_MARK_FUN_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_SAVE_REGS_START:
        char_counter += printf("CODE_MARK_SAVE_REGS_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_SAVE_REGS_END:
        char_counter += printf("CODE_MARK_SAVE_REGS_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_LOAD_REGS_START:
        char_counter += printf("CODE_MARK_LOAD_REGS_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_LOAD_REGS_END:
        char_counter += printf("CODE_MARK_LOAD_REGS_END p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_INIT_CODE_START:
        char_counter += printf("CODE_MARK_INIT_CODE_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_INIT_CODE_END:
        char_counter += printf("CODE_MARK_INIT_CODE_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_CALL_START:
        char_counter += printf("CODE_MARK_FUN_CALL_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_CALL_END:
        char_counter += printf("CODE_MARK_FUN_CALL_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_CALL_JUMP_START:
        char_counter += printf("CODE_MARK_FUN_CALL_JUMP_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_CALL_JUMP_END:
        char_counter += printf("CODE_MARK_FUN_CALL_JUMP_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_RET_START:
        char_counter += printf("CODE_MARK_FUN_RET_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_RET_END:
        char_counter += printf("CODE_MARK_FUN_RET_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_RETURN_VALUE_START:
        char_counter += printf("CODE_MARK_FUN_RETURN_VALUE_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_FUN_RETURN_VALUE_END:
        char_counter += printf("CODE_MARK_FUN_RETURN_VALUE_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_PUTING_PARAMS_START:
        char_counter += printf("CODE_MARK_PUTING_PARAMS_START, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    case CODE_MARK_PUTING_PARAMS_END:
        char_counter += printf("CODE_MARK_PUTING_PARAMS_END, p1 = %d, p2 = %d", inst->op2, inst->op3);
        break;
    default:
        char_counter += printf("%d, p1 = %d, p2 = %d", inst->op1, inst->op2, inst->op3);
        break;
    }
    return char_counter;
}

void print_instruction(instruction_t *inst) {
    int char_counter = 0;
    if (strncmp(inst->code, "jump", 4) == 0) {
        char_counter += printf("%s => ", inst->code);
        char_counter += print_instr_param(inst->op1, inst->op1_type);
    } else if (inst->op1_type == OT_LABEL) {
        char_counter += printf("L%d:", inst->op1);
    } else if (inst->op1_type == OT_MARK) {
        char_counter += print_mark(inst);
    } else if (strncmp(inst->code, "jump", 4) == 0) {
        char_counter += printf("%s => ", inst->code);
        char_counter += print_instr_param(inst->op1, inst->op1_type);
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
        *offset = decl->men_offset;
    } else {
        *reg = RFP;
        *offset = decl->men_offset + 16;
    }
}

void comment_instruction(instruction_entry_t *entry, char *message, ...) {
    va_list argptr;
    va_start(argptr, message);
    vsprintf(entry->entry->comment, message, argptr);
    va_end(argptr);
}

instruction_entry_t *generate_label_instruction(int label) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_LABEL;
    instr->op1 = label;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_DISABLED;
    instr->op3 = EMPTY;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instructionB(int reg, int label1, int label2) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "cbr");
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_REG;
    instr->op1 = reg;
    instr->op2_type = OT_LABEL;
    instr->op2 = label1;
    instr->op3_type = OT_LABEL;
    instr->op3 = label2;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instruction(char *code, int reg1, int reg2, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_REG;
    instr->op2 = reg2;
    instr->op3_type = OT_REG;
    instr->op3 = reg3;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instructionI(char *code, int reg1, int value, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_IMED;
    instr->op2 = value;
    instr->op3_type = OT_REG;
    instr->op3 = reg3;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_instructionS(char *code, int reg1, int value, int reg3) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, code);
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_REG;
    instr->op1 = reg1;
    instr->op2_type = OT_REG;
    instr->op2 = value;
    instr->op3_type = OT_IMED;
    instr->op3 = reg3;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_jump(int reg) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "jump");
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_REG;
    instr->op1 = reg;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_DISABLED;
    instr->op3 = EMPTY;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_jumpI(int label) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "jumpI");
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_LABEL;
    instr->op1 = label;
    instr->op2_type = OT_DISABLED;
    instr->op2 = EMPTY;
    instr->op3_type = OT_DISABLED;
    instr->op3 = EMPTY;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, "\0");
    return instr_lst_create_new(instr);
}

instruction_entry_t *generate_mark(int type, int p1, int p2, char *param) {
    instruction_t *instr = (instruction_t*) malloc(sizeof(instruction_t));
    strcpy(instr->code, "");
    instr->lazy = 0;
    instr->reg_result = -1;
    instr->op1_type = OT_MARK;
    instr->op1 = type;
    instr->op2_type = OT_MARK;
    instr->op2 = p1;
    instr->op3_type = OT_MARK;
    instr->op3 = p2;
    strcpy(instr->comment, "\0");
    strcpy(instr->mark_property, param);
    return instr_lst_create_new(instr);
}

