all: etapa2

etapa2: etapa2.o
	gcc -o etapa2 lex.yy.o parser.tab.o -lfl
	
etapa2.o: parser lex main.c 
	gcc -c lex.yy.c parser.tab.c

parser: parser.y
	bison -d parser.y

lex: scanner.l
	flex scanner.l
	
clean: 
	rm lex.yy.c parser.tab.c parser.tab.h etapa2
