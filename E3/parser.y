/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "asp.h"
  #include "util.h"
  #include "types.h"
  
  #define YYDEBUG 1
  
  extern void *arvore;
  
  int get_line_number (void);
  int yylex(void);
  void yyerror (char const *s);
%}

%define api.value.type {struct YYSTYPE}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_PR_END
%token TK_PR_DEFAULT
%token TOKEN_ERRO

%token<valor_lexico.string> TK_OC_LE
%token<valor_lexico.string> TK_OC_GE
%token<valor_lexico.string> TK_OC_EQ
%token<valor_lexico.string> TK_OC_NE
%token<valor_lexico.string> TK_OC_AND
%token<valor_lexico.string> TK_OC_OR
%token<valor_lexico.string> TK_OC_SL
%token<valor_lexico.string> TK_OC_SR

%token<valor_lexico.integer> TK_LIT_INT
%token<valor_lexico.real> TK_LIT_FLOAT
%token<valor_lexico.boolean> TK_LIT_FALSE
%token<valor_lexico.boolean> TK_LIT_TRUE
%token<valor_lexico.character> TK_LIT_CHAR
%token<valor_lexico.string> TK_LIT_STRING
%token<valor_lexico.string> TK_IDENTIFICADOR

%type<node> operand
%type<node> function_call 
%type<node> function_call_list
%type<node> literal 
%type<node> prog 
%type<node> function_body
%type<node> statement_list
%type<node> statement
%type<node> statement_block
%type<node> assignment
%type<node> local_decl
%type<node> local_decl_list
%type<node> in_out
%type<node> shift
%type<node> control_flow
%type<node> control_if
%type<node> control_for
%type<node> control_while
%type<node> control_jump

%type<node> expression
%type<node> expression10
%type<node> expression9
%type<node> expression8
%type<node> expression7
%type<node> expression6
%type<node> expression5
%type<node> expression4
%type<node> expression3
%type<node> expression2
%type<node> expression1
%type<node> expression0

%start s

%%

// Única entrada, para setar a arvore
s : prog { arvore = $1; } ;

// O programa é um conjunto de declarações globais e
// declarações de funções, também é aceito uma linguagem vazia 
prog : 
    global_decl prog { $$ = $2; }
  | type TK_IDENTIFICADOR function_params function_body prog { 
        $$ = create_node_function($2, $4, $5); 
    }       
  | TK_PR_STATIC type TK_IDENTIFICADOR function_params function_body prog { 
        $$ = create_node_function($3, $5, $6); 
    }   
  | { $$ = NULL; };

// Declaração de variáveis globais
global_decl : 
    TK_PR_STATIC type global_decl_list ';'
  | type global_decl_list ';';

global_decl_list : 
    TK_IDENTIFICADOR ',' global_decl_list { free($1); } 
  | TK_IDENTIFICADOR '[' TK_LIT_INT ']' ',' global_decl_list { free($1); } 
  | TK_IDENTIFICADOR { free($1); } 
  | TK_IDENTIFICADOR '[' TK_LIT_INT ']' { free($1); };

// Declaração das funções        
function_params: 
    '(' ')'
  | '(' function_params_list ')';

function_params_list: 
    type TK_IDENTIFICADOR ',' function_params_list { free($2); }
  | TK_PR_CONST type TK_IDENTIFICADOR ',' function_params_list { free($3); }
  | type TK_IDENTIFICADOR { free($2); }
  | TK_PR_CONST type TK_IDENTIFICADOR { free($3); };  

function_body: statement_block { asp_scope_clear(); };

// Lista de comandos da linguagem
statement_block:
    '{' '}' { $$ = NULL; }
  | '{' statement_list '}' { 
        $$ = $2;
        if ($$ != NULL) {
          asp_scope_completed($$);
        }
  };
    
statement_list:
    statement statement_list { 
        if ($2->type == DECL_T) {
          $$ = asp_list_complete($1, $2);
        } else {
          $$ = asp_stmt_list($1, $2); 
        }
    } 
  | statement {
        $$ = $1;
        if ($$ != NULL) {
          asp_scope_end($$);
        }
    };

// Todos os comandos simples da linguagem
statement:
    statement_block ';'
  | assignment ';'
  | local_decl ';'
  | in_out ';'
  | function_call ';'
  | shift ';'
  | control_jump ';'
  | control_flow ';';

// Declaração de variáveis locais
local_decl:
    TK_PR_STATIC type local_decl_list { $$ = $3; }
  | TK_PR_CONST type local_decl_list { $$ = $3; }
  | TK_PR_STATIC TK_PR_CONST type local_decl_list { $$ = $4; }
  | type local_decl_list { $$ = $2; } ;

