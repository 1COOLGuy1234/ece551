CFLAGS=-std=gnu99 -pedantic -Wall
testPower: test-power.o power.o
	gcc -o testPower test-power.o power.o
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
power.o: power.c
	gcc $(CFLAGS) -c power.c
.PHONY: clean
clean:
	rm -f testPower *.o *.c~ *.h~
