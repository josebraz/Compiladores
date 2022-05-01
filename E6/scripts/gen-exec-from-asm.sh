# root dir
cd ..

make

echo "Generating assembly from test file"
./etapa6 < tests/test.c > tests/test-out.s
echo ""

cd tests

echo "Generating object link file"
gcc -c test-out.s -o test-out.o
echo ""

echo "Generating exec"
gcc test-out.o -o test
echo ""



