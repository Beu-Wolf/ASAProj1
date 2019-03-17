#!/bin/bash

g++ solver.cpp

for i in {1..9}
do
	echo "======= Test #${i} ======="
	time -p ./a.out < inputs/$i.in > tmp
	diff tmp inputs/$i.out | grep real
done

rm tmp

rm a.out
