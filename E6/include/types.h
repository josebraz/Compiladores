/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#ifndef TYPES_H
#define TYPES_H

#include "stdlib.h"

#define HASHMAP_KEY_SIZE 128

enum op_type {
    OT_DISABLED = 0,
    OT_REG      = 1,
    OT_IMED     = 2,
    OT_IND      = 3,
    OT_LABEL    = 4,
    OT_MARK     = 5
};

typedef struct __instruction {
    char code[10];
    char comment[100];
    char mark_property[100]; // Para guardar informações adicionais da marcação
    int lazy; // indica se pode ser colocar na lista de instruções depois
    int reg_result;
    enum op_type op1_type;
    int op1;
    enum op_type op2_type;
    int op2;
    enum op_type op3_type;
    int op3;
} instruction_t;

typedef struct instruction_entry_t {
    struct instruction_entry_t *next;
    struct instruction_entry_t *previous;
    instruction_t *entry;
} instruction_entry_t;

enum node_mark {
    STMT_T = 0,             // Nodo do tipo comando simples
    EXPRES_T = 1,           // Nodo do tipo expressão
    LITERAL_T = 2,          // Nodo do tipo literal (folha)
    ARRAY_T = 3,            // Node do tipo array
    VAR_T = 4,
    DECL_VAR_INIT_T = 5,
    DECL_VAR_T = 6,
    FUN_CALL_T = 7
};

enum data_type {
    DT_UNKNOWN  = -1,
    DT_INTEGER  = 0,
    DT_FLOAT    = 1,
    DT_STRING   = 2,
    DT_BOOL     = 3,
    DT_CHAR     = 4
};

enum nature_type {
    NT_LITERAL  = 0,
    NT_VARIABLE = 1,
    NT_VECTOR   = 2,
    NT_FUNCTION = 3
};

enum TOKEN_TYPE {
    INTEGER_T   = 0,
    FLOAT_T     = 1,
    STRING_T    = 2,
    BOOL_T      = 3,
    CHAR_T      = 4,
    SPEC_CHAR_T = 5,
    COMP_OPER_T = 6,
    IDENT_T     = 7
};

typedef struct bool_list {
    int *label_pointer;
    struct bool_list *next;
} bool_list;

/**
 * Estrutura do nodo da nossa ASP
 * 
 */
typedef struct node {
    char *label;         // Identificadore do nodo (ver sessão 2.4)
    void *value;         // Ponteiro para o valor (quando for folha)
    int size;            // Quantidade de filhos que o nodo tem
    enum node_mark mark; // Marcação do nodo, para controles da criação da AST
    enum data_type type; // O tipo do dado
    struct node **nodes; // Lista de nodos filhos (pode ser NULL)
    struct node *next;   // representa o próximo nodo da lista
    // Parte da geração de código
    instruction_entry_t *code;
    int reg_result;
    bool_list *true_list;
    bool_list *false_list;
} node; 

typedef struct __declaration_type {
    enum data_type decl_type;  // o tipo que o usuário informou
    char *ident;
    int is_const;
    int is_static;
} declaration_type_t;

/**
 * Tipo customizado para ser usado no lex
 * 
 */
typedef struct YYSTYPE {
     int line;             // Linha do lexema
     enum TOKEN_TYPE type; // Tipo do token
     node* node;
     enum data_type dt_type;
     union valor_lexico {  // Valor do lexema como union
        char* string;
        char character;
        int boolean;
        int integer;
        float real;
    } valor_lexico;
} YYSTYPE;

typedef declaration_type_t list_entry_t;

typedef struct __list
{
    int size;
    int actual_capacity;  // Capacidade atual da pilha
    list_entry_t **entries;  // Ponteiro para as entradas da pilha
} list_t;

typedef struct __hashmap_value {
    int line;
    enum data_type type;
    enum nature_type nature;
    int men_size;            // quanto a variável ocupa, para funções é a memória de todas as variáveis
    int men_offset;
    list_t *args;
    int fun_label;
} hashmap_value_t;

typedef struct __hashmap_entry {
    char key[HASHMAP_KEY_SIZE];
    hashmap_value_t *value;
} hashmap_entry_t;

typedef struct __hashmap {
    int size;
    int actual_capacity;
    hashmap_entry_t **values;
    char *label;  // um identificador do escopo
    int offset;   // deslocamento do registrador do escopo (rfp ou rbss)
} hashmap_t;

typedef hashmap_t stack_entry_t;

typedef struct __stack
{
    int index;               // Indice atual da pilha, -1 é vazia
    size_t actual_capacity;  // Capacidade atual da pilha
    stack_entry_t **entries; // Ponteiro para as entradas da pilha
} stack_t;

#endif
