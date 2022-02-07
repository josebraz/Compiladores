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
    statement statement_list | 
    statement;

statement:
    local_decl; // todo: adicionar os outros comandos

local_decl:
    TK_PR_STATIC type local_decl_list ';' |
    TK_PR_CONST type local_decl_list ';' |
    TK_PR_STATIC TK_PR_CONST type local_decl_list ';' |
    type local_decl_list ';';

local_decl_list:
    TK_IDENTIFICADOR ',' local_decl_list | 
    TK_IDENTIFICADOR TK_OC_LE literal ',' local_decl_list | 
    TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR ',' local_decl_list | 
    TK_IDENTIFICADOR TK_OC_LE literal |
    TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR |
    TK_IDENTIFICADOR;

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
