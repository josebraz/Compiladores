# Cleaning and making
make

rm tests/output/*.s

# first base case testing
./etapa7 < tests/kwj00 > tests/output/kwj00.s
./etapa7 -O < tests/kwj00 > tests/output/kwj00-output.s

# looping through first cases
for i in 1 2 3 4 5 6 7 8 9;
    do 
    ./etapa7 < tests/kwj0"$i" > tests/output/kwj0"$i".s
    ./etapa7 -O < tests/kwj0"$i" > tests/output/kwj0"$i"-output.s
    done

# looping through every test case
for i in 10 11 12 13 14 15 16 17 18 19 20 21 23 24;
    do 
    ./etapa7 < tests/kwj"$i" > tests/output/kwj"$i".s
    ./etapa7 -O < tests/kwj"$i" > tests/output/kwj"$i"-output.s
    done

make clean
