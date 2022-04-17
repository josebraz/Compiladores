echo "Testing program output with ilocsim.py simulator:"
echo ""

cd ..
make clean
make

./etapa5 < tests/declaration.c > tests/output/declaration.iloc
./etapa5 < tests/empty.c > tests/output/empty.iloc
./etapa5 < tests/fibo.c > tests/output/fibo.iloc
./etapa5 < tests/one_function.c > tests/output/one_function.iloc

echo ""
echo "Intermedaite code generate"
echo "Running ilocsim.py simulator:"
echo ""

python3 scripts/ilocsim.py tests/output/declaration.iloc > scripts/ilocsim_output/declaration.sim
python3 scripts/ilocsim.py tests/output/empty.iloc > scripts/ilocsim_output/empty.sim
python3 scripts/ilocsim.py tests/output/fibo.iloc > scripts/ilocsim_output/fibo.sim
python3 scripts/ilocsim.py tests/output/one_function.iloc > scripts/ilocsim_output/one_function.sim

echo ""
echo "ilocsim simulator ended"
echo "Results on scripts/ilocsim_output folder"

