all: etapa5

etapa5: etapa5.o
	gcc -o etapa5 lex.yy.o parser.tab.o main.o asp.o util.o stack.o hashmap.o list.o semantic.o instr_lst.o code_gen.o bool_lst.o -lfl
	
etapa5.o: parser lex main.c asp.c stack.c hashmap.c list.c semantic.c instr_lst.c code_gen.c bool_lst.c
	gcc -c -g lex.yy.c parser.tab.c main.c asp.c util.c stack.c hashmap.c list.c semantic.c instr_lst.c code_gen.c bool_lst.c

parser: parser.y
	bison -d parser.y -v 

lex: scanner.l
	flex scanner.l
	
clean: 
	rm lex.yy.c parser.tab.c parser.tab.h *.o *.png *.output etapa5
