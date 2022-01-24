CFLAGS=-std=gnu99 -pedantic -Wall
test-subseq: test-subseq.o maxSeq.o
	gcc -o test-subseq test-subseq.o maxSeq.o
test-subseq.o: test-subseq.c
	gcc -c test-subseq.c
maxSeq.o: maxSeq.c
	gcc -c maxSeq.c
.PHONY: clean
	rm -f test *.o *.c~ *.h~
