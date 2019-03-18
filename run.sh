#!/bin/bash

echo Compiling...
g++ -std=c++11 -O3 -Wall solver.cpp -lm

echo Running tests...
for i in {1..9}
do
	echo "======= Test #${i} ======="
	echo "Time: "
	time -p ./a.out < inputs/$i.in > tmp
	diff tmp inputs/$i.out | grep real
	echo "Valgrind call: "
	valgrind ./a.out < inputs/$i.in | grep HEAP
	
	

done

echo Cleaning up...
rm tmp
rm a.out
echo Done. Exiting...
