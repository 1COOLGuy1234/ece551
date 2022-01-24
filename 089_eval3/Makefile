CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++11
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) page.o story.o util.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o page.o story.o util.o
	g++ $(CPPFLAGS) -o $@ $^
%.o: %.c
	g++ $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

page.o: page.hpp
story.o: story.hpp

