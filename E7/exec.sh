echo "Type test name please:"

read testname
./etapa6 < tests/validation-tests/$testname > tests/output/"$testname.s"
gcc -c tests/output/"$testname.s" -o tests/obj/"$testname.o"
gcc tests/obj/"$testname.o" -o tests/exec/"$testname"
./$testname

"Program Output:"

echo $?