%{
  #include <stdio.h>
  
  int get_line_number (void);
  int yylex(void);
  void yyerror (char const *s);
%}

%define parse.error verbose

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
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%start prog

%%

prog : 
    global_decl prog | 
    function prog | 
    global_decl | 
    function;

global_decl : 
    TK_PR_STATIC type global_decl_list ';' |
    type global_decl_list ';';

global_decl_list : 
    TK_IDENTIFICADOR ',' global_decl_list | 
    TK_IDENTIFICADOR '[' TK_LIT_INT ']' ',' global_decl_list | 
    TK_IDENTIFICADOR |
    TK_IDENTIFICADOR '[' TK_LIT_INT ']';
            
function: 
    function_header function_body;

function_header: 
    type TK_IDENTIFICADOR function_params |
    TK_PR_STATIC type TK_IDENTIFICADOR function_params;
          
function_params: 
    '(' ')' | 
    '(' function_params_list ')';

function_params_list: 
    type TK_IDENTIFICADOR ',' function_params_list |
    TK_PR_CONST type TK_IDENTIFICADOR ',' function_params_list |
    type TK_IDENTIFICADOR |
    TK_PR_CONST type TK_IDENTIFICADOR;  

function_body: statement_block;

statement_block:
    '{' '}' |
    '{' statement_list '}';
    
statement_list:
    statement ';' statement_list | 
    statement ';';

statement:
    local_decl |
    assignment |
    in_out |
    function_call |
    shift |
    TK_PR_RETURN expression |
    TK_PR_BREAK |
    TK_PR_CONTINUE |
    control_flow;

local_decl:
    TK_PR_STATIC type local_decl_list |
    TK_PR_CONST type local_decl_list |
    TK_PR_STATIC TK_PR_CONST type local_decl_list |
    type local_decl_list;

local_decl_list:
    TK_IDENTIFICADOR ',' local_decl_list | 
    TK_IDENTIFICADOR TK_OC_LE literal ',' local_decl_list | 
    TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR ',' local_decl_list | 
    TK_IDENTIFICADOR TK_OC_LE literal |
    TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR |
    TK_IDENTIFICADOR;

assignment:
    TK_IDENTIFICADOR '=' expression |
    TK_IDENTIFICADOR '[' expression ']' '=' expression;
    
in_out:
    TK_PR_INPUT TK_IDENTIFICADOR |
    TK_PR_OUTPUT TK_IDENTIFICADOR |
    TK_PR_OUTPUT literal;

function_call:
    TK_IDENTIFICADOR '(' ')' |
    TK_IDENTIFICADOR '(' function_call_list ')';

function_call_list:
    expression ',' function_call_list |
    expression;

shift:
    TK_IDENTIFICADOR TK_OC_SL TK_LIT_INT |
    TK_IDENTIFICADOR '[' expression ']' TK_OC_SL TK_LIT_INT |
    TK_IDENTIFICADOR TK_OC_SR TK_LIT_INT |
    TK_IDENTIFICADOR '[' expression ']' TK_OC_SR TK_LIT_INT;

control_if:
    TK_PR_IF '(' expression ')' statement_block |
    TK_PR_IF '(' expression ')' statement_block TK_PR_ELSE statement_block;
    
control_for:
    TK_PR_FOR '(' assignment ':' expression ':' assignment ')' statement_block;
    
control_while:
    TK_PR_WHILE '(' expression ')' TK_PR_DO statement_block;

control_flow:
    control_if |
    control_for |
    control_while;

expression:
    logic_expr |
    arith_expr;

arith_expr:
    '(' arith_expr ')' |
    arith_unary_operator arith_expr |
    arith_expr arith_binary_operator arith_expr |
    arith_operands;
    
arith_unary_operator:
    '+' | '-' | '&' | '*' | '?' | '#';
    
arith_binary_operator:
    '+' | '-' | '*' | '/' | '%' | '|' | '&' | '^';

arith_operands:
    TK_IDENTIFICADOR |
    TK_IDENTIFICADOR '[' TK_LIT_INT ']' |
    TK_LIT_INT |
    TK_LIT_FLOAT |
    function_call;

logic_expr:
    '(' logic_expr ')' |
    arith_expr relational_binary_operator arith_expr |
    logic_expr logic_binary_operator logic_expr |
    '!' logic_expr | 
    TK_LIT_FALSE | 
    TK_LIT_TRUE;

relational_binary_operator:
    TK_OC_LE | TK_OC_GE | TK_OC_EQ | TK_OC_NE;

logic_binary_operator:
    TK_OC_AND | TK_OC_OR;

literal: 
    TK_LIT_INT |
    TK_LIT_FLOAT |
    TK_LIT_FALSE |
    TK_LIT_TRUE |
    TK_LIT_CHAR |
    TK_LIT_STRING;
      
type: 
    TK_PR_INT | 
    TK_PR_FLOAT | 
    TK_PR_BOOL | 
    TK_PR_CHAR | 
    TK_PR_STRING;

%%

void yyerror(char const *s) {
  printf("ERROR:\n\tline: %d\n\tmessage: %s\n", get_line_number(), s);
}
