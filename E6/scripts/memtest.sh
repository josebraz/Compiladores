echo "Running a valgrind complete mem test"
echo ""

cd .. 
make clean
make

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./etapa6 < tests/empty.c > tests/output/empty.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./etapa6 < tests/asd01 > tests/output/asd01

echo ""
echo "Test completed - results on folder output inside tests"