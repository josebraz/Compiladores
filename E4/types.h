/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

#ifndef TYPES_H
#define TYPES_H

enum node_type {
    STMT_T = 0,             // Nodo do tipo comando simples
    EXPRES_T = 1,           // Nodo do tipo expressão
    LITERAL_T = 2,          // Nodo do tipo literal (folha)
    ARRAY_T = 3,            // Node do tipo array
    BLOCK_START_MARK_T = 4, // Marcador de início de bloco/lista
    BLOCK_END_MARK_T = 5    // Marcador de final de bloco/lista
};

/**
 * Estrutura do nodo da nossa ASP
 * 
 */
typedef struct node {
    char *label;         // Identificadore do nodo (ver sessão 2.4)
    void *value;         // Ponteiro para o valor (quando for folha)
    int size;            // Quantidade de filhos que o nodo tem
    enum node_type type; // Tipo do nodo
    struct node **nodes; // Lista de nodos filhos (pode ser NULL)
} node; 

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
 * Tipo customizado para ser usado no lex
 * 
 */
typedef struct YYSTYPE {
     int line;             // Linha do lexema
     enum TOKEN_TYPE type; // Tipo do token
     node* node;
     union valor_lexico {  // Valor do lexema como union
        char* string;
        char character;
        int boolean;
        int integer;
        float real;
    } valor_lexico;
} YYSTYPE;


#endif
