

/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "semantic.h"
#include "stack.h"
#include "types.h"
#include "asp.h"
#include "list.h"
#include "hashmap.h"
#include "errors.h"

stack_t* scope_stack;

extern int get_line_number(void);

void hashmap_print(hashmap_t *map);

int size_data_type(enum data_type type) {
    if (type == DT_BOOL) return 1;
    if (type == DT_CHAR) return 1;
    if (type == DT_FLOAT) return 8;
    if (type == DT_INTEGER) return 4;
    return 0;
}

void print_data_type(enum data_type type) {
    if (type == DT_BOOL) printf("bool");
    else if (type == DT_CHAR) printf("char");
    else if (type == DT_FLOAT) printf("float");
    else if (type == DT_INTEGER) printf("int");
    else if (type == DT_STRING) printf("string");
}

void list_print(list_t* l) {
    printf("[");
    for (int i = 0; i < l->size - 1; i++) {
        print_data_type(l->entries[i]->decl_type);
        printf(" %s, ", l->entries[i]->ident);
    }
    if (l->size > 0) {
        print_data_type(l->entries[l->size-1]->decl_type);
        printf(" %s", l->entries[l->size-1]->ident);
    }
    printf("]");
}

void show_error_message(int code, char *message, ...) {
    fprintf(stderr, "Erro semântico:%d - ", get_line_number());
    va_list argptr;
    va_start(argptr, message);
    vfprintf(stderr, message, argptr);
    va_end(argptr);
    fprintf(stderr, "\n");
    exit(code);
}

// Guardam a informação dos tipo e atributos de 
// uma lista de declaração de variáveis
int is_static_decl = 0;
int is_const_delc = 0;
enum data_type type_decl = DT_INTEGER;

void init_decl_list(int is_static, int is_const, enum data_type type) {
    is_static_decl = is_static;
    is_const_delc = is_const;
    type_decl = type;
}

hashmap_value_t *create_hashmap_value(
    enum data_type type,
    enum nature_type nature,
    int mem_mult,
    list_t *args
) {
    hashmap_value_t *value = (hashmap_value_t *) malloc(sizeof(hashmap_value_t));
    value->line = get_line_number();
    value->nature = nature;
    value->men_size = mem_mult * size_data_type(type);
    value->type = type;
    value->args = args;
    value->fun_label = -1;
    value->men_offset = 0;

    return value;
}

void semantic_init() {
    scope_stack = stack_init();
    hashmap_t* global_table = hashmap_init("global");
    stack_push(scope_stack, global_table);
}

stack_entry_t *current_scope() {
    return stack_peek(scope_stack);
}

void free_scopes() {
    for (int i = 0; i < scope_stack->actual_capacity; i++) {
        hashmap_destroy(scope_stack->entries[i]);
        scope_stack->entries[i] = NULL;
    }
    stack_destroy(scope_stack);
}

void enter_scope(char *label) {
    hashmap_t *current_scope = stack_peek(scope_stack);
    hashmap_t* new_table = hashmap_init(label);
    // Escopos alinhados herdam o offset da tabela pai
    if (strcmp(current_scope->label, "global") != 0) {
        new_table->offset = current_scope->offset;
    }
    stack_push(scope_stack, new_table);
}

void exit_scope() {
    hashmap_t *current_scope = stack_pop(scope_stack);
    hashmap_t *out_scope = stack_peek(scope_stack);
    if (strcmp(out_scope->label, "global") != 0) {
        out_scope->offset = current_scope->offset;
    } else {
        // Saiu de um função e o out_scope é o global
        hashmap_value_t *value = hashmap_get(out_scope, current_scope->label);
        value->men_size = current_scope->offset;
    }
    // hashmap_print(current_scope);
    hashmap_destroy(current_scope);
}

void verify_alread_declared(hashmap_t *current_scope, char *ident) {
    hashmap_value_t *value = hashmap_get(current_scope, ident);
    if (value != NULL) { // Ja tem uma função com esse nome declarado
        show_error_message(ERR_DECLARED, "Variável \"%s\" já está declarada neste escopo", ident);
    }
}

hashmap_value_t *ident_var_declaration_item(char *ident) {
    return ident_var_declaration(ident, type_decl, is_static_decl);
}

hashmap_value_t *ident_var_declaration_init_item(char *ident, node *init) {
    enum data_type infered_type = infer_expression_type(init);
    if (infered_type == type_decl && type_decl == DT_STRING) {
        hashmap_value_t *value = ident_var_declaration(ident, type_decl, is_static_decl);
        value->men_size = strlen((char *) init->value);
    } else if (can_implicit_conversion(infered_type, type_decl)) {
        return ident_var_declaration(ident, type_decl, is_static_decl);
    } else if (type_decl == DT_STRING) {
        show_error_message(ERR_STRING_TO_X, "Erro ao declarar \"%s\" - Não podemos fazer coersão de string", ident);
    } else if (type_decl == DT_CHAR) {
        show_error_message(ERR_CHAR_TO_X, "Erro ao declarar \"%s\" - Não podemos fazer coersão de char", ident);
    }
    return NULL;
}

