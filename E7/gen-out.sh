make clean 
make 

rm output/asm/*.s

./etapa7 < input/expr_comuns.c > output/asm/expr_comuns.s
./etapa7 -O < input/expr_comuns.c > output/asm/expr_comuns-otimizada.s
./etapa7 < input/expr_const.c > output/asm/expr_const.s
./etapa7 -O < input/expr_const.c > output/asm/expr_const-otimizada.s

gcc -c output/asm/expr_comuns.s -o output/obj/expr_comuns.o
gcc output/obj/expr_comuns.o -o output/exec/expr_comuns

gcc -c output/asm/expr_comuns-otimizada.s -o output/obj/expr_comuns-otimizada.o
gcc output/obj/expr_comuns-otimizada.o -o output/exec/expr_comuns-otimizada

gcc -c output/asm/expr_const.s -o output/obj/expr_const.o
gcc output/obj/expr_const.o -o output/exec/expr_const

gcc -c output/asm/expr_const-otimizada.s -o output/obj/expr_const-otimizada.o
gcc output/obj/expr_const-otimizada.o -o output/exec/expr_const-otimizada