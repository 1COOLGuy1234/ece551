#!/bin/bash
for i in `seq 65530 66000`
do
    ./isPrime-broken2 $i > result2.txt
    ./isPrime-correct $i > result_correct.txt
    diff result2.txt result_correct.txt > diff_2_correct.txt
    if [ -s ./diff_2_correct.txt ] ; then
	echo $i
    fi
done