local_decl_list:
    TK_IDENTIFICADOR ',' local_decl_list { $$ = $3; free($1); }
  | TK_IDENTIFICADOR { $$ = NULL; free($1); }
  | TK_IDENTIFICADOR TK_OC_LE literal ',' local_decl_list { 
        free($2);
        node *id_node = create_leaf_id($1); 
        if ($5 == NULL) {
            $$ = create_node("<=", DECL_T, 2, id_node, $3); 
            asp_last_list_item($$);
        } else {
            $$ = create_node("<=", DECL_T, 3, id_node, $3, $5); 
        }
    } 
  | TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR ',' local_decl_list { 
        free($2);
        node *dest_node = create_leaf_id($1); 
        node *source_node = create_leaf_id($3); 
        if ($5 == NULL) {
            $$ = create_node("<=", DECL_T, 2, dest_node, source_node); 
            asp_last_list_item($$);
        } else {
            $$ = create_node("<=", DECL_T, 3, dest_node, source_node, $5); 
        }
    } 
  | TK_IDENTIFICADOR TK_OC_LE literal { 
        free($2);
        node *id_node = create_leaf_id($1); 
        $$ = create_node("<=", DECL_T, 2, id_node, $3); 
        asp_last_list_item($$);
    } 
  | TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR { 
        free($2);
        node *dest_node = create_leaf_id($1); 
        node *source_node = create_leaf_id($3); 
        $$ = create_node("<=", DECL_T, 2, dest_node, source_node);  
        asp_last_list_item($$);
    };

// Comando de atribuição (depois de declarar)
assignment:
    TK_IDENTIFICADOR '=' expression { 
        node *id_node = create_leaf_id($1); 
        $$ = create_node("=", STMT_T, 2, id_node, $3); 
    } 
  | TK_IDENTIFICADOR '[' expression ']' '=' expression { 
        node *id_node = create_leaf_id($1); 
        node *index_node = create_node("[]", ARRAY_T, 2, id_node, $3);
        $$ = create_node("=", STMT_T, 2, index_node, $6); 
    } ;

// Operadores de entrada e saída    
in_out:
    TK_PR_INPUT TK_IDENTIFICADOR { 
        node *id_node = create_leaf_id($2);
        $$ = create_node("input", STMT_T, 1, id_node); 
    }
  | TK_PR_OUTPUT TK_IDENTIFICADOR { 
        node *id_node = create_leaf_id($2);
        $$ = create_node("output", STMT_T, 1, id_node); 
    }
  | TK_PR_OUTPUT literal {  $$ = create_node("output", STMT_T, 1, $2);  };

// Chamada de uma função com 0 ou mais argumentos sepados por vígula
function_call:
    TK_IDENTIFICADOR '(' ')' { $$ = create_leaf_fun_call($1, NULL); }
  | TK_IDENTIFICADOR '(' function_call_list ')' { 
        $$ = create_leaf_fun_call($1, $3); 
    };

function_call_list:
    expression ',' function_call_list { $$ = add_child($1, $3); }
  | expression { $$ = $1; } ;

// Operador de shift com suporte a lista
shift:
    TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT {
        node *id_node = create_leaf_id($1);
        node *offset = create_leaf_int($3);
        $$ = create_node(">>", STMT_T, 2, id_node, offset); 
        free($2);
    }
  | TK_IDENTIFICADOR '[' expression ']' TK_OC_SL TK_LIT_INT {
        node *id_node = create_leaf_id($1); 
        node *index_node = create_node("[]", ARRAY_T, 2, id_node, $3);
        node *offset = create_leaf_int($6);
        $$ = create_node(">>", STMT_T, 2, index_node, offset); 
        free($5);
  }
  | TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT {
        node *id_node = create_leaf_id($1);
        node *offset = create_leaf_int($3);
        $$ = create_node("<<", STMT_T, 2, id_node, offset); 
        free($2);
    }
  | TK_IDENTIFICADOR '[' expression ']' TK_OC_SR TK_LIT_INT {
        node *id_node = create_leaf_id($1); 
        node *index_node = create_node("[]", ARRAY_T, 2, id_node, $3);
        node *offset = create_leaf_int($6);
        $$ = create_node("<<", STMT_T, 2, index_node, offset); 
        free($5);
  };


// Controle de fluxo, loop for, while e if
control_flow:
    control_if 
  | control_for 
  | control_while;

control_if:
    TK_PR_IF '(' expression ')' statement_block {
        $$ = create_node("if", STMT_T, 2, $3, $5); 
    }
  | TK_PR_IF '(' expression ')' statement_block TK_PR_ELSE statement_block {
        $$ = create_node("if", STMT_T, 3, $3, $5, $7); 
    };

control_for:
    TK_PR_FOR '(' assignment ':' expression ':' assignment ')' statement_block {
        $$ = create_node("for", STMT_T, 4, $3, $5, $7, $9); 
    };    

