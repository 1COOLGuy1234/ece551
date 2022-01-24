CFLAGS=-std=gnu99 -pedantic -Wall
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc -c test.c
.PHONY: clean
	rm -f test *.o *.c~ *.h~
