/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

%option yylineno
%{

  #include "parser.tab.h"
  // Para compilar o analisador
  // $ flex scanner.l
  // vai gerar o arquivos lex.yy.c
  // Agora podemos buildar o programa com a nossa main e linkando o lex
  // $ gcc lex.yy.c main.c -o analisador.out -lfl
  // Agora é só executar e correr pro abraço
  // $ ./analisador < teste.c

  int get_line_number (void) {
    return yylineno;
  }
%}

DIGIT [0-9]
ID [a-zA-Z_]+[a-zA-Z0-9_]*
INT {DIGIT}+
FLOAT {INT}\.{DIGIT}+([E|e][+|-]?{INT})?
CHAR ['].[']
STRING ["].*["]
COMMENT ((\/\/.*)|(\/\*[^(\*\/)]*\*\/))|(\/\*)|(\*\/)

%%

  /* 1. Palavras Reservadas */
"int"       { return TK_PR_INT; }
"float"     { return TK_PR_FLOAT; }
"bool"      { return TK_PR_BOOL; }
"char"      { return TK_PR_CHAR; }
"string"    { return TK_PR_STRING; }
"if"        { return TK_PR_IF; }
"then"      { return TK_PR_THEN; }
"else"      { return TK_PR_ELSE; }
"while"     { return TK_PR_WHILE; }
"do"        { return TK_PR_DO; }
"input"     { return TK_PR_INPUT; }
"output"    { return TK_PR_OUTPUT; }
"return"    { return TK_PR_RETURN; }
"const"     { return TK_PR_CONST; }
"static"    { return TK_PR_STATIC; }
"foreach"   { return TK_PR_FOREACH; }
"for"       { return TK_PR_FOR; }
"switch"    { return TK_PR_SWITCH; }
"case"      { return TK_PR_CASE; }
"break"     { return TK_PR_BREAK; }
"continue"  { return TK_PR_CONTINUE; }
"class"     { return TK_PR_CLASS; }
"private"   { return TK_PR_PRIVATE; }
"public"    { return TK_PR_PUBLIC; }
"protected" { return TK_PR_PROTECTED; }
"end"       { return TK_PR_END; }
"default"   { return TK_PR_DEFAULT; }

  /* 2. Caracteres Especiais */
"," { return yytext[0]; }
";" { return yytext[0]; }
":" { return yytext[0]; } 
"(" { return yytext[0]; } 
")" { return yytext[0]; } 
"[" { return yytext[0]; } 
"]" { return yytext[0]; } 
"{" { return yytext[0]; }
"}" { return yytext[0]; }
"+" { return yytext[0]; }
"-" { return yytext[0]; }
"|" { return yytext[0]; }
"*" { return yytext[0]; }
"/" { return yytext[0]; }
"<" { return yytext[0]; }
">" { return yytext[0]; }
"=" { return yytext[0]; }
"!" { return yytext[0]; }
"&" { return yytext[0]; }
"%" { return yytext[0]; }
"#" { return yytext[0]; }
"^" { return yytext[0]; }
"." { return yytext[0]; }
"$" { return yytext[0]; }

  /* 3. Operadores Compostos */
"<=" { return TK_OC_LE; }
">=" { return TK_OC_GE; }
"==" { return TK_OC_EQ; }
"!=" { return TK_OC_NE; }
"&&" { return TK_OC_AND; }
"||" { return TK_OC_OR; }
">>" { return TK_OC_SL; }
"<<" { return TK_OC_SR; }

  /* literais bool */
"false" { return TK_LIT_FALSE; }
"true"  { return TK_LIT_TRUE; }

  /* 4. Identificadores */
{ID} { return TK_IDENTIFICADOR; }

  /* 5. Literais */
{INT}     { return TK_LIT_INT; }
{FLOAT}   { return TK_LIT_FLOAT; }
{STRING}  { return TK_LIT_STRING; }
{CHAR}    { return TK_LIT_CHAR; }

  /* Captar caracteres irrelevantes para a linguagem */
[ \t\n]+ { }
{COMMENT} { }

  /* Captar erros, se não bateu nenhum token acima */
.               { return TOKEN_ERRO; }
\'(.)*\'        { return TOKEN_ERRO; }
