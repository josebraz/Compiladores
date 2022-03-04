/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "asp.h"
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

%type<valor_lexico.node> operand
%type<valor_lexico.node> function_call 
%type<valor_lexico.node> literal 
%type<valor_lexico.node> prog 
%type<valor_lexico.node> function_body
%type<valor_lexico.node> statement_list
%type<valor_lexico.node> statement
%type<valor_lexico.node> statement_block
%type<valor_lexico.node> assignment
%type<valor_lexico.node> local_decl
%type<valor_lexico.node> local_decl_list

%type<valor_lexico.node> expression
%type<valor_lexico.node> expression10
%type<valor_lexico.node> expression9
%type<valor_lexico.node> expression8
%type<valor_lexico.node> expression7
%type<valor_lexico.node> expression6
%type<valor_lexico.node> expression5
%type<valor_lexico.node> expression4
%type<valor_lexico.node> expression3
%type<valor_lexico.node> expression2
%type<valor_lexico.node> expression1
%type<valor_lexico.node> expression0

%start s

%%

s : prog { arvore = $1; } ;

// O programa é um conjunto de declarações globais e
// declarações de funções, também é aceito uma linguagem vazia 
prog : 
    global_decl prog { $$ = $2; }
  | type TK_IDENTIFICADOR function_params function_body prog { $$ = create_node($2, 2, $4, $5); }       
  | TK_PR_STATIC type TK_IDENTIFICADOR function_params function_body prog { $$ = create_node($3, 2, $5, $6); }   
  | { $$ = NULL; };

// Declaração de variáveis globais
global_decl : 
    TK_PR_STATIC type global_decl_list ';'
  | type global_decl_list ';';

global_decl_list : 
    TK_IDENTIFICADOR ',' global_decl_list
  | TK_IDENTIFICADOR '[' TK_LIT_INT ']' ',' global_decl_list
  | TK_IDENTIFICADOR
  | TK_IDENTIFICADOR '[' TK_LIT_INT ']';

// Declaração das funções        
function_params: 
    '(' ')'
  | '(' function_params_list ')';

function_params_list: 
    type TK_IDENTIFICADOR ',' function_params_list
  | TK_PR_CONST type TK_IDENTIFICADOR ',' function_params_list
  | type TK_IDENTIFICADOR
  | TK_PR_CONST type TK_IDENTIFICADOR;  

function_body: statement_block;

// Lista de comandos da linguagem
statement_block:
    '{' '}' { $$ = NULL; }
  | '{' statement_list '}' { $$ = $2; } ;
    
statement_list:
    statement statement_list { 
        if ($1 != NULL) {
            $$ = $1; add_child($1, $2);
        } else {
            $$ = $2;
        }
    } 
  | statement;

statement:
    statement_block
  | assignment ';'
  | local_decl ';';
//   | in_out ';'
//   | function_call ';' 
//   | shift ';'
//   | TK_PR_RETURN expression ';'
//   | TK_PR_BREAK ';'
//   | TK_PR_CONTINUE ';'
//   | control_flow;


// Declaração de variáveis locais
local_decl:
    TK_PR_STATIC type local_decl_list { $$ = $3; }
  | TK_PR_CONST type local_decl_list { $$ = $3; }
  | TK_PR_STATIC TK_PR_CONST type local_decl_list { $$ = $4; }
  | type local_decl_list { $$ = $2; };

local_decl_list:
    TK_IDENTIFICADOR ',' local_decl_list { $$ = $3; }
  | TK_IDENTIFICADOR { $$ = NULL; }
  | TK_IDENTIFICADOR TK_OC_LE literal ',' local_decl_list { 
        node *id_node = create_leaf_id($1); 
        $$ = create_node("<=", 3, id_node, $3, $5); 
    } 
  | TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR ',' local_decl_list { 
        node *dest_node = create_leaf_id($1); 
        node *source_node = create_leaf_id($3); 
        $$ = create_node("<=", 3, dest_node, source_node, $5); 
    } 
  | TK_IDENTIFICADOR TK_OC_LE literal { 
        node *id_node = create_leaf_id($1); 
        $$ = create_node("<=", 2, id_node, $3); 
    } 
  | TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR { 
        node *dest_node = create_leaf_id($1); 
        node *source_node = create_leaf_id($3); 
        $$ = create_node("<=", 2, dest_node, source_node);  
    } ;


// Comando de atribuição (depois de declarar)
assignment:
    TK_IDENTIFICADOR '=' expression { 
        node *id_node = create_leaf_id($1); 
        $$ = create_node("=", 2, id_node, $3); 
    } 
  | TK_IDENTIFICADOR '[' expression ']' '=' expression { 
        node *id_node = create_leaf_id($1); 
        node *index_node = create_node("[]", 2, id_node, $3);
        $$ = create_node("=", 2, index_node, $6); 
    } ;


// Operadores de entrada e saída    
in_out:
    TK_PR_INPUT TK_IDENTIFICADOR
  | TK_PR_OUTPUT TK_IDENTIFICADOR
  | TK_PR_OUTPUT literal;


