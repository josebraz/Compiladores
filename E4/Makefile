all: etapa4

etapa4: etapa4.o
	gcc -o etapa4 lex.yy.o parser.tab.o main.o asp.o util.o stack.o hashmap.o list.o semantic.o -lfl
	
etapa4.o: parser lex main.c asp.c stack.c hashmap.c list.c semantic.c 
	gcc -c -g lex.yy.c parser.tab.c main.c asp.c util.c stack.c hashmap.c list.c semantic.c 

parser: parser.y
	bison -d parser.y -v 

lex: scanner.l
	flex scanner.l
	
clean: 
	rm lex.yy.c parser.tab.c parser.tab.h *.o *.png *.output etapa4
