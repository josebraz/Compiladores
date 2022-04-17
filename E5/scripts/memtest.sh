echo "Running a valgrind complete mem test"
echo ""

cd .. 
make clean
make

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./etapa5 < tests/empty.c > tests/output/empty.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./etapa5 < tests/declaration.c > tests/output/declaration.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./etapa5 < tests/fibo.c > tests/output/fibo.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./etapa5 < tests/one_function.c > tests/output/one_function.c

echo ""
echo "Test completed - results on folder output inside tests"