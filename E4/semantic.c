
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semantic.h"
#include "stack.h"
#include "types.h"
#include "asp.h"
#include "list.h"
#include "hashmap.h"
#include "errors.h"

enum data_type current_data_process = DT_UNKNOWN;

void hashmap_print(hashmap_t *map);

int size_data_type(enum data_type type) {
    if (type == DT_BOOL) return 1;
    if (type == DT_CHAR) return 1;
    if (type == DT_FLOAT) return 8;
    if (type == DT_INTEGER) return 4;
    return 0;
}

hashmap_value_t *create_hashmap_value(
    enum data_type type,
    enum nature_type nature,
    int mem_mult,
    list_t *args
) {
    hashmap_value_t *value = (hashmap_value_t *) malloc (sizeof(hashmap_value_t));
    value->line = -1;
    value->nature = nature;
    value->men_size = mem_mult * size_data_type(type);
    value->type = type;
    value->args = args;

    return value;
}

void semantic_init() {
    printf("semantic_init\n");

    scope_stack = stack_init();
    hashmap_t* global_table = hashmap_init();
    stack_push(scope_stack, global_table);
}

void enter_scope() {
    printf("enter_scope\n");
    hashmap_t* new_table = hashmap_init();
    stack_push(scope_stack, new_table);
}

void exit_scope() {
    printf("exit_scope\n");
    hashmap_t *current_scope = stack_pop(scope_stack);
    hashmap_print(current_scope);
    // free(current_scope);
}

void verify_alread_declared(hashmap_t *current_scope, char *ident) {
    hashmap_value_t *value = hashmap_get(current_scope, ident);
    if (value != NULL) { // Ja tem uma função com esse nome declarado
        printf("ERROR - ERR_DECLARED\n");
        exit(ERR_DECLARED);
    }
}

void ident_var_declaration(
    char *ident,
    enum data_type type,
    int is_static
) {
    printf("ident_var_declaration\n");

    hashmap_t *current_scope = stack_peek(scope_stack);
    verify_alread_declared(current_scope, ident);

    hashmap_value_t *value = create_hashmap_value(type, NT_VARIABLE, 1, NULL);
    hashmap_put(current_scope, ident, value);
}

void ident_vector_declaration(
    char *ident,
    enum data_type type,
    int is_static,
    int vector_size
) {
    printf("ident_vector_declaration\n");

    if (type == DT_STRING) {
        printf("ERROR - ERR_STRING_VECTOR\n");
        exit(ERR_STRING_VECTOR);
    }

    hashmap_t *current_scope = stack_peek(scope_stack);
    verify_alread_declared(current_scope, ident);

    hashmap_value_t *value = create_hashmap_value(type, NT_VECTOR, vector_size, NULL);
    hashmap_put(current_scope, ident, value);    
}

void ident_var_array_local_decl_list(
    enum data_type type,
    int is_static,
    int is_const,
    node *list
) {
    printf("ident_var_array_local_decl_list\n");
    print_tree_labels(list);
}

void ident_var_array_global_decl_list(
    enum data_type type,
    int is_static,
    node *list
) {
    printf("ident_var_array_global_decl_list\n");

    node *p = list;
    while (p != NULL) {
        if (p->mark == DECL_VAR_T) {
            ident_var_declaration(p->label, type, is_static);
        } else if (p->mark == DECL_ARRAY_T) {
            int vector_size = *((int *) p->nodes[1]->value);
            ident_vector_declaration(p->nodes[0]->label, type, is_static, vector_size);
        }
        p = next_node(p);
    } 
}

void ident_fun_declaration(
    char *ident,
    enum data_type return_type,
    node *params
) {
    printf("ident_fun_declaration\n");
    
    hashmap_t *current_scope = stack_peek(scope_stack);
    verify_alread_declared(current_scope, ident);

    list_t *args = list_init();
    if (params != NULL) {
        node *p = params;
        while (p != NULL) {
            if (p->type == DT_STRING) {
                printf("ERROR - ERR_FUNCTION_STRING\n");
                exit(ERR_FUNCTION_STRING);
            }
            declaration_type_t *decl = (declaration_type_t*) malloc(sizeof(declaration_type_t));
            decl->decl_type = p->type;
            decl->ident = p->label;
            list_add(args, decl);
            p = next_node(p);
        }       
    }

    hashmap_value_t *value = create_hashmap_value(return_type, NT_FUNCTION, 0, args);
    hashmap_put(current_scope, ident, value);
}

void ident_var_use(char *ident) {

}

void ident_vector_use(char *ident) {

}

void ident_fun_use(char *ident, node *params) {

}

void ident_var_set(char *ident, node *value) {

}

void ident_vector_set(char *ident, node *index, node *value) {

}

enum data_type infer_expression_type(node *root) {

}

void print_data_type(enum data_type type) {
    if (type == DT_BOOL) printf("bool");
    else if (type == DT_CHAR) printf("char");
    else if (type == DT_FLOAT) printf("float");
    else if (type == DT_INTEGER) printf("int");
    else if (type == DT_STRING) printf("string");
}

void hashmap_print(hashmap_t *map) {
    int fold = 0;
    int index = 0;
    printf("hashmap %p {\n", map);
    if (map != NULL) {
        while (fold < map->size) {
            hashmap_entry_t *entry = map->values[index++];
            if (entry != NULL) {
                printf("\t[%s] ", entry->key);
                hashmap_value_t *value = entry->value;
                if (value->nature == NT_FUNCTION) {
                    printf("FUNCTION ");
                    list_print(value->args);
                    printf(" -> ");
                    print_data_type(value->type);
                } else if (value->nature == NT_VARIABLE) {
                    printf("VAR ");
                    print_data_type(value->type);
                } else if (value->nature == NT_VECTOR) {
                    printf("ARRAY ");
                    print_data_type(value->type);
                    printf("[%d]", value->men_size/size_data_type(value->type));
                }
                printf("\n");
                fold++;
            }
        }
    }
    printf("}\n");
}

void print_stack() {
    stack_entry_t *entry;
    if (scope_stack != NULL) {
        while (!stack_is_empty(scope_stack)) {
            entry = stack_pop(scope_stack);
            hashmap_print(entry);
        }
    }
}
