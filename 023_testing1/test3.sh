#!/bin/bash
for i in `seq 0 100000`
do
    ./isPrime-broken3 $i > result3.txt
    ./isPrime-correct $i > result_correct.txt
    if [[ $(diff result3.txt result_correct.txt | wc -c) -ne 0 ]]
    then
	echo $i
    fi
done