hashmap_value_t *ident_var_declaration(
    char *ident,
    enum data_type type,
    int is_static
) {
    hashmap_t *current_scope = stack_peek(scope_stack);
    if (current_scope == NULL) return NULL;
    verify_alread_declared(current_scope, ident);

    hashmap_value_t *value = create_hashmap_value(type, NT_VARIABLE, 1, NULL);
    value->men_offset = current_scope->offset;
    current_scope->offset += value->men_size;
    hashmap_put(current_scope, ident, value);
    return value;
}

void ident_vector_declaration(
    char *ident,
    enum data_type type,
    int is_static,
    int vector_size
) {
    if (type == DT_STRING) {
        show_error_message(ERR_STRING_VECTOR, "Erro ao declarar \"%s\" - Um vetor não pode ser do tipo string", ident);
    }

    hashmap_t *current_scope = stack_peek(scope_stack);
    verify_alread_declared(current_scope, ident);

    hashmap_value_t *value = create_hashmap_value(type, NT_VECTOR, vector_size, NULL);
    value->men_offset = current_scope->offset;
    current_scope->offset += value->men_size;
    hashmap_put(current_scope, ident, value);    
}

void literal_use(node* literal) {
    if (literal->mark != LITERAL_T) return;
    hashmap_t *global_scope = scope_stack->entries[0];
    char *key = literal->label;
    hashmap_value_t *value = hashmap_get(global_scope, key);
    if (value == NULL) {
        value = create_hashmap_value(literal->type, NT_LITERAL, 1, NULL);
        if (literal->type == DT_STRING) {
            value->men_size = strlen(key);
        }
        value->men_offset = global_scope->offset;
        // global_scope->offset += value->men_size;
        hashmap_put(global_scope, key, value);
    }
}

void ident_var_array_global_decl_list(
    enum data_type type,
    int is_static,
    node *list
) {
    node *p = list;
    while (p != NULL) {
        if (p->mark == VAR_T) {
            ident_var_declaration(p->label, type, is_static);
        } else if (p->mark == ARRAY_T) {
            int vector_size = *((int *) p->nodes[1]->value);
            ident_vector_declaration(p->nodes[0]->label, type, is_static, vector_size);
        }
        p = p->next;
    } 
}

void ident_fun_declaration(
    char *ident,
    enum data_type return_type,
    node *params,
    int label
) {
    hashmap_t *current_scope = stack_peek(scope_stack);
    verify_alread_declared(current_scope, ident);

    if (return_type == DT_STRING) {
        show_error_message(ERR_FUNCTION_STRING, "Erro ao declarar \"%s\" - String não pode ser o retorno de uma função", ident);
    }

    enter_scope(ident);

    list_t *args = list_init();
    node *p = params;
    while (p != NULL) {
        if (p->type == DT_STRING) {
            show_error_message(ERR_FUNCTION_STRING, "Erro ao declarar \"%s\" - String não pode ser um parâmetro de função", ident);
        }
        declaration_type_t *decl = (declaration_type_t*) malloc(sizeof(declaration_type_t));
        decl->decl_type = p->type;
        decl->ident = p->label;
        decl->is_const = 0;
        decl->is_static = 0;

        list_add(args, decl);
        ident_var_declaration(decl->ident, decl->decl_type, decl->is_static);

        p = p->next;
    }       

    hashmap_value_t *value = create_hashmap_value(return_type, NT_FUNCTION, 0, args);
    value->fun_label = label;
    hashmap_put(current_scope, ident, value);
}

hashmap_value_t *find_declaration(char *ident, hashmap_t **fold_scope) {
    hashmap_t *scope;
    hashmap_value_t *value;
    int index = scope_stack->index;
    while (index >= 0) {
        scope = scope_stack->entries[index];
        value = hashmap_get(scope, ident);
        if (value != NULL) {
            if (fold_scope != NULL) {
                *fold_scope = scope;
            }
            return value;
        }
        index--;
    }
    return NULL;
}

hashmap_value_t *ident_var_use(char *ident) {
    hashmap_value_t *decl = find_declaration(ident, NULL);
    if (decl == NULL) {
        show_error_message(ERR_UNDECLARED, "Erro ao usar \"%s\" - Variável não declarada anteriormente", ident);
    }
    if (decl->nature == NT_FUNCTION) {
        show_error_message(ERR_FUNCTION, "Erro ao usar \"%s\" - Função sendo usada como variável", ident);
    } 
    if (decl->nature == NT_VECTOR) {
        show_error_message(ERR_VECTOR, "Erro ao usar \"%s\" - Vetor sendo usada como variável", ident);
    }
    return decl;
}

