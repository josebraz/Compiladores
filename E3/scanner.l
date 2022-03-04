/* autores: José Henrique da Silva Braz & Jeison Casonatti Caroly */

%option yylineno
%{

  #include "parser.tab.h"
  #include "types.h"
  #include <string.h>
  
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
  
  void composite_operators() {
    yylval.valor_lexico.string = strdup(yytext);
    yylval.line = get_line_number();
    yylval.type = COMP_OPER_T;
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
","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"|"|"*"|"/"|"<"|">"|"="|"!"|"&"|"%"|"#"|"^"|"."|"$"|"?" { 
    yylval.valor_lexico.string = strdup(yytext);
    yylval.line = get_line_number();
    yylval.type = SPEC_CHAR_T;
    return yytext[0]; 
}

  /* 3. Operadores Compostos */
"<=" { composite_operators(); return TK_OC_LE; }
">=" { composite_operators(); return TK_OC_GE; }
"==" { composite_operators(); return TK_OC_EQ; }
"!=" { composite_operators(); return TK_OC_NE; }
"&&" { composite_operators(); return TK_OC_AND; }
"||" { composite_operators(); return TK_OC_OR; }
">>" { composite_operators(); return TK_OC_SL; }
"<<" { composite_operators(); return TK_OC_SR; }

  /* literais bool */
"false" { 
    yylval.valor_lexico.boolean = 0;
    yylval.line = get_line_number();
    yylval.type = BOOL_T;
    return TK_LIT_FALSE; 
}
"true"  { 
    yylval.valor_lexico.boolean = 1;
    yylval.line = get_line_number();
    yylval.type = BOOL_T;
    return TK_LIT_TRUE; 
}

  /* 4. Identificadores */
{ID} { 
    yylval.valor_lexico.string = strdup(yytext);
    yylval.line = get_line_number();
    yylval.type = IDENT_T;
	return TK_IDENTIFICADOR; 
}

  /* 5. Literais */
{INT}     { 
    yylval.valor_lexico.integer = atoi(yytext); 
    yylval.line = get_line_number();
    yylval.type = INTEGER_T;
    return TK_LIT_INT;
}
{FLOAT}   { 
    yylval.valor_lexico.real = atof(yytext); 
    yylval.line = get_line_number();
    yylval.type = FLOAT_T;
    return TK_LIT_FLOAT; 
}
{STRING}  { 
    char *value = strdup(yytext);
    value[strlen(value)-1] = '\0';
    yylval.valor_lexico.string = value + 1;
    yylval.line = get_line_number();
    yylval.type = STRING_T;
    return TK_LIT_STRING; 
}
{CHAR}    { 
    char value = yytext[1]; // elimina as aspas
    yylval.valor_lexico.character = value; 
    yylval.line = get_line_number();
    yylval.type = CHAR_T;
    return TK_LIT_CHAR; 
}

  /* Captar caracteres irrelevantes para a linguagem */
[ \t\n]+ { }
{COMMENT} { }

  /* Captar erros, se não bateu nenhum token acima */
.               { return TOKEN_ERRO; }
\'(.)*\'        { return TOKEN_ERRO; }
