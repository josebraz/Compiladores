# Folders path
OBJ := obj/
INC := include/
SRC := src/
DOC := doc/
TST := test/

all: dirs asp.o util.o hashmap.o list.o semantic.o instr_lst.o code_gen.o bool_lst.o stack.o parser.tab.c lex.yy.c
	gcc -c ${SRC}main.c -o ${OBJ}main.o -Wall
	gcc -c ${INC}parser.tab.c -o ${OBJ}parser.tab.o
	gcc -c ${SRC}lex.yy.c -o ${OBJ}lex.yy.o
	gcc -o etapa5 ${OBJ}main.o ${OBJ}asp.o ${OBJ}util.o ${OBJ}hashmap.o ${OBJ}list.o ${OBJ}semantic.o ${OBJ}instr_lst.o ${OBJ}code_gen.o ${OBJ}bool_lst.o ${OBJ}stack.o ${OBJ}lex.yy.o ${OBJ}parser.tab.o -lfl -Wall

parser.tab.c:
	bison -d -v --output=${INC}parser.tab.c ${SRC}parser.y --report-file ${DOC}parser.output

lex.yy.c:
	flex -o ${SRC}lex.yy.c ${SRC}scanner.l

asp.o:
	gcc -c ${SRC}asp.c -o ${OBJ}asp.o -I ${INC} -Wall

util.o:
	gcc -c ${SRC}util.c -o ${OBJ}util.o -I ${INC} -Wall

hashmap.o:
	gcc -c ${SRC}hashmap.c -o ${OBJ}hashmap.o -I ${INC} -Wall

list.o:
	gcc -c ${SRC}list.c -o ${OBJ}list.o -I ${INC} -Wall

semantic.o:
	gcc -c ${SRC}semantic.c -o ${OBJ}semantic.o -I ${INC} -Wall

instr_lst.o:
	gcc -c ${SRC}instr_lst.c -o ${OBJ}instr_lst.o -I ${INC} -Wall

code_gen.o:
	gcc -c ${SRC}code_gen.c -o ${OBJ}code_gen.o -I ${INC} -Wall

bool_lst.o:
	gcc -c ${SRC}bool_lst.c -o ${OBJ}bool_lst.o -I ${INC} -Wall

stack.o:
	gcc -c ${SRC}stack.c -o ${OBJ}stack.o -I ${INC} -Wall

dirs: 
	mkdir -p ${OBJ}
	mkdir -p ${DOC}

test:
	@cat -n ${TST}test.c
	@valgrind --leak-check=full --track-origins=yes ./etapa5 < ${TST}test.c
	@#./etapa5 < ${SRC}test.c

clean:
	rm ${SRC}lex.yy.c ${INC}parser.tab.* ${OBJ}*.o etapa5 ${DOC}*.output