// Chamada de uma função com 0 ou mais argumentos sepados por vígula
function_call:
    TK_IDENTIFICADOR '(' ')' {
        char *f_name = strdup($1);
        char *label = "call ";
        $$ = create_leaf_fun_call($1, strcat(label, f_name)); 
    }
  | TK_IDENTIFICADOR '(' function_call_list ')' {
        char *f_name = strdup($1);
        char *label = "call ";
        $$ = create_leaf_fun_call($1, strcat(label, f_name)); 
    };

function_call_list:
    expression ',' function_call_list
  | expression;


// Operador de shift com suporte a lista
shift:
    TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT 
  | TK_IDENTIFICADOR '[' expression ']' TK_OC_SL TK_LIT_INT
  | TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT
  | TK_IDENTIFICADOR '[' expression ']' TK_OC_SR TK_LIT_INT;


// Controle de fluxo, loop for, while e if
control_flow:
    control_if 
  | control_for 
  | control_while;

control_if:
    TK_PR_IF '(' expression ')' statement_block
  | TK_PR_IF '(' expression ')' statement_block TK_PR_ELSE statement_block;

control_for:
    TK_PR_FOR '(' assignment ':' expression ':' assignment ')' statement_block;    

control_while:
    TK_PR_WHILE '(' expression ')' TK_PR_DO statement_block;


// Expressões Aritméticas e Lógicas
// Quanto mais "profundo" na estrutura das expressões da gramática
// maior será a precedencia da produção
// A associatividade é construída com a forma que é feito a recursão
expression:
    expression10 '?' expression10 ':' expression10 { $$ = create_node("?:", 3, $1, $3, $5); } 
  | expression10;
    
expression10:
    expression10 TK_OC_OR expression9 { $$ = create_node("||", 2, $1, $3); } 
  | expression9;

expression9:
    expression9 TK_OC_AND expression8 { $$ = create_node("&&", 2, $1, $3); } 
  | expression8;

expression8:
    expression8 '|' expression7 { $$ = create_node("|", 2, $1, $3); } 
  | expression7;

expression7:
    expression7 '&' expression6 { $$ = create_node("&", 2, $1, $3); } 
  | expression6;

expression6:
    expression6 TK_OC_EQ expression5 { $$ = create_node("==", 2, $1, $3); } 
  | expression6 TK_OC_NE expression5 { $$ = create_node("!=", 2, $1, $3); } 
  | expression5;

expression5:
    expression5 '<' expression4 { $$ = create_node("<", 2, $1, $3); } 
  | expression5 '>' expression4 { $$ = create_node(">", 2, $1, $3); } 
  | expression5 TK_OC_LE expression4 { $$ = create_node("<=", 2, $1, $3); } 
  | expression5 TK_OC_GE expression4 { $$ = create_node(">=", 2, $1, $3); } 
  | expression4;

expression4:
    expression4 '+' expression3 { $$ = create_node("+", 2, $1, $3); } 
  | expression4 '-' expression3 { $$ = create_node("-", 2, $1, $3); } 
  | expression3;
    
expression3:
    expression3 '*' expression2 { $$ = create_node("*", 2, $1, $3); } 
  | expression3 '/' expression2 { $$ = create_node("/", 2, $1, $3); } 
  | expression3 '%' expression2 { $$ = create_node("%", 2, $1, $3); } 
  | expression2;
    
expression2:
    expression2 '^' expression1 { $$ = create_node("^", 2, $1, $3); } 
  | expression1;

expression1:
    '+' expression0 { $$ = create_node_unary_ope("+", $2); } 
  | '-' expression0 { $$ = create_node_unary_ope("-", $2); } 
  | '?' expression0 { $$ = create_node_unary_ope("?", $2); } 
  | '!' expression0 { $$ = create_node_unary_ope("!", $2); } 
  | '&' expression0 { $$ = create_node_unary_ope("&", $2); } 
  | '*' expression0 { $$ = create_node_unary_ope("*", $2); } 
  | '#' expression0 { $$ = create_node_unary_ope("#", $2); } 
  | expression0;

expression0:
    '(' expression ')' { $$ = $2; }
  | operand;


// Operandos da linguagem com suporte a array    
operand:
    TK_IDENTIFICADOR { $$ = create_leaf_id($1); } 
  | TK_LIT_INT { $$ = create_leaf_int($1); } 
  | TK_LIT_FLOAT { $$ = create_leaf_float($1); } 
  | TK_LIT_FALSE { $$ = create_leaf_bool($1, "false"); } 
  | TK_LIT_TRUE { $$ = create_leaf_bool($1, "true"); } 
  | function_call
  | TK_IDENTIFICADOR '[' TK_LIT_INT ']' { $$ = create_node_id_array($1, create_leaf_int($3)); } ;


// Literais da linguagem
literal: 
    TK_LIT_INT { $$ = create_leaf_int($1); } 
  | TK_LIT_FLOAT { $$ = create_leaf_float($1); } 
  | TK_LIT_FALSE { $$ = create_leaf_bool($1, "false"); } 
  | TK_LIT_TRUE { $$ = create_leaf_bool($1, "true"); } 
  | TK_LIT_CHAR { $$ = create_leaf_char($1); } 
  | TK_LIT_STRING { $$ = create_leaf_string($1, $1); } ;


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
