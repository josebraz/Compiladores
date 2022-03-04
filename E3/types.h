#ifndef TYPES_H
#define TYPES_H

#include "asp.h"

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

typedef struct YYSTYPE {
     int line;
     enum TOKEN_TYPE type;
     union valor_lexico {
        char* string;
        char character;
        int boolean;
        int integer;
        float real;
        node* node;
    } valor_lexico;
} YYSTYPE;


#endif