hashmap_value_t *ident_vector_use(char *ident, node *index) {
    hashmap_value_t *decl = find_declaration(ident, NULL);
    if (decl == NULL) {
        show_error_message(ERR_UNDECLARED, "Erro ao usar \"%s\" - Vetor não declarado anteriormente", ident);
    }
    if (decl->nature == NT_FUNCTION) {
        show_error_message(ERR_FUNCTION, "Erro ao usar \"%s\" - Função sendo usada como vetor", ident);
    } 
    if (decl->nature == NT_VARIABLE) {
        show_error_message(ERR_VARIABLE, "Erro ao usar \"%s\" - Variável sendo usada como vetor", ident);
    }
    enum data_type index_type = infer_expression_type(index);
    if (index_type != DT_INTEGER) { // indice não avalia para inteiro
        show_error_message(ERR_VECTOR, "Erro ao usar \"%s\" - Indice do vetor deve ser um inteiro", ident);
    }
    return decl;
}

void ident_fun_use(char *ident, node *params) {
    hashmap_value_t *value = hashmap_get(scope_stack->entries[0], ident);
    if (value == NULL) {
        show_error_message(ERR_UNDECLARED, "Erro ao usar \"%s\" - Função não declarada anteriormente", ident);
    }
    if (value->nature == NT_VARIABLE) {
        show_error_message(ERR_VARIABLE, "Erro ao usar \"%s\" - Variável sendo usada como função", ident);
    }
    if (value->nature == NT_VECTOR) {
        show_error_message(ERR_VECTOR, "Erro ao usar \"%s\" - Vetor sendo usada como função", ident);
    }

    list_entry_t *item;
    enum data_type p_data_type;
    int p_index = 0;
    node *p = params;
    while (p != NULL) {
        item = list_get(value->args, p_index);
        if (item == NULL) {
            show_error_message(ERR_MISSING_ARGS, "Argumentos sobrando na chamada da função \"%s\"", ident);
        }
        p_data_type = infer_expression_type(p);
        if (p_data_type == DT_STRING) {
            show_error_message(ERR_FUNCTION_STRING, "Erro ao usar \"%s\" - String não pode ser um parâmetro de função", ident);
        }
        if (can_implicit_conversion(p_data_type, item->decl_type) == 0) {
            show_error_message(ERR_WRONG_TYPE_ARGS, "Tipo errado para a função \"%s\"", ident);
        }
        p_index++;
        p = p->next;
    }
    if (value->args->size > p_index) {
        show_error_message(ERR_MISSING_ARGS, "Argumentos faltantes na chamada da função \"%s\"", ident);
    }
}

int get_string_size(node* value) {
    if (value->mark == LITERAL_T && value->type == DT_STRING) {
        return strlen((char *) value->value);
    } else if (value->mark == VAR_T) {
        char *ident = (char *) value->value;
        hashmap_value_t *decl = find_declaration(ident, NULL);
        if (decl == NULL) {
            show_error_message(ERR_UNDECLARED, "Erro ao usar \"%s\" - Identificador não declarado anteriormente", ident);
        }
        if (decl->type == DT_STRING) {
            return decl->men_size;
        }
    }
    return 0;
}

void ident_var_set(char *ident, node *value) {
    hashmap_value_t *decl = ident_var_use(ident);
    enum data_type infered_type = infer_expression_type(value);
    if (!can_implicit_conversion(decl->type, infered_type)) {
        show_error_message(ERR_WRONG_TYPE, "Erro ao alterar \"%s\" - Tipo dos dados não são compatíveis", ident);
    }
    if (decl->type == DT_STRING) {
        int new_size = get_string_size(value);
        if (decl->men_size < new_size) {
            show_error_message(ERR_STRING_MAX, "Erro ao alterar \"%s\" - Tamanho da string deve ser menor ou igual a %d, informado %d", ident, decl->men_size, new_size);
        }
    }
}

void ident_vector_set(char *ident, node *index, node *value) {
    hashmap_value_t *decl = ident_vector_use(ident, index);
    enum data_type infered_type = infer_expression_type(value);
    if (!can_implicit_conversion(decl->type, infered_type)) {
        show_error_message(ERR_WRONG_TYPE, "Erro ao alterar \"%s\" - Tipo dos dados não são compatíveis", ident);
    }
}

void verify_input_use(node *ident) {
    enum data_type infered_type = infer_expression_type(ident);
    if (infered_type != DT_FLOAT && infered_type != DT_INTEGER) {
        show_error_message(ERR_WRONG_PAR_INPUT, "Erro no input \"%s\" - O tipo do parâmetro precisa ser um int ou float", ident);
    }
}

