# Folders path
OBJ := obj/
INC := include/
SRC := src/
DOC := doc/
TST := tests/
OUT := tests/output/
SIO := scripts/ilocsim_output/

all: dirs asp.o util.o hashmap.o list.o semantic.o instr_lst.o code_gen.o bool_lst.o stack.o depend_graph.o parser.tab.c lex.yy.c 
	gcc -c -g ${SRC}main.c -o ${OBJ}main.o -Wall
	gcc -c -g ${INC}parser.tab.c -o ${OBJ}parser.tab.o
	gcc -c -g ${SRC}lex.yy.c -o ${OBJ}lex.yy.o
	gcc -o etapa6 ${OBJ}main.o ${OBJ}asp.o ${OBJ}util.o ${OBJ}hashmap.o ${OBJ}list.o ${OBJ}semantic.o ${OBJ}instr_lst.o ${OBJ}code_gen.o ${OBJ}bool_lst.o ${OBJ}stack.o ${OBJ}depend_graph.o ${OBJ}lex.yy.o ${OBJ}parser.tab.o -lfl -Wall

parser.tab.c:
	bison -d -v --output=${INC}parser.tab.c ${SRC}parser.y --report-file ${DOC}parser.output

lex.yy.c:
	flex -o ${SRC}lex.yy.c ${SRC}scanner.l

asp.o:
	gcc -c -g ${SRC}asp.c -o ${OBJ}asp.o -I ${INC} -Wall

util.o:
	gcc -c -g ${SRC}util.c -o ${OBJ}util.o -I ${INC} -Wall

hashmap.o:
	gcc -c -g ${SRC}hashmap.c -o ${OBJ}hashmap.o -I ${INC} -Wall

list.o:
	gcc -c -g ${SRC}list.c -o ${OBJ}list.o -I ${INC} -Wall

semantic.o:
	gcc -c -g ${SRC}semantic.c -o ${OBJ}semantic.o -I ${INC} -Wall

instr_lst.o:
	gcc -c -g ${SRC}instr_lst.c -o ${OBJ}instr_lst.o -I ${INC} -Wall

code_gen.o:
	gcc -c -g ${SRC}code_gen.c -o ${OBJ}code_gen.o -I ${INC} -Wall

bool_lst.o:
	gcc -c -g ${SRC}bool_lst.c -o ${OBJ}bool_lst.o -I ${INC} -Wall

stack.o:
	gcc -c -g ${SRC}stack.c -o ${OBJ}stack.o -I ${INC} -Wall

depend_graph.o:
	gcc -c -g ${SRC}depend_graph.c -o ${OBJ}depend_graph.o -I ${INC} -Wall

dirs: 
	mkdir -p ${OBJ}
	mkdir -p ${DOC}

test: all
	@echo "\n"
	@cat -n ${TST}sample.c
	@echo "\n"
	@valgrind --leak-check=full --track-origins=yes ./etapa6 < ${TST}sample.c
	@#./etapa6 < ${SRC}sample.c

clean:
	rm ${SRC}lex.yy.c ${INC}parser.tab.* ${OBJ}*.o etapa6 ${DOC}*.output ${OUT}*.c ${OUT}*.iloc ${SIO}*.sim rm 