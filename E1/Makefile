all: etapa1

etapa1: lex.yy.c main.c tokens.h
	gcc -o etapa1 main.c lex.yy.c -lfl

lex.yy.c: scanner.l
	flex scanner.l