void verify_output_use(node *ident_or_literal) {
    enum data_type infered_type = infer_expression_type(ident_or_literal);
    if (infered_type != DT_FLOAT && infered_type != DT_INTEGER) {
        show_error_message(ERR_WRONG_PAR_OUTPUT, "Erro no output \"%s\" - O tipo do parâmetro precisa ser um int ou float", ident_or_literal);
    }
}

void verify_return(node *expression) {
    hashmap_t *scope = scope_stack->entries[1]; // depois do global é o escopo da função
    hashmap_value_t *value = find_declaration(scope->label, NULL);
    enum data_type infered_return = infer_expression_type(expression);
    if (infered_return == DT_STRING) {
        show_error_message(ERR_FUNCTION_STRING, "Erro no retorno de \"%s\" - String não pode ser um retorno de função", scope->label);
    }
    if (infered_return != value->type) {
        show_error_message(ERR_WRONG_PAR_RETURN, "Erro no retorno de \"%s\" - O tipo do retorno deve ser o mesmo do tipo da função", scope->label);
    }
}

void verify_shift(int p) {
    if (p > 16) {
        show_error_message(ERR_WRONG_PAR_SHIFT, "Erro no shift - O valor máximo é 16");
    }
}

int can_implicit_conversion(enum data_type source, enum data_type dest) {
    if (source == dest) return 1;
    if (source == DT_INTEGER && (dest == DT_FLOAT || dest == DT_BOOL)) {
        return 1;
    }
    if (source == DT_BOOL && (dest == DT_FLOAT || dest == DT_INTEGER)) {
        return 1;
    }
    if (source == DT_FLOAT && (dest == DT_BOOL || dest == DT_INTEGER)) {
        return 1;
    }
    return 0;
}

enum data_type coercion_type(enum data_type type1, enum data_type type2) {
    if (type1 == type2) return type1;
    if (type1 == DT_FLOAT || type2 == DT_FLOAT) return DT_FLOAT;
    if (type1 == DT_INTEGER || type2 == DT_INTEGER) return DT_INTEGER;
    return DT_BOOL;
}

enum data_type infer_expression_type(node *root) {
    if (root->mark == LITERAL_T) {
        return root->type;
    }
    char *ident = NULL;
    if (root->mark == VAR_T) {
        ident = (char *) root->value;
    } else if (root->mark == FUN_CALL_T) {
        ident = (char *) root->value;
    } else if (root->mark == ARRAY_T) {
        ident = (char *) root->nodes[0]->value;
    }
    if (ident != NULL) {
        hashmap_value_t *value = find_declaration(ident, NULL);
        if (value == NULL) {
            show_error_message(ERR_UNDECLARED, "Erro ao usar \"%s\" - Identificador não declarado anteriormente", ident);
        }
        return value->type;
    }

    if (root->mark == EXPRES_T) {
        enum data_type infered = infer_expression_type(root->nodes[0]);
        for (int i = 1; i < root->size; i++) {
            infered = coercion_type(infered, infer_expression_type(root->nodes[i]));
        }
        return infered;
    }
    return DT_UNKNOWN;
}

void hashmap_print(hashmap_t *map) {
    int fold = 0;
    int index = 0;
    printf("# hashmap %s {\n", map->label);
    if (map != NULL) {
        printf("(offset = %d)\n", map->offset);
        while (fold < map->size) {
            hashmap_entry_t *entry = map->values[index++];
            if (entry != NULL) {
                printf("#\tL: %d\t[%s]\t", entry->value->line, entry->key);
                hashmap_value_t *value = entry->value;
                if (value->nature == NT_FUNCTION) {
                    printf("FUNC\t");
                    list_print(value->args);
                    printf(" -> ");
                    print_data_type(value->type);
                    printf("\tMEN_SIZE %d", value->men_size);
                    printf("\tLABEL: %d", value->fun_label);
                } else if (value->nature == NT_VARIABLE) {
                    printf("VAR\t");
                    print_data_type(value->type);
                    printf("\tMEN_SIZE %d", value->men_size);
                } else if (value->nature == NT_VECTOR) {
                    printf("ARRAY\t");
                    print_data_type(value->type);
                    printf("[%d]", value->men_size/size_data_type(value->type));
                    printf("\tMEN_SIZE %d", value->men_size);
                } else if (value->nature == NT_LITERAL) {
                    printf("LIT\t");
                    print_data_type(value->type);
                    printf("\tMEN_SIZE %d", value->men_size);
                }
                printf("\n");
                fold++;
            }
        }
    }
    printf("# }\n");
}

void print_stack() {
    if (scope_stack != NULL) {
        for (int i = 0; i <= scope_stack->index; i++) {
            hashmap_print(scope_stack->entries[i]);
        }
    }
}
