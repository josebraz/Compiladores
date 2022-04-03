/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

#ifndef TYPES_H
#define TYPES_H

#include "stdlib.h"

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
    int men_size;
    list_t *args;
    // void *value;
} hashmap_value_t;

typedef struct __hashmap_entry {
    char key[20];
    hashmap_value_t *value;
} hashmap_entry_t;

typedef struct __hashmap {
    int size;
    int actual_capacity;
    hashmap_entry_t **values;
    char *label;  // um identificador do escopo
} hashmap_t;

typedef hashmap_t stack_entry_t;

typedef struct __stack
{
    int index;               // Indice atual da pilha, -1 é vazia
    size_t actual_capacity;  // Capacidade atual da pilha
    stack_entry_t **entries; // Ponteiro para as entradas da pilha
} stack_t;


#endif
