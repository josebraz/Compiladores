#!/usr/bin/bash

# Cleaning and making
make

rm tests/output/*.s
rm tests/exec/*

# first base case testing
./etapa7 < tests/kwj00 > tests/output/kwj00.s
./etapa7 -O < tests/kwj00 > tests/output/kwj00-output.s

gcc -c tests/output/kwj00.s -o tests/obj/kwj00.o
gcc tests/obj/kwj00.o -o tests/exec/kwj00

gcc -c tests/output/kwj00-output.s -o tests/obj/kwj00-output.o
gcc tests/obj/kwj00-output.o -o tests/exec/kwj00-output
#echo $lines_original
#echo $lines_optmized
    #if [ $lines_original \< $lines_optmized ]
    #    then echo "error kwj00-output.s"
    #fi

# looping through first cases
for i in 1 2 3 4 5 6 7 8 9;
    do 
    ./etapa7 < tests/kwj0"$i" > tests/output/kwj0"$i".s
    ./etapa7 -O < tests/kwj0"$i" > tests/output/kwj0"$i"-output.s
    
    gcc -c tests/output/kwj0"$i".s -o tests/obj/kwj0"$i".o
    gcc tests/obj/kwj0"$i".o -o tests/exec/kwj0"$i"

    gcc -c tests/output/kwj0"$i"-output.s -o tests/obj/kwj0"$i"-output.o
    gcc tests/obj/kwj0"$i"-output.o -o tests/exec/kwj0"$i"-output

    echo ""
    #if [ $lines_original \< $lines_optmized ]
    #    then echo "error kwj0"$i"-output.s"
    #fi
    done

# looping through every test case
for i in 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24;
    do 
    ./etapa7 < tests/kwj"$i" > tests/output/kwj"$i".s
    ./etapa7 -O < tests/kwj"$i" > tests/output/kwj"$i"-output.s

    gcc -c tests/output/kwj"$i".s -o tests/obj/kwj"$i".o
    gcc tests/obj/kwj"$i".o -o tests/exec/kwj"$i"

    gcc -c tests/output/kwj"$i"-output.s -o tests/obj/kwj"$i"-output.o
    gcc tests/obj/kwj"$i"-output.o -o tests/exec/kwj"$i"-output
    
    echo ""
    #if [ $lines_original \< $lines_optmized ]
    #    then echo "error kwj"$i"-output.s"
    #fi
    done

make clean
