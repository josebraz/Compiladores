all: etapa3

etapa3: etapa3.o
	gcc -o etapa3 lex.yy.o parser.tab.o main.o asp.o util.o -lfl
	
etapa3.o: parser lex main.c asp.c
	gcc -c lex.yy.c parser.tab.c main.c asp.c util.c

parser: parser.y
	bison -d parser.y -v 

lex: scanner.l
	flex scanner.l
	
clean: 
	rm lex.yy.c parser.tab.c parser.tab.h etapa3