control_while:
    TK_PR_WHILE '(' expression ')' TK_PR_DO statement_block {
        $$ = create_node("while", STMT_T, 2, $3, $6); 
    };

control_jump:
    TK_PR_RETURN expression { $$ = create_node("return", STMT_T, 1, $2); }
  | TK_PR_BREAK { $$ = create_node("break", STMT_T, 0); }
  | TK_PR_CONTINUE { $$ = create_node("continue", STMT_T, 0); }

// Expressões Aritméticas e Lógicas
// Quanto mais "profundo" na estrutura das expressões da gramática
// maior será a precedencia da produção
// A associatividade é construída com a forma que é feito a recursão
expression:
    expression10 '?' expression10 ':' expression10 { $$ = create_node_ternary_ope("?:", $1, $3, $5); } 
  | expression10;
    
expression10:
    expression10 TK_OC_OR expression9 { $$ = create_node_binary_ope("||", $1, $3); free($2); } 
  | expression9;

expression9:
    expression9 TK_OC_AND expression8 { $$ = create_node_binary_ope("&&", $1, $3); free($2); } 
  | expression8;

expression8:
    expression8 '|' expression7 { $$ = create_node_binary_ope("|", $1, $3); } 
  | expression7;

expression7:
    expression7 '&' expression6 { $$ = create_node_binary_ope("&", $1, $3); } 
  | expression6;

expression6:
    expression6 TK_OC_EQ expression5 { $$ = create_node_binary_ope("==", $1, $3); free($2); } 
  | expression6 TK_OC_NE expression5 { $$ = create_node_binary_ope("!=", $1, $3); free($2); } 
  | expression5;

expression5:
    expression5 '<' expression4 { $$ = create_node_binary_ope("<", $1, $3); } 
  | expression5 '>' expression4 { $$ = create_node_binary_ope(">", $1, $3); } 
  | expression5 TK_OC_LE expression4 { $$ = create_node_binary_ope("<=", $1, $3); free($2); } 
  | expression5 TK_OC_GE expression4 { $$ = create_node_binary_ope(">=", $1, $3); free($2); } 
  | expression4;

expression4:
    expression4 '+' expression3 { $$ = create_node_binary_ope("+", $1, $3); } 
  | expression4 '-' expression3 { $$ = create_node_binary_ope("-", $1, $3); } 
  | expression3;
    
expression3:
    expression3 '*' expression2 { $$ = create_node_binary_ope("*", $1, $3); } 
  | expression3 '/' expression2 { $$ = create_node_binary_ope("/", $1, $3); } 
  | expression3 '%' expression2 { $$ = create_node_binary_ope("%", $1, $3); } 
  | expression2;
    
expression2:
    expression2 '^' expression1 { $$ = create_node_binary_ope("^", $1, $3); } 
  | expression1;

expression1:
    '+' expression1 { $$ = create_node_unary_ope("+", $2); } 
  | '-' expression1 { $$ = create_node_unary_ope("-", $2); } 
  | '?' expression1 { $$ = create_node_unary_ope("?", $2); } 
  | '!' expression1 { $$ = create_node_unary_ope("!", $2); } 
  | '&' expression1 { $$ = create_node_unary_ope("&", $2); } 
  | '*' expression1 { $$ = create_node_unary_ope("*", $2); } 
  | '#' expression1 { $$ = create_node_unary_ope("#", $2); } 
  | expression0;

expression0:
    '(' expression ')' { $$ = $2; }
  | operand;

// Operandos da linguagem com suporte a array    
operand:
    TK_IDENTIFICADOR { $$ = create_leaf_id($1); } 
  | TK_LIT_INT { $$ = create_leaf_int($1); } 
  | TK_LIT_FLOAT { $$ = create_leaf_float($1); } 
  | function_call
  | TK_IDENTIFICADOR '[' expression ']' { $$ = create_node_id_array($1, $3); } ;


// Literais da linguagem
literal: 
    TK_LIT_INT { $$ = create_leaf_int($1); } 
  | TK_LIT_FLOAT { $$ = create_leaf_float($1); } 
  | TK_LIT_FALSE { $$ = create_leaf_bool($1, "false"); } 
  | TK_LIT_TRUE { $$ = create_leaf_bool($1, "true"); } 
  | TK_LIT_CHAR { $$ = create_leaf_char($1); } 
  | TK_LIT_STRING { $$ = create_leaf_string($1); } ;


// Declaração de tipos      
type: 
    TK_PR_INT
  | TK_PR_FLOAT 
  | TK_PR_BOOL  
  | TK_PR_CHAR 
  | TK_PR_STRING ;

%%

// Função que é chamada pelo bison para imprimir algum 
// erro sintático da linguagem analisada
void yyerror(char const *s) {
  printf("ERROR:\n\tline: %d\n\tmessage: %s\n", get_line_number(), s);
}
