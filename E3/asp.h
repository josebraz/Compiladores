#ifndef ASP_H
#define ASP_H

#define INTEGER_T   0
#define FLOAT_T     1
#define STRING_T    2
#define BOOL_T      3
#define CHAR_T      4
#define SPEC_CHAR_T 5
#define OPER_COMP_T 6
#define IDENT_T     7

typedef struct YYSTYPE {
     int line;
     int type;
     union valor_lexico {
        char* string;
        char character;
        int boolean;
        int integer;
        float real;
    } valor_lexico;
} YYSTYPE;

typedef struct {
    char *label;
    void *value;
    int size;
    struct node **nodes;
} node; 


node* create_node(char *label, int nodes, ...);

node* create_leaf(void *value, char* label);

node* create_leaf_int(int value, char* label);

#endif
