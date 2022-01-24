#!/bin/bash
for i in `seq 0 1000`
do
    ./isPrime-broken4 $i > result4.txt
    ./isPrime-correct $i > result_correct.txt
    if [[ $(diff result4.txt result_correct.txt | wc -c) -ne 0 ]]
    then
	echo $i
    fi
